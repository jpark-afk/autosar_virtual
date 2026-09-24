#!/usr/bin/env python3

import argparse
import json
import re
from pathlib import Path

import xml.etree.ElementTree as ET


SUPPORTED_PATTERNS = {
    "rte_reads": re.compile(r"\b(Rte_Read_[A-Za-z0-9_]+)\s*\("),
    "rte_writes": re.compile(r"\b(Rte_Write_[A-Za-z0-9_]+)\s*\("),
    "rte_irtriggers": re.compile(r"\b(Rte_IrTrigger_[A-Za-z0-9_]+)\s*\("),
}

REPORT_ONLY_PATTERNS = {
    "rte_calls": re.compile(r"\b(Rte_Call_[A-Za-z0-9_]+)\s*\("),
    "rte_irv_reads": re.compile(r"\b(Rte_IrvRead_[A-Za-z0-9_]+)\s*\("),
    "rte_irv_writes": re.compile(r"\b(Rte_IrvWrite_[A-Za-z0-9_]+)\s*\("),
    "rte_modes": re.compile(r"\b(Rte_Mode_[A-Za-z0-9_]+)\s*\("),
}


def strip_c_comments(text: str) -> str:
    """
    Remove C block comments and C++ style line comments.
    Keep newlines so reported line numbers remain stable.
    """

    def replace_block_comment(match):
        return "\n" * match.group(0).count("\n")

    text = re.sub(
        r"/\*.*?\*/",
        replace_block_comment,
        text,
        flags=re.DOTALL,
    )

    text = re.sub(
        r"//[^\n]*",
        "",
        text,
    )

    return text

def scan_file(path: Path, result: dict) -> None:
    text = path.read_text(encoding="utf-8", errors="ignore")
    text = strip_c_comments(text)

    patterns = {}
    patterns.update(SUPPORTED_PATTERNS)
    patterns.update(REPORT_ONLY_PATTERNS)

    for category, pattern in patterns.items():
        for match in pattern.finditer(text):
            symbol = match.group(1)

            line = text.count("\n", 0, match.start()) + 1

            result[category].append(
                {
                    "symbol": symbol,
                    "file": str(path),
                    "line": line,
                }
            )

# unused
# def deduplicate(result: dict) -> None:
#     for category, entries in result.items():
#         seen = set()
#         unique = []

#         for entry in entries:
#             key = entry["symbol"]

#             if key not in seen:
#                 seen.add(key)
#                 unique.append(entry)

#         result[category] = unique

def scan_psl_rxindication_callback(path: Path):
    """
    Scan the AUTOSAR adapter for the RTI PSL DDS RxIndication callback.

    Example:
        system_property.psl_property.dds_rxindication =
            DdsCddRxIndication;
    """

    text = path.read_text(
        encoding="utf-8",
        errors="ignore",
    )
    text = strip_c_comments(text)

    pattern = re.compile(
        r"\b[A-Za-z_][A-Za-z0-9_]*"
        r"\.psl_property"
        r"\.dds_rxindication"
        r"\s*=\s*"
        r"([A-Za-z_][A-Za-z0-9_]*)"
        r"\s*;"
    )

    match = pattern.search(text)

    if match is None:
        return None

    return match.group(1)

def scan_trigger_macros(path: Path) -> list:
    """
    Scan adapter headers for Trigger_* -> Rte_IrTrigger_* mappings.
    """

    text = path.read_text(encoding="utf-8", errors="ignore")
    text = strip_c_comments(text)

    pattern = re.compile(
        r"^[ \t]*#define[ \t]+"
        r"(Trigger_[A-Za-z0-9_]+)[ \t]+"
        r"(Rte_IrTrigger_[A-Za-z0-9_]+)",
        re.MULTILINE,
    )

    result = []

    for match in pattern.finditer(text):
        line = text.count("\n", 0, match.start()) + 1

        result.append(
            {
                "trigger": match.group(1),
                "rte_irtrigger": match.group(2),
                "file": str(path),
                "line": line,
            }
        )

    return result

def scan_function_dependencies(path: Path) -> list:
    """
    Find C function bodies and map RTE calls used inside each function.

    This is intentionally a lightweight scanner for generated DdsCdd C code.
    It uses brace matching instead of trying to fully parse C.
    """

    text = path.read_text(encoding="utf-8", errors="ignore")

    rte_pattern = re.compile(
        r"\b("
        r"Rte_Read_[A-Za-z0-9_]+|"
        r"Rte_Write_[A-Za-z0-9_]+|"
        r"Rte_IrTrigger_[A-Za-z0-9_]+|"
        r"Rte_Call_[A-Za-z0-9_]+|"
        r"Rte_IrvRead_[A-Za-z0-9_]+|"
        r"Rte_IrvWrite_[A-Za-z0-9_]+|"
        r"Rte_Mode_[A-Za-z0-9_]+|"
        r"Trigger_[A-Za-z0-9_]+"
        r")\s*\("
    )

    function_pattern = re.compile(
        r"FUNC\s*\([^)]*\)\s*"
        r"(?P<name>[A-Za-z_][A-Za-z0-9_]*)"
        r"\s*\([^;{}]*\)"
        r"(?:\s*/\*.*?\*/)*"
        r"\s*\{",
        re.MULTILINE,
    )

    result = []

    for match in function_pattern.finditer(text):
        function_name = match.group("name")

        brace_start = text.find("{", match.start())

        if brace_start < 0:
            continue

        depth = 0
        brace_end = None

        for index in range(brace_start, len(text)):
            if text[index] == "{":
                depth += 1

            elif text[index] == "}":
                depth -= 1

                if depth == 0:
                    brace_end = index + 1
                    break

        if brace_end is None:
            continue

        body = text[brace_start:brace_end]

        dependencies = []

        for rte_match in rte_pattern.finditer(body):
            symbol = rte_match.group(1)

            if symbol not in dependencies:
                dependencies.append(symbol)

        line = text.count("\n", 0, match.start()) + 1

        result.append(
            {
                "name": function_name,
                "file": str(path),
                "line": line,
                "rte_dependencies": dependencies,
            }
        )

    return result

def resolve_trigger_dependencies(result: dict) -> None:
    """
    Resolve Trigger_* dependencies through adapter macro mappings.
    Keep the original dependency and store the resolved RTE dependency
    separately.
    """

    trigger_map = {
        entry["trigger"]: entry["rte_irtrigger"]
        for entry in result["trigger_macros"]
    }

    for runnable in result["runnables"]:
        resolved = []

        for dependency in runnable["rte_dependencies"]:
            if dependency.startswith("Trigger_"):
                dependency = trigger_map.get(dependency, dependency)

            if dependency not in resolved:
                resolved.append(dependency)

        runnable["resolved_rte_dependencies"] = resolved

def load_arxml(path: Path):
    """
    Load an AUTOSAR ARXML document.

    XML comments are not part of the semantic scan.
    """

    tree = ET.parse(path)
    root = tree.getroot()

    namespace = ""

    if root.tag.startswith("{"):
        namespace = root.tag[1:].split("}", 1)[0]

    return tree, root, namespace

def scan_aswc_receive_points(
        root,
        namespace: str,
) -> list:
    """
    Scan ASWC DATA-RECEIVE-POINT-BY-ARGUMENTS entries.

    Extract:
      - R-Port name
      - data element name
      - generated Rte_Read symbol
    """

    ns = {"ar": namespace}
    result = []

    for access in root.findall(
        ".//ar:DATA-RECEIVE-POINT-BY-ARGUMENTS/"
        "ar:VARIABLE-ACCESS",
        ns,
    ):
        port_ref = access.findtext(
            ".//ar:PORT-PROTOTYPE-REF",
            default="",
            namespaces=ns,
        )

        data_ref = access.findtext(
            ".//ar:TARGET-DATA-PROTOTYPE-REF",
            default="",
            namespaces=ns,
        )

        if not port_ref or not data_ref:
            continue

        port = port_ref.rsplit("/", 1)[-1]
        data_element = data_ref.rsplit("/", 1)[-1]

        interface_ref = data_ref.rsplit("/", 1)[0]

        result.append(
            {
                "port": port,
                "data_element": data_element,
                "interface_ref": interface_ref,
                "symbol": (
                    f"Rte_Read_{port}_{data_element}"
                ),
            }
        )

    return result

