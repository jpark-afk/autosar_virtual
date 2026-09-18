#!/usr/bin/env bash

export RTIMEHOME="${RTIMEHOME:-$HOME/dds/rti_connext_dds_micro-4.3.0_ER738}"

export RTI_PIL_LIB_DIR="$RTIMEHOME/lib/x86_64leElfgcc13.3.0"
export RTI_PIL_INCLUDE_DIR="$RTIMEHOME/include"

# Trampoline / GOIL
export TRAMPOLINE_HOME="$HOME/autosar_virtual/third_party/trampoline"
export GOIL="$TRAMPOLINE_HOME/goil/makefile-unix/goil"
export VIPER_PATH="$TRAMPOLINE_HOME/viper"
export GOIL_TEMPLATES="$TRAMPOLINE_HOME/goil/templates"
