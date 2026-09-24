/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from C:\Users\jpark\Documents\rti_workspace\svc-autosar-patch\projects\test\user_work\dds_system.xml
  using RTI Connext AUTOSAR Runtime CDD Code Generator version 4.0.1.1 (build BUILD_4.0.1.1_20260916T000000Z_RTI_REL, commit unknown, expat 2.8.2).
  RTI Connext AUTOSAR Runtime CDD Code Generator is part of the RTI Connext DDS distribution.
  For more information, consult RTI Connext AUTOSAR Runtime CDD Code Generator User's Manual.
*/

#ifndef __C__USERS_JPARK_DOCUMENTS_RTI_WORKSPACE_SVC_AUTOSAR_PATCH_PROJECTS_TEST__USER_WORK_DDS_SYSTEM_CONVERSIONS_H_H__
#define __C__USERS_JPARK_DOCUMENTS_RTI_WORKSPACE_SVC_AUTOSAR_PATCH_PROJECTS_TEST__USER_WORK_DDS_SYSTEM_CONVERSIONS_H_H__

#include "Rte_Type.h"
#include "dds_system_types.h"

/* /Cabin_Door_PDIO_FL_t */
void Cabin_Door_PDIO_FL_t_dds_to_rte(const dds_Cabin_Door_PDIO_FL_t* src, Cabin_Door_PDIO_FL_t* dst);
void Cabin_Door_PDIO_FL_t_rte_to_dds(const Cabin_Door_PDIO_FL_t* src, dds_Cabin_Door_PDIO_FL_t* dst);

/* /GCS_LEFT_2_PDIO_FL_t */
void GCS_LEFT_2_PDIO_FL_t_dds_to_rte(const dds_GCS_LEFT_2_PDIO_FL_t* src, GCS_LEFT_2_PDIO_FL_t* dst);
void GCS_LEFT_2_PDIO_FL_t_rte_to_dds(const GCS_LEFT_2_PDIO_FL_t* src, dds_GCS_LEFT_2_PDIO_FL_t* dst);

/* /StdTypes/float */
static void StdTypes_float_dds_to_rte(const DDS_Float* src, float* dst)
{
    *dst = (float)*src;

}

static void StdTypes_float_rte_to_dds(const float* src, DDS_Float* dst)
{
    *dst = (DDS_Float)*src;

}

/* /StdTypes/uint16 */
static void StdTypes_uint16_dds_to_rte(const DDS_UnsignedShort* src, uint16* dst)
{
    *dst = (uint16)*src;

}

static void StdTypes_uint16_rte_to_dds(const uint16* src, DDS_UnsignedShort* dst)
{
    *dst = (DDS_UnsignedShort)*src;

}

/* /StdTypes/uint8 */
static void StdTypes_uint8_dds_to_rte(const DDS_Octet* src, uint8* dst)
{
    *dst = (uint8)*src;

}

static void StdTypes_uint8_rte_to_dds(const uint8* src, DDS_Octet* dst)
{
    *dst = (DDS_Octet)*src;

}



#endif /* __C__USERS_JPARK_DOCUMENTS_RTI_WORKSPACE_SVC_AUTOSAR_PATCH_PROJECTS_TEST__USER_WORK_DDS_SYSTEM_CONVERSIONS_H_H__ */