def scan_aswc_send_points(
        root,
        namespace: str,
) -> list:
    """
    Scan ASWC DATA-SEND-POINTS entries.

    Extract:
      - P-Port name
      - data element name
      - generated Rte_Write symbol
    """

    ns = {"ar": namespace}
    result = []

    for access in root.findall(
        ".//ar:DATA-SEND-POINTS/"
        "ar:VARIABLE-ACCESS",
        ns,
    ):
        port_ref = access.findtext(
            ".//ar:PORT-PROTOTYPE-REF",
            default="",
            namespaces=ns,
        )

        data_ref = access.findtext(
            ".//ar:TARGET-DATA-PROTOTYPE-REF",
            default="",
            namespaces=ns,
        )

        if not port_ref or not data_ref:
            continue

        port = port_ref.rsplit("/", 1)[-1]
        data_element = data_ref.rsplit("/", 1)[-1]

        interface_ref = data_ref.rsplit("/", 1)[0]

        result.append(
            {
                "port": port,
                "data_element": data_element,
                "interface_ref": interface_ref,
                "symbol": (
                    f"Rte_Write_{port}_{data_element}"
                ),
            }
        )

    return result

def scan_arxml_implementation_data_types(
        root,
        namespace: str,
) -> list:
    """
    Scan STRUCTURE IMPLEMENTATION-DATA-TYPE definitions.

    Extract:
      - datatype name
      - member name
      - referenced implementation datatype
    """

    ns = {"ar": namespace}
    result = []

    for data_type in root.findall(
        ".//ar:IMPLEMENTATION-DATA-TYPE",
        ns,
    ):
        category = data_type.findtext(
            "ar:CATEGORY",
            default="",
            namespaces=ns,
        )

        if category != "STRUCTURE":
            continue

        type_name = data_type.findtext(
            "ar:SHORT-NAME",
            default="",
            namespaces=ns,
        )

        members = []

        for element in data_type.findall(
            "ar:SUB-ELEMENTS/"
            "ar:IMPLEMENTATION-DATA-TYPE-ELEMENT",
            ns,
        ):
            member_name = element.findtext(
                "ar:SHORT-NAME",
                default="",
                namespaces=ns,
            )

            type_ref = element.findtext(
                ".//ar:IMPLEMENTATION-DATA-TYPE-REF",
                default="",
                namespaces=ns,
            )

            if not type_ref:
                type_ref = element.findtext(
                    ".//ar:BASE-TYPE-REF",
                    default="",
                    namespaces=ns,
                )

            if not type_ref:
                raise SystemExit(
                    "ERROR: structure member type cannot be resolved: "
                    f"{type_name}.{member_name}"
                )

            members.append(
                {
                    "name": member_name,
                    "type_ref": type_ref,
                    "type_name": (
                        type_ref.rsplit("/", 1)[-1]
                        if type_ref else ""
                    ),
                }
            )

        if type_name:
            result.append(
                {
                    "name": type_name,
                    "category": category,
                    "members": members,
                }
            )

    return result

def scan_timing_events(root, namespace: str) -> list:
    """
    Scan AUTOSAR TIMING-EVENT elements.
    XML comments are ignored by ElementTree.
    """

    ns = {"ar": namespace}

    result = []

    for event in root.findall(".//ar:TIMING-EVENT", ns):
        short_name = event.findtext("ar:SHORT-NAME", default="", namespaces=ns)
        runnable_ref = event.findtext(
            "ar:START-ON-EVENT-REF",
            default="",
            namespaces=ns,
        )
        offset = event.findtext("ar:OFFSET", default="", namespaces=ns)
        period = event.findtext("ar:PERIOD", default="", namespaces=ns)

        runnable = runnable_ref.rsplit("/", 1)[-1] if runnable_ref else ""

        result.append(
            {
                "name": short_name,
                "runnable": runnable,
                "runnable_ref": runnable_ref,
                "offset": offset,
                "period": period,
            }
        )

    return result

def scan_init_events(root, namespace: str) -> list:
    """
    Scan AUTOSAR INIT-EVENT elements.
    """

    ns = {"ar": namespace}
    result = []

    for event in root.findall(".//ar:INIT-EVENT", ns):
        short_name = event.findtext(
            "ar:SHORT-NAME",
            default="",
            namespaces=ns,
        )

        runnable_ref = event.findtext(
            "ar:START-ON-EVENT-REF",
            default="",
            namespaces=ns,
        )

        runnable = runnable_ref.rsplit("/", 1)[-1] if runnable_ref else ""

        result.append(
            {
                "name": short_name,
                "runnable": runnable,
                "runnable_ref": runnable_ref,
            }
        )

    return result

def scan_data_received_events(root, namespace: str) -> list:
    """
    Scan AUTOSAR DATA-RECEIVED-EVENT elements.
    """

    ns = {"ar": namespace}
    result = []

    for event in root.findall(".//ar:DATA-RECEIVED-EVENT", ns):
        short_name = event.findtext(
            "ar:SHORT-NAME",
            default="",
            namespaces=ns,
        )

        runnable_ref = event.findtext(
            "ar:START-ON-EVENT-REF",
            default="",
            namespaces=ns,
        )

        port_ref = event.findtext(
            "ar:DATA-IREF/ar:CONTEXT-R-PORT-REF",
            default="",
            namespaces=ns,
        )

        data_ref = event.findtext(
            "ar:DATA-IREF/ar:TARGET-DATA-ELEMENT-REF",
            default="",
            namespaces=ns,
        )

        result.append(
            {
                "name": short_name,
                "runnable": runnable_ref.rsplit("/", 1)[-1]
                    if runnable_ref else "",
                "r_port": port_ref.rsplit("/", 1)[-1]
                    if port_ref else "",
                "data_element": data_ref.rsplit("/", 1)[-1]
                    if data_ref else "",
                "runnable_ref": runnable_ref,
                "r_port_ref": port_ref,
                "data_element_ref": data_ref,
            }
        )

    return result

def scan_internal_trigger_events(root, namespace: str) -> list:
    """
    Scan AUTOSAR INTERNAL-TRIGGER-OCCURRED-EVENT elements.
    """

    ns = {"ar": namespace}
    result = []

    for event in root.findall(
        ".//ar:INTERNAL-TRIGGER-OCCURRED-EVENT",
        ns,
    ):
        short_name = event.findtext(
            "ar:SHORT-NAME",
            default="",
            namespaces=ns,
        )

        runnable_ref = event.findtext(
            "ar:START-ON-EVENT-REF",
            default="",
            namespaces=ns,
        )

        source_ref = event.findtext(
            "ar:EVENT-SOURCE-REF",
            default="",
            namespaces=ns,
        )

        source_parts = source_ref.rstrip("/").split("/") if source_ref else []

        source_runnable = (
            source_parts[-2]
            if len(source_parts) >= 2
            else ""
        )

        triggering_point = (
            source_parts[-1]
            if source_parts
            else ""
        )

        result.append(
            {
                "name": short_name,
                "target_runnable": runnable_ref.rsplit("/", 1)[-1]
                    if runnable_ref else "",
                "source_runnable": source_runnable,
                "triggering_point": triggering_point,
                "runnable_ref": runnable_ref,
                "event_source_ref": source_ref,
            }
        )

    return result

def scan_arxml_runnables(root, namespace: str) -> list:
    """
    Scan all RUNNABLE-ENTITY definitions from the CDD ARXML.
    """

    ns = {"ar": namespace}
    result = []

    for runnable in root.findall(".//ar:RUNNABLE-ENTITY", ns):
        short_name = runnable.findtext(
            "ar:SHORT-NAME",
            default="",
            namespaces=ns,
        )

        if short_name:
            result.append(short_name)

    return result

def scan_arxml_r_ports(root, namespace: str) -> list:
    """
    Scan R-PORT-PROTOTYPE definitions and their data elements.
    """

    ns = {"ar": namespace}
    result = []

    for port in root.findall(".//ar:R-PORT-PROTOTYPE", ns):
        port_name = port.findtext(
            "ar:SHORT-NAME",
            default="",
            namespaces=ns,
        )

        interface_ref = port.findtext(
            "ar:REQUIRED-INTERFACE-TREF",
            default="",
            namespaces=ns,
        )

        for com_spec in port.findall(
            "ar:REQUIRED-COM-SPECS/"
            "ar:NONQUEUED-RECEIVER-COM-SPEC",
            ns,
        ):
            data_ref = com_spec.findtext(
                "ar:DATA-ELEMENT-REF",
                default="",
                namespaces=ns,
            )

            data_element = (
                data_ref.rsplit("/", 1)[-1]
                if data_ref else ""
            )

            result.append(
                {
                    "port": port_name,
                    "data_element": data_element,
                    "data_element_ref": data_ref,
                    "interface_ref": interface_ref,
                }
            )

    return result

def scan_arxml_p_ports(root, namespace: str) -> list:
    """
    Scan P-PORT-PROTOTYPE definitions and their data elements.
    """

    ns = {"ar": namespace}
    result = []

    for port in root.findall(".//ar:P-PORT-PROTOTYPE", ns):
        port_name = port.findtext(
            "ar:SHORT-NAME",
            default="",
            namespaces=ns,
        )

        interface_ref = port.findtext(
            "ar:PROVIDED-INTERFACE-TREF",
            default="",
            namespaces=ns,
        )

        for com_spec in port.findall(
            "ar:PROVIDED-COM-SPECS/"
            "ar:NONQUEUED-SENDER-COM-SPEC",
            ns,
        ):
            data_ref = com_spec.findtext(
                "ar:DATA-ELEMENT-REF",
                default="",
                namespaces=ns,
            )

            data_element = (
                data_ref.rsplit("/", 1)[-1]
                if data_ref else ""
            )

            result.append(
                {
                    "port": port_name,
                    "data_element": data_element,
                    "data_element_ref": data_ref,
                    "interface_ref": interface_ref,
                }
            )

    return result

def match_arxml_runnable_to_c(arxml_runnable: str, runnables: list):
    """
    Match an AUTOSAR runnable name to the generated DdsCdd C function.
    """

    expected_c_name = f"DdsCdd{arxml_runnable}"

    for runnable in runnables:
        if runnable["name"] == expected_c_name:
            return runnable

    return None

def build_rte_buffer_model(
        rte_reads: list,
        rte_writes: list,
        aswc_reads: list,
        aswc_writes: list,
) -> list:
    """
    Build one Virtual RTE buffer per communication endpoint.

    Endpoint identity:
        (interface_ref, data_element)

    Supports:
        N CDD Reads / M CDD Writes
        N or M may be zero, but not both.
    """

    buffers = {}

    for entry in (
        rte_reads
        + rte_writes
        + aswc_reads
        + aswc_writes
    ):
        key = (
            entry["interface_ref"],
            entry["data_element"],
        )

        if key not in buffers:
            interface_name = (
                entry["interface_ref"]
                .rsplit("/", 1)[-1]
            )

            buffer_name = (
                "g_"
                + interface_name.lower()
            )

            buffers[key] = {
                "interface_ref": entry["interface_ref"],
                "interface_name": interface_name,
                "data_element": entry["data_element"],
                "buffer_name": buffer_name,
            }

    return list(buffers.values())

def generate_rte_type_header(rte_data_types: list) -> str:
    """
    Generate the complete Virtual AUTOSAR Rte_Type.h content.
    """

    lines = [
        "#ifndef RTE_TYPE_H",
        "#define RTE_TYPE_H",
        "",
        '#include "Std_Types.h"',
        "",
        "/* --------------------------------------------------------------------------",
        " * Virtual RTE application data types",
        " * -------------------------------------------------------------------------- */",
        "",
    ]

    for data_type in rte_data_types:
        if data_type["category"] != "STRUCTURE":
            raise ValueError(
                "Unsupported RTE datatype category: "
                f'{data_type["category"]} '
                f'({data_type["name"]})'
            )

        lines.append("typedef struct")
        lines.append("{")

        type_width = max(
            len(member["type_name"])
            for member in data_type["members"]
        )

        for member in data_type["members"]:
            lines.append(
                f'    {member["type_name"]:<{type_width}} '
                f'{member["name"]};'
            )

        lines.append(f'}} {data_type["name"]};')
        lines.append("")

    lines.append("#endif /* RTE_TYPE_H */")
    lines.append("")

    return "\n".join(lines)

def generate_rte_ddscdd_type_header(
        rte_reads: list,
        rte_writes: list,
        aswc_reads: list,
        aswc_writes: list,
        data_received: list,
        internal_trigger: list,
        psl_rxindication_callback,
) -> str:
    """
    Generate the CDD-derived portion of Virtual AUTOSAR Rte_DdsCddType.h.
    """

    lines = [
        "#ifndef RTE_DDSCDDTYPE_H",
        "#define RTE_DDSCDDTYPE_H",
        "",
        '#include "Std_Types.h"',
        '#include "Rte_Type.h"',
        "",
        "/* --------------------------------------------------------------------------",
        " * Minimal AUTOSAR RTE compatibility for Virtual AUTOSAR",
        " * -------------------------------------------------------------------------- */",
        "",
        "#ifndef FUNC",
        "#define FUNC(rettype, memclass) rettype",
        "#endif",
        "",
        "#ifndef DdsCdd_CODE",
        "#define DdsCdd_CODE",
        "#endif",
        "",
        "/* --------------------------------------------------------------------------",
        " * RTE Sender/Receiver APIs",
        " * -------------------------------------------------------------------------- */",
        "",
    ]

    for entry in rte_reads:
        lines.extend([
            "Std_ReturnType",
            f'{entry["symbol"]}(',
            f'    {entry["data_element"]} *data);',
            "",
        ])

    for entry in rte_writes:
        lines.extend([
            "Std_ReturnType",
            f'{entry["symbol"]}(',
            f'    const {entry["data_element"]} *data);',
            "",
        ])
    
    for entry in aswc_reads:
        lines.extend([
            "Std_ReturnType",
            f'{entry["symbol"]}(',
            f'    {entry["data_element"]} *data);',
            "",
        ])
    
    for entry in aswc_writes:
        lines.extend([
            "Std_ReturnType",
            f'{entry["symbol"]}(',
            f'    const {entry["data_element"]} *data);',
            "",
        ])

    lines.extend([
        "/* --------------------------------------------------------------------------",
        " * RTE Internal Trigger APIs",
        " * -------------------------------------------------------------------------- */",
        "",
    ])

    for entry in internal_trigger:
        lines.extend([
            f'void {entry["rte_trigger"]}(void);',
            "",
        ])

    lines.extend([
        "/* --------------------------------------------------------------------------",
        " * Virtual DataReceivedEvent state",
        " * -------------------------------------------------------------------------- */",
        "",
    ])

    for entry in data_received:
        port_name = entry["r_port"]

        if port_name.startswith("R_"):
            port_name = port_name[2:]

        lines.extend([
            f'boolean Rte_ConsumeDataReceived_{port_name}(void);',
            "",
        ])
    
    if psl_rxindication_callback is not None:
        lines.extend([
            "/* --------------------------------------------------------------------------",
            " * RTI AUTOSAR PSL callback",
            " * -------------------------------------------------------------------------- */",
            "",
            "FUNC(void, DdsCdd_CODE) "
            f"{psl_rxindication_callback}(void);",
            "",
        ])

    lines.append("#endif /* RTE_DDSCDDTYPE_H */")
    lines.append("")

    return "\n".join(lines)

def generate_rte_ddscdd_type_source(
    rte_buffers: list,
    rte_reads: list,
    rte_writes: list,
    aswc_reads: list,
    aswc_writes: list,
    data_received: list,
    internal_trigger: list,
) -> str:
    """
    Generate the Virtual AUTOSAR Rte_DdsCddType.c source.

    Phase 4.3-D:
      - fixed includes
      - shared RTE data buffers
    """

    lines = [
        '#include <string.h>',
        "",
        '#include "tpl_os.h"',
        '#include "Rte_DdsCddType.h"',
        "",
        "/* --------------------------------------------------------------------------",
        " * Virtual RTE data buffers",
        " * -------------------------------------------------------------------------- */",
        "",
    ]

    for buffer in rte_buffers:
        lines.append(
            f'static {buffer["data_element"]} '
            f'{buffer["buffer_name"]};'
        )

    for event in data_received:
        key = (
            event["interface_ref"],
            event["data_element"],
        )

        buffer = next(
            buffer
            for buffer in rte_buffers
            if (
                buffer["interface_ref"],
                buffer["data_element"],
            ) == key
        )

        flag_name = f'{buffer["buffer_name"]}_received'

        lines.append(
            f"static boolean {flag_name} = FALSE;"
        )

    for entry in aswc_reads:
        key = (
            entry["interface_ref"],
            entry["data_element"],
        )

        buffer = next(
            buffer
            for buffer in rte_buffers
            if (
                buffer["interface_ref"],
                buffer["data_element"],
            ) == key
        )

        lines.append(
            f'static boolean {buffer["buffer_name"]}_unread = FALSE;'
        )

    lines.append("")

    for entry in rte_reads:
        key = (
            entry["interface_ref"],
            entry["data_element"],
        )

        buffer = next(
            buffer
            for buffer in rte_buffers
            if (
                buffer["interface_ref"],
                buffer["data_element"],
            ) == key
        )        

        lines.extend([
            "Std_ReturnType",
            f'{entry["symbol"]}(',
            f'        {entry["data_element"]} *data)',
            "{",
            "    if (data == NULL)",
            "    {",
            "        return E_NOT_OK;",
            "    }",
            "",
            f'    memcpy(data, &{buffer["buffer_name"]}, sizeof(*data));',
            "",
            "    return E_OK;",
            "}",
            "",
        ])

    for entry in rte_writes:
        key = (
            entry["interface_ref"],
            entry["data_element"],
        )

        buffer = next(
            buffer
            for buffer in rte_buffers
            if (
                buffer["interface_ref"],
                buffer["data_element"],
            ) == key
        )

        aswc_read = next(
            (
                read
                for read in aswc_reads
                if (
                    read["interface_ref"],
                    read["data_element"],
                ) == key
            ),
            None,
        )

        lines.extend([
            "Std_ReturnType",
            f'{entry["symbol"]}(',
            f'        const {entry["data_element"]} *data)',
            "{",
            "    if (data == NULL)",
            "    {",
            "        return E_NOT_OK;",
            "    }",
            "",
            f'    memcpy(&{buffer["buffer_name"]}, data, sizeof(*data));',
        ])

        if aswc_read is not None:
            lines.append(
                f'    {buffer["buffer_name"]}_unread = TRUE;'
            )

        lines.extend([
            "",
            "    return E_OK;",
            "}",
            "",
        ])

    for entry in aswc_reads:
        key = (
            entry["interface_ref"],
            entry["data_element"],
        )

        buffer = next(
            buffer
            for buffer in rte_buffers
            if (
                buffer["interface_ref"],
                buffer["data_element"],
            ) == key
        )

        lines.extend([
            "Std_ReturnType",
            f'{entry["symbol"]}(',
            f'        {entry["data_element"]} *data)',
            "{",
            "    if ((data == NULL) ||",
            f'        ({buffer["buffer_name"]}_unread == FALSE))',
            "    {",
            "        return E_NOT_OK;",
            "    }",
            "",
            f'    memcpy(data, &{buffer["buffer_name"]}, sizeof(*data));',
            f'    {buffer["buffer_name"]}_unread = FALSE;',
            "",
            "    return E_OK;",
            "}",
            "",
        ])

    for entry in aswc_writes:
        key = (
            entry["interface_ref"],
            entry["data_element"],
        )

        buffer = next(
            buffer
            for buffer in rte_buffers
            if (
                buffer["interface_ref"],
                buffer["data_element"],
            ) == key
        )

        received_event = next(
            (
                event
                for event in data_received
                if (
                    event["interface_ref"],
                    event["data_element"],
                ) == key
            ),
            None,
        )

        flag_name = (
            f'{buffer["buffer_name"]}_received'
            if received_event is not None
            else None
        )

        lines.extend([
            "Std_ReturnType",
            f'{entry["symbol"]}(',
            f'        const {entry["data_element"]} *data)',
            "{",
            "    if (data == NULL)",
            "    {",
            "        return E_NOT_OK;",
            "    }",
            "",
            f'    memcpy(&{buffer["buffer_name"]}, data, sizeof(*data));',
        ])

        if flag_name is not None:
            lines.extend([
                f"    {flag_name} = TRUE;",
                "    (void)SetEvent(",
                "        DdsCddWrite_Task,",
                "        DdsCddPeriodicWriteEvent);",
            ])

        lines.extend([
            "",
            "    return E_OK;",
            "}",
            "",
        ])
    
    for event in data_received:
        key = (
            event["interface_ref"],
            event["data_element"],
        )

        buffer = next(
            buffer
            for buffer in rte_buffers
            if (
                buffer["interface_ref"],
                buffer["data_element"],
            ) == key
        )

        flag_name = f'{buffer["buffer_name"]}_received'

        port_name = event["r_port"]
        if port_name.startswith("R_"):
            port_name = port_name[2:]

        lines.extend([
            f"boolean Rte_ConsumeDataReceived_{port_name}(void)",
            "{",
            f"    if ({flag_name} == FALSE)",
            "    {",
            "        return FALSE;",
            "    }",
            "",
            f"    {flag_name} = FALSE;",
            "",
            "    return TRUE;",
            "}",
            "",
        ])
    
    fixed_internal_trigger_map = {
        "Enable": (
            "DdsCddStart_Task",
            "DdsCddStartEvent",
        ),
        "TimerUpdate": (
            "DdsCddWrite_Task",
            "DdsCddTimerUpdateEvent",
        ),
        "ProcessData": (
            "DdsCddProcessData_Task",
            "DdsCddProcessDataEvent",
        ),
    }

    for entry in internal_trigger:
        target = entry["target_runnable"]

        if target not in fixed_internal_trigger_map:
            raise SystemExit(
                "ERROR: InternalTrigger target is incompatible "
                "with fixed Virtual AUTOSAR OS model: "
                f"{target} "
                f"(event={entry['event']})"
            )

        task_name, event_name = fixed_internal_trigger_map[target]

        lines.extend([
            f'void {entry["rte_trigger"]}(void)',
            "{",
            "    (void)SetEvent(",
            f"        {task_name},",
            f"        {event_name});",
            "}",
            "",
        ])

    return "\n".join(lines)


def generate_virtual_aswc_header() -> str:
    """Generate the Virtual ASWC runnable interface."""

    return "\n".join([
        "#ifndef VIRTUAL_ASWC_H",
        "#define VIRTUAL_ASWC_H",
        "",
        "void VirtualAswc_Run(void);",
        "",
        "#endif /* VIRTUAL_ASWC_H */",
        "",
    ])


def generate_virtual_aswc_source(
        aswc_reads: list,
        aswc_writes: list,
) -> str:
    """Generate a type-safe default Virtual ASWC test runnable."""

    lines = [
        '#include <stdio.h>',
        '#include <string.h>',
        "",
        '#include "VirtualAswc.h"',
        '#include "Rte_DdsCddType.h"',
        "",
        "void VirtualAswc_Run(void)",
        "{",
    ]

    if aswc_writes:
        lines.append("    static uint8 counter = 0U;")
        lines.append("")

    for index, entry in enumerate(aswc_reads):
        variable_name = f"read_data_{index}"
        status_name = f"read_status_{index}"
        port_name = entry["port"]

        if port_name.startswith("R_"):
            port_name = port_name[2:]

        lines.extend([
            f'    {entry["data_element"]} {variable_name};',
            f'    Std_ReturnType {status_name};',
            "",
            f'    {status_name} = {entry["symbol"]}(&{variable_name});',
            "",
            f'    if ({status_name} == E_OK)',
            "    {",
            f'        printf("[VirtualAswc] {port_name} received first=0x%02X\\n",',
            f'                (unsigned int)((const uint8 *)&{variable_name})[0]);',
            "    }",
            "",
        ])

    for index, entry in enumerate(aswc_writes):
        variable_name = f"write_data_{index}"

        lines.extend([
            f'    {entry["data_element"]} {variable_name};',
            "",
            f'    memset(&{variable_name}, 0, sizeof({variable_name}));',
            f'    ((uint8 *)&{variable_name})[0] = counter++;',
            f'    (void){entry["symbol"]}(&{variable_name});',
            "",
        ])

    lines.extend([
        "}",
        "",
    ])

    return "\n".join(lines)


def generate_ddscdd_task_source(
    data_received: list,
    timing: list,
    init: list,
    internal_trigger: list,
) -> str:
    """
    Generate CDD-specific AUTOSAR task implementations.

    The Virtual AUTOSAR OS topology is fixed. This generator only maps
    CDD semantic events/runnables onto that fixed task model.
    """

    timer_update = next(
        (
            entry
            for entry in internal_trigger
            if entry["target_runnable"] == "TimerUpdate"
        ),
        None,
    )

    init_runnable = next(
        (
            entry
            for entry in init
            if entry["arxml_runnable"] == "Init"
        ),
        None,
    )

    start_runnable = next(
        (
            entry
            for entry in internal_trigger
            if entry["target_runnable"] == "Enable"
        ),
        None,
    )

    process_data = next(
        (
            entry
            for entry in internal_trigger
            if entry["target_runnable"] == "ProcessData"
        ),
        None,
    )

    timer_tick = next(
        (
            entry
            for entry in timing
            if entry["arxml_runnable"] == "TimerTick"
        ),
        None,
    )

    if init_runnable is None:
        raise SystemExit(
            "ERROR: fixed Virtual AUTOSAR model requires "
            "Init InitEvent"
        )

    if start_runnable is None:
        raise SystemExit(
            "ERROR: fixed Virtual AUTOSAR model requires "
            "InternalTrigger target Enable"
        )

    if timer_update is None:
        raise SystemExit(
            "ERROR: fixed Virtual AUTOSAR model requires "
            "InternalTrigger target TimerUpdate"
        )

    if process_data is None:
        raise SystemExit(
            "ERROR: fixed Virtual AUTOSAR model requires "
            "InternalTrigger target ProcessData"
        )

    if timer_tick is None:
        raise SystemExit(
            "ERROR: fixed Virtual AUTOSAR model requires "
            "TimerTick TimingEvent"
        )

    periodic_runnables = [
        entry
        for entry in timing
        if entry["arxml_runnable"] != "TimerTick"
    ]

    declarations = {
        init_runnable["c_runnable"],
        start_runnable["target_c_runnable"],
        timer_tick["c_runnable"],
        timer_update["target_c_runnable"],
        process_data["target_c_runnable"],
    }

    declarations.update(
        entry["c_runnable"]
        for entry in data_received
    )

    declarations.update(
        entry["c_runnable"]
        for entry in periodic_runnables
    )

    lines = [
        '#include <stdio.h>',
        "",
        '#include "tpl_os.h"',
        '#include "Rte_DdsCddType.h"',
        "",
        "/* --------------------------------------------------------------------------",
        " * CDD runnable declarations",
        " * -------------------------------------------------------------------------- */",
        "",
    ]

    for runnable in sorted(declarations):
        lines.append(f"extern void {runnable}(void);")

    lines.extend([
        "",
        "/* --------------------------------------------------------------------------",
        " * CDD initialization and start tasks",
        " * -------------------------------------------------------------------------- */",
        "",
        "TASK(DdsCddInit_Task)",
        "{",
        f'    {init_runnable["c_runnable"]}();',
        '    printf("[DdsCddInit_Task] DdsCddInit completed.\\n");',
        "",
        "    TerminateTask();",
        "}",
        "",
        "TASK(DdsCddStart_Task)",
        "{",
        "    EventMaskType events;",
        "",
        "    WaitEvent(DdsCddStartEvent);",
        "    GetEvent(DdsCddStart_Task, &events);",
        "",
        "    if ((events & DdsCddStartEvent) != 0U)",
        "    {",
        "        ClearEvent(DdsCddStartEvent);",
        f'        {start_runnable["target_c_runnable"]}();',
        '        printf("[DdsCddStart_Task] DdsCddEnable completed.\\n");',
        "    }",
        "",
        "    TerminateTask();",
        "}",
        "",
        "/* --------------------------------------------------------------------------",
        " * CDD TimerTick task",
        " * -------------------------------------------------------------------------- */",
        "",
        "TASK(DdsCddTimerTick_Task)",
        "{",
        f'    {timer_tick["c_runnable"]}();',
        "",
        "    TerminateTask();",
        "}",
        "",
        "/* --------------------------------------------------------------------------",
        " * CDD Write task",
        " * -------------------------------------------------------------------------- */",
        "",
        "TASK(DdsCddWrite_Task)",
        "{",
        "    EventMaskType events;",
        "",
        "    for (;;)",
        "    {",
        "        WaitEvent(",
        "            DdsCddTimerUpdateEvent |",
        "            DdsCddPeriodicWriteEvent);",
        "",
        "        GetEvent(DdsCddWrite_Task, &events);",
        "",
        "        if ((events & DdsCddTimerUpdateEvent) != 0U)",
        "        {",
        "            ClearEvent(DdsCddTimerUpdateEvent);",
        "",
        f'            {timer_update["target_c_runnable"]}();',
        "        }",
        "",
        "        if ((events & DdsCddPeriodicWriteEvent) != 0U)",
        "        {",
        "            ClearEvent(DdsCddPeriodicWriteEvent);",
        "",
    ])

    for entry in data_received:
        port_name = entry["r_port"]

        if port_name.startswith("R_"):
            port_name = port_name[2:]

        lines.extend([
            f"            if (Rte_ConsumeDataReceived_{port_name}() != FALSE)",
            "            {",
            f'                {entry["c_runnable"]}();',
            "            }",
            "",
        ])

    lines.extend([
        "        }",
        "    }",
        "}",
        "",
        "/* --------------------------------------------------------------------------",
        " * CDD Read task",
        " * -------------------------------------------------------------------------- */",
        "",
        "TASK(DdsCddRead_Task)",
        "{",
        "    EventMaskType events;",
        "",
        "    for (;;)",
        "    {",
        "        WaitEvent(DdsCddPeriodicReadEvent);",
        "",
        "        GetEvent(DdsCddRead_Task, &events);",
        "",
        "        if ((events & DdsCddPeriodicReadEvent) != 0U)",
        "        {",
        "            ClearEvent(DdsCddPeriodicReadEvent);",
        "",
    ])

    for entry in periodic_runnables:
        lines.append(
            f'            {entry["c_runnable"]}();'
        )

    lines.extend([
        "        }",
        "    }",
        "}",
        "",
        "/* --------------------------------------------------------------------------",
        " * CDD ProcessData task",
        " * -------------------------------------------------------------------------- */",
        "",
        "TASK(DdsCddProcessData_Task)",
        "{",
        "    EventMaskType events;",
        "",
        "    for (;;)",
        "    {",
        "        WaitEvent(DdsCddProcessDataEvent);",
        "",
        "        GetEvent(DdsCddProcessData_Task, &events);",
        "",
        "        if ((events & DdsCddProcessDataEvent) != 0U)",
        "        {",
        "            ClearEvent(DdsCddProcessDataEvent);",
        "",
        f'            {process_data["target_c_runnable"]}();',
        "        }",
        "    }",
        "}",
        "",
    ])

    return "\n".join(lines)

def main() -> None:
    parser = argparse.ArgumentParser(
        description="Scan generated DdsCdd sources for RTE dependencies."
    )

    parser.add_argument(
        "source_dir",
        type=Path,
        help="Directory containing generated DdsCdd C/H files",
    )

    parser.add_argument(
        "-o",
        "--output",
        type=Path,
        default=Path("build/ddscdd_scan.json"),
        help="Output JSON file",
    )

    parser.add_argument(
        "--rte-output-dir",
        type=Path,
        default=None,
        help="Directory for generated Virtual RTE files",
    )

    args = parser.parse_args()

    if not args.source_dir.is_dir():
        raise SystemExit(
            f"ERROR: source directory not found: {args.source_dir}"
        )

    result = {
        "rte_reads": [],
        "rte_writes": [],
        "rte_irtriggers": [],
        "rte_calls": [],
        "rte_irv_reads": [],
        "rte_irv_writes": [],
        "rte_modes": [],
        "runnables": [],
        "trigger_macros": [],
    }

    files = sorted(
        list(args.source_dir.rglob("*.c"))
        + list(args.source_dir.rglob("*.h"))
    )

    for path in files:
        scan_file(path, result)

        if path.suffix == ".c":
            result["runnables"].extend(
                scan_function_dependencies(path)
            )
    
    adapter_header = args.source_dir.parent / "adaptation" / "dds_cdd_adapter.h"

    if adapter_header.is_file():
        result["trigger_macros"].extend(
            scan_trigger_macros(adapter_header)
        )

    adapter_source = (
        args.source_dir.parent
        / "adaptation"
        / "dds_cdd_adapter.c"
    )

    psl_rxindication_callback = None

    if adapter_source.is_file():
        psl_rxindication_callback = (
            scan_psl_rxindication_callback(adapter_source)
        )

    print(
        "PSL RxIndication callback:",
        psl_rxindication_callback,
    )
    
    # ------------------------------------------------------------------
    # Discover and load CDD ARXML
    # ------------------------------------------------------------------

    cdd_arxml = args.source_dir.parent / "autosar_model" / "DdsCddType.arxml"

    if not cdd_arxml.is_file():
        raise SystemExit(
            f"ERROR: CDD ARXML not found: {cdd_arxml}"
        )
    
    cdd_root = args.source_dir.parent
    app_name = cdd_root.name

    aswc_arxml = (
        cdd_root.parent
        / f"{app_name}_EXAMPLE_ASWC"
        / "autosar_model"
        / "application.arxml"
    )

    if not aswc_arxml.is_file():
        raise SystemExit(
            f"ERROR: ASWC ARXML not found: {aswc_arxml}"
        )
    
    _, aswc_root, aswc_namespace = load_arxml(
        aswc_arxml
    )
    print("ASWC ARXML :", aswc_arxml)
    print("ASWC NS    :", aswc_namespace)

    aswc_receive_points = scan_aswc_receive_points(
        aswc_root,
        aswc_namespace,
    )

    print("ASWC RECEIVE POINTS:")
    for entry in aswc_receive_points:
        print(entry)
    
    aswc_send_points = scan_aswc_send_points(
        aswc_root,
        aswc_namespace,
    )

    print("ASWC SEND POINTS:")
    for entry in aswc_send_points:
        print(entry)

    # ------------------------------------------------------------------
    # Discover DDS datatype ARXML
    # ------------------------------------------------------------------

    dds_types_arxml = (
        args.source_dir.parent
        / "dds_gen"
        / "dds_system_types.arxml"
    )

    if not dds_types_arxml.is_file():
        raise SystemExit(
            f"ERROR: DDS datatype ARXML not found: {dds_types_arxml}"
        )

    _, arxml_root, arxml_namespace = load_arxml(cdd_arxml)

    _, dds_types_root, dds_types_namespace = load_arxml(
        dds_types_arxml
    )

    dds_implementation_types = scan_arxml_implementation_data_types(
        dds_types_root,
        dds_types_namespace,
    )

    arxml_runnables = scan_arxml_runnables(
        arxml_root,
        arxml_namespace,
    )

    arxml_r_ports = scan_arxml_r_ports(
        arxml_root,
        arxml_namespace,
    )

    arxml_p_ports = scan_arxml_p_ports(
        arxml_root,
        arxml_namespace,
    )

    normalized_rte_reads = []

    rte_read_symbols = {
        entry["symbol"]: entry
        for entry in result["rte_reads"]
    }

    for port in arxml_r_ports:
        expected_symbol = (
            f'Rte_Read_{port["port"]}_{port["data_element"]}'
        )

        raw = rte_read_symbols.get(expected_symbol)

        normalized_rte_reads.append(
            {
                "symbol": expected_symbol,
                "port": port["port"],
                "data_element": port["data_element"],
                "interface_ref": port["interface_ref"],
                "found_in_c": raw is not None,
                "file": raw["file"] if raw else None,
                "line": raw["line"] if raw else None,
            }
        )

    normalized_rte_writes = []

    rte_write_symbols = {
        entry["symbol"]: entry
        for entry in result["rte_writes"]
    }

    for port in arxml_p_ports:
        expected_symbol = (
            f'Rte_Write_{port["port"]}_{port["data_element"]}'
        )

        raw = rte_write_symbols.get(expected_symbol)

        normalized_rte_writes.append(
            {
                "symbol": expected_symbol,
                "port": port["port"],
                "data_element": port["data_element"],
                "interface_ref": port["interface_ref"],
                "found_in_c": raw is not None,
                "file": raw["file"] if raw else None,
                "line": raw["line"] if raw else None,
            }
        )
    
    if (
        not normalized_rte_reads
        and not normalized_rte_writes
    ):
        raise SystemExit(
            "ERROR: DdsCdd has neither Rte_Read nor Rte_Write interface"
        )
    
    # ------------------------------------------------------------------
    # Build RTE datatype model
    #
    # Only datatypes actually referenced by CDD R/P ports are required
    # by the generated Virtual RTE.
    # ------------------------------------------------------------------

    required_rte_type_names = {
        entry["data_element"]
        for entry in (
            normalized_rte_reads
            + normalized_rte_writes
        )
    }

    rte_data_types = [
        data_type
        for data_type in dds_implementation_types
        if data_type["name"] in required_rte_type_names
    ]

    found_rte_type_names = {
        data_type["name"]
        for data_type in rte_data_types
    }

    missing_rte_type_names = (
        required_rte_type_names
        - found_rte_type_names
    )

    if missing_rte_type_names:
        raise SystemExit(
            "ERROR: required RTE datatype not found in DDS datatype ARXML: "
            + ", ".join(sorted(missing_rte_type_names))
        )
    
    rte_type_header = generate_rte_type_header(
        rte_data_types
    )

    expected_c_runnables = {
        f"DdsCdd{name}"
        for name in arxml_runnables
    }

    result["runnables"] = [
        runnable
        for runnable in result["runnables"]
        if runnable["name"] in expected_c_runnables
    ]

    print("\n===== CDD ARXML RUNNABLES =====")

    for runnable in arxml_runnables:
        print(runnable)

    timing_events = scan_timing_events(
        arxml_root,
        arxml_namespace,
    )

    init_events = scan_init_events(
        arxml_root,
        arxml_namespace,
    )

    data_received_events = scan_data_received_events(
        arxml_root,
        arxml_namespace,
    )

    internal_trigger_events = scan_internal_trigger_events(
        arxml_root,
        arxml_namespace,
    )

    resolve_trigger_dependencies(result) #important call


    print("\n===== INIT EVENT -> C RUNNABLE =====")

    for event in init_events:
        matched = match_arxml_runnable_to_c(
            event["runnable"],
            result["runnables"],
        )

        if matched is None:
            print(f"{event['runnable']} -> NOT FOUND")
        else:
            print(
                f"{event['runnable']}"
                f" -> {matched['name']}"
            )

    # --------------------------------------------------------------
    # Temporary validation: ARXML TimingEvent -> generated C runnable
    # --------------------------------------------------------------

    print("\n===== TIMING EVENT -> C RUNNABLE =====")

    for event in timing_events:
        matched = match_arxml_runnable_to_c(
            event["runnable"],
            result["runnables"],
        )

        if matched is None:
            print(f"{event['runnable']} -> NOT FOUND")
        else:
            print(
                f"{event['runnable']}"
                f" -> {matched['name']}"
            )

    # --------------------------------------------------------------
    # Temporary validation: DataReceivedEvent -> generated C runnable
    # --------------------------------------------------------------

    print("\n===== DATA RECEIVED EVENT -> C RUNNABLE =====")

    for event in data_received_events:
        matched = match_arxml_runnable_to_c(
            event["runnable"],
            result["runnables"],
        )

        if matched is None:
            print(f"{event['runnable']} -> NOT FOUND")
        else:
            print(
                f"{event['runnable']}"
                f" -> {matched['name']}"
            )

    # --------------------------------------------------------------
    # Temporary validation: InternalTrigger source -> generated C runnable
    # --------------------------------------------------------------

    print("\n===== INTERNAL TRIGGER SOURCE -> C RUNNABLE =====")

    for event in internal_trigger_events:
        matched = match_arxml_runnable_to_c(
            event["source_runnable"],
            result["runnables"],
        )

        if matched is None:
            print(f"{event['source_runnable']} -> NOT FOUND")
        else:
            print(
                f"{event['source_runnable']}"
                f" -> {matched['name']}"
            )

    print("\n===== INTERNAL TRIGGER -> RTE DEPENDENCY =====")

    for event in internal_trigger_events:
        matched = match_arxml_runnable_to_c(
            event["source_runnable"],
            result["runnables"],
        )

        if matched is None:
            print(f"{event['source_runnable']} -> C RUNNABLE NOT FOUND")
            continue

        dependencies = matched.get(
            "resolved_rte_dependencies",
            matched["rte_dependencies"],
        )

        expected_suffix = "_" + event["triggering_point"]

        rte_trigger = next(
            (
                dependency
                for dependency in dependencies
                if dependency.startswith("Rte_IrTrigger_")
                and dependency.endswith(expected_suffix)
            ),
            None,
        )

        if rte_trigger is None:
            rte_trigger = next(
                (
                    entry["rte_irtrigger"]
                    for entry in result["trigger_macros"]
                    if entry["rte_irtrigger"].endswith(expected_suffix)
                ),
                None,
            )

        if rte_trigger is None:
            print(
                f"{event['source_runnable']}"
                f" / {event['triggering_point']}"
                f" -> NOT FOUND"
            )
        else:
            print(
                f"{event['source_runnable']}"
                f" / {event['triggering_point']}"
                f" -> {rte_trigger}"
            )

    print("\n===== RTE PORT API VALIDATION =====")

    for entry in normalized_rte_reads:
        status = "FOUND" if entry["found_in_c"] else "NOT FOUND"

        print(
            f"READ  {entry['port']} / "
            f"{entry['data_element']} "
            f"-> {entry['symbol']} [{status}]"
        )

    for entry in normalized_rte_writes:
        status = "FOUND" if entry["found_in_c"] else "NOT FOUND"

        print(
            f"WRITE {entry['port']} / "
            f"{entry['data_element']} "
            f"-> {entry['symbol']} [{status}]"
        )

    missing_rte_apis = [
        entry["symbol"]
        for entry in (
            normalized_rte_reads
            + normalized_rte_writes
        )
        if not entry["found_in_c"]
    ]

    if missing_rte_apis:
        raise SystemExit(
            "ERROR: mandatory RTE API not found in generated C: "
            + ", ".join(missing_rte_apis)
        )
    
    if psl_rxindication_callback is not None:
        c_runnable_names = {
            runnable["name"]
            for runnable in result["runnables"]
        }

        if psl_rxindication_callback not in c_runnable_names:
            raise SystemExit(
                "ERROR: PSL RxIndication callback not found "
                "in generated C: "
                + psl_rxindication_callback
            )

    # --------------------------------------------------------------
    # Store ARXML scan result
    # --------------------------------------------------------------

    result["cdd_arxml"] = {
        "file": str(cdd_arxml),
        "namespace": arxml_namespace,
        "runnables": arxml_runnables,
        "r_ports": arxml_r_ports,
        "p_ports": arxml_p_ports,
        "normalized_rte_reads": normalized_rte_reads,
        "normalized_rte_writes": normalized_rte_writes,
        "timing_events": timing_events,
        "init_events": init_events,
        "data_received_events": data_received_events,
        "internal_trigger_events": internal_trigger_events,
    }

    data_received_model = []

    for event in data_received_events:
        matched = match_arxml_runnable_to_c(
            event["runnable"],
            result["runnables"],
        )

        matched_read = next(
            (
                entry
                for entry in normalized_rte_reads
                if entry["port"] == event["r_port"]
                and entry["data_element"] == event["data_element"]
            ),
            None,
        )

        if matched_read is None:
            raise SystemExit(
                "ERROR: DataReceivedEvent endpoint cannot be resolved: "
                f"{event['name']} "
                f"(r_port={event['r_port']}, "
                f"data_element={event['data_element']})"
            )

        data_received_model.append(
            {
                "event": event["name"],
                "arxml_runnable": event["runnable"],
                "c_runnable": matched["name"] if matched else None,
                "r_port": event["r_port"],
                "data_element": event["data_element"],
                "interface_ref": matched_read["interface_ref"],
                "rte_dependencies": (
                    matched["resolved_rte_dependencies"]
                    if matched else []
                ),
            }
    )
    
    timing_model = []

    for event in timing_events:
        matched = match_arxml_runnable_to_c(
            event["runnable"],
            result["runnables"],
        )

        timing_model.append(
            {
                "event": event["name"],
                "arxml_runnable": event["runnable"],
                "c_runnable": matched["name"] if matched else None,
                "offset": event["offset"],
                "period": event["period"],
                "rte_dependencies": (
                    matched["resolved_rte_dependencies"]
                    if matched else []
                ),
            }
        )

    init_model = []

    for event in init_events:
        matched = match_arxml_runnable_to_c(
            event["runnable"],
            result["runnables"],
        )

        init_model.append(
            {
                "event": event["name"],
                "arxml_runnable": event["runnable"],
                "c_runnable": matched["name"] if matched else None,
                "rte_dependencies": (
                    matched["resolved_rte_dependencies"]
                    if matched else []
                ),
            }
        )

    internal_trigger_model = []

    for event in internal_trigger_events:
        matched = match_arxml_runnable_to_c(
            event["source_runnable"],
            result["runnables"],
        )

        dependencies = (
            matched["resolved_rte_dependencies"]
            if matched else []
        )

        target_matched = match_arxml_runnable_to_c(
            event["target_runnable"],
            result["runnables"],
        )

        expected_suffix = "_" + event["triggering_point"]

        rte_trigger = next(
            (
                dependency
                for dependency in dependencies
                if dependency.startswith("Rte_IrTrigger_")
                and dependency.endswith(expected_suffix)
            ),
            None,
        )

        if rte_trigger is None:
            rte_trigger = next(
                (
                    entry["rte_irtrigger"]
                    for entry in result["trigger_macros"]
                    if entry["rte_irtrigger"].endswith(expected_suffix)
                ),
                None,
            )

        if rte_trigger is None:
            raise SystemExit(
                "ERROR: InternalTrigger RTE API cannot be resolved: "
                f"{event['name']} "
                f"(source={event['source_runnable']}, "
                f"point={event['triggering_point']})"
            )

        internal_trigger_model.append(
            {
                "event": event["name"],
                "source_runnable": event["source_runnable"],
                "source_c_runnable": matched["name"] if matched else None,
                "triggering_point": event["triggering_point"],
                "rte_trigger": rte_trigger,
                "target_runnable": event["target_runnable"],
                "target_c_runnable": (
                    target_matched["name"]
                    if target_matched else None
                ),
            }
        )

    rte_buffers = build_rte_buffer_model(
        normalized_rte_reads,
        normalized_rte_writes,
        aswc_receive_points,
        aswc_send_points,
    )

    result["intermediate_model"] = {
        "ports": {
            "reads": normalized_rte_reads,
            "writes": normalized_rte_writes,
        },
        "aswc": {
            "reads": aswc_receive_points,
            "writes": aswc_send_points,
        },
        "buffers": rte_buffers,
        "types": rte_data_types,
        "data_received": data_received_model,
        "timing": timing_model,
        "init": init_model,
        "internal_trigger": internal_trigger_model,
    }    

    print("===== RTE BUFFER MODEL =====")
    for entry in rte_buffers:
        print(entry)
    
    rte_ddscdd_type_source = generate_rte_ddscdd_type_source(
        rte_buffers,
        normalized_rte_reads,
        normalized_rte_writes,
        aswc_receive_points,
        aswc_send_points,
        data_received_model,
        internal_trigger_model,
    )

    ddscdd_task_source = generate_ddscdd_task_source(
        data_received_model,
        timing_model,
        init_model,
        internal_trigger_model,
    )

    print("===== GENERATED RTE SOURCE =====")
    print(rte_ddscdd_type_source)
    
    rte_ddscdd_type_header = generate_rte_ddscdd_type_header(
        normalized_rte_reads,
        normalized_rte_writes,
        aswc_receive_points,
        aswc_send_points,
        data_received_model,
        internal_trigger_model,
        psl_rxindication_callback,
    )

    virtual_aswc_header = generate_virtual_aswc_header()
    virtual_aswc_source = generate_virtual_aswc_source(
        aswc_receive_points,
        aswc_send_points,
    )

    print("\n===== CDD INIT EVENTS =====")

    for event in init_events:
        print(f"{event['name']}")
        print(f"  runnable : {event['runnable']}")

    print("\n===== CDD TIMING EVENTS =====")

    for event in timing_events:
        print(f"{event['name']}")
        print(f"  runnable : {event['runnable']}")
        print(f"  offset   : {event['offset']}")
        print(f"  period   : {event['period']}")
    
    print("\n===== CDD DATA RECEIVED EVENTS =====")

    for event in data_received_events:
        print(f"{event['name']}")
        print(f"  runnable     : {event['runnable']}")
        print(f"  r_port       : {event['r_port']}")
        print(f"  data_element : {event['data_element']}")
    
    print("\n===== CDD INTERNAL TRIGGER EVENTS =====")

    for event in internal_trigger_events:
        print(f"{event['name']}")
        print(f"  source runnable  : {event['source_runnable']}")
        print(f"  triggering point : {event['triggering_point']}")
        print(f"  target runnable  : {event['target_runnable']}")

    for category in [
        "rte_reads",
        "rte_writes",
        "rte_irtriggers",
        "rte_calls",
        "rte_irv_reads",
        "rte_irv_writes",
        "rte_modes",
    ]:
        seen = set()
        unique = []

        for entry in result[category]:
            if entry["symbol"] not in seen:
                seen.add(entry["symbol"])
                unique.append(entry)

        result[category] = unique

    args.output.parent.mkdir(parents=True, exist_ok=True)

    args.output.write_text(
        json.dumps(result, indent=2),
        encoding="utf-8",
    )

    if args.rte_output_dir is not None:
        args.rte_output_dir.mkdir(
            parents=True,
            exist_ok=True,
        )

        generated_rte_type = (
            args.rte_output_dir / "Rte_Type.h"
        )

        generated_rte_type.write_text(
            rte_type_header,
            encoding="utf-8",
        )
    
        generated_rte_ddscdd_type = (
            args.rte_output_dir / "Rte_DdsCddType.h"
        )

        generated_rte_ddscdd_type.write_text(
            rte_ddscdd_type_header,
            encoding="utf-8",
        )

        generated_rte_ddscdd_source = (
            args.rte_output_dir / "Rte_DdsCddType.c"
        )

        generated_rte_ddscdd_source.write_text(
            rte_ddscdd_type_source,
            encoding="utf-8",
        )

        generated_ddscdd_task_source = (
            args.rte_output_dir / "DdsCdd_Task.c"
        )

        generated_ddscdd_task_source.write_text(
            ddscdd_task_source,
            encoding="utf-8",
        )

        generated_virtual_aswc_header = (
            args.rte_output_dir / "VirtualAswc.h"
        )

        generated_virtual_aswc_header.write_text(
            virtual_aswc_header,
            encoding="utf-8",
        )

        generated_virtual_aswc_source = (
            args.rte_output_dir / "VirtualAswc.c"
        )

        generated_virtual_aswc_source.write_text(
            virtual_aswc_source,
            encoding="utf-8",
        )

    print("===== DdsCdd RTE Scanner =====")
    print(f"Source : {args.source_dir}")
    print(f"Files  : {len(files)}")
    print(f"CDD ARXML : {cdd_arxml}")
    print(f"ARXML NS  : {arxml_namespace}")
    print()

    for category in [
        "rte_reads",
        "rte_writes",
        "rte_irtriggers",
        "rte_calls",
        "rte_irv_reads",
        "rte_irv_writes",
        "rte_modes",
    ]:
        entries = result[category]

        print(f"{category}: {len(entries)}")

        for entry in entries:
            print(
                f"  {entry['symbol']} "
                f"({entry['file']}:{entry['line']})"
            )

    print()
    print(f"runnables: {len(result['runnables'])}")

    for runnable in result["runnables"]:
        print(
            f"  {runnable['name']} "
            f"({runnable['file']}:{runnable['line']})"
        )

        for dependency in runnable["rte_dependencies"]:
            print(f"    -> {dependency}")

    print()
    print(f"JSON: {args.output}")


if __name__ == "__main__":
    main()
