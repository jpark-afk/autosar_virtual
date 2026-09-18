/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from C:\Users\jpark\Documents\rti_workspace\svc-autosar-patch\projects\test\user_work\dds_system.xml
  using RTI Connext AUTOSAR Runtime CDD Code Generator version 4.0.0.0 (build BUILD_4.0.0.0_20251016T000000Z_RTI_REL, commit unknown, expat 2.7.1).
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

/* /Cabin_Seat_PSUIO_DRV_t */
/* void Cabin_Seat_PSUIO_DRV_t_dds_to_rte(const dds_Cabin_Seat_PSUIO_DRV_t* src, Cabin_Seat_PSUIO_DRV_t* dst); */
/* void Cabin_Seat_PSUIO_DRV_t_rte_to_dds(const Cabin_Seat_PSUIO_DRV_t* src, dds_Cabin_Seat_PSUIO_DRV_t* dst); */
/* /GCS_LEFT_2_PDIO_FL_t */
void GCS_LEFT_2_PDIO_FL_t_dds_to_rte(const dds_GCS_LEFT_2_PDIO_FL_t* src, GCS_LEFT_2_PDIO_FL_t* dst);
void GCS_LEFT_2_PDIO_FL_t_rte_to_dds(const GCS_LEFT_2_PDIO_FL_t* src, dds_GCS_LEFT_2_PDIO_FL_t* dst);

/* /GCS_LEFT_2_PSUIO_DRV_t */
/* void GCS_LEFT_2_PSUIO_DRV_t_dds_to_rte(const dds_GCS_LEFT_2_PSUIO_DRV_t* src, GCS_LEFT_2_PSUIO_DRV_t* dst); */
/* void GCS_LEFT_2_PSUIO_DRV_t_rte_to_dds(const GCS_LEFT_2_PSUIO_DRV_t* src, dds_GCS_LEFT_2_PSUIO_DRV_t* dst); */
/* /StdTypes/boolean */
static void StdTypes_boolean_dds_to_rte(const DDS_Boolean* src, boolean* dst)
{
    *dst = (boolean)*src;

}

static void StdTypes_boolean_rte_to_dds(const boolean* src, DDS_Boolean* dst)
{
    *dst = (DDS_Boolean)*src;

}

/* /StdTypes/double */
static void StdTypes_double_dds_to_rte(const DDS_Double* src, double* dst)
{
    *dst = (double)*src;

}

static void StdTypes_double_rte_to_dds(const double* src, DDS_Double* dst)
{
    *dst = (DDS_Double)*src;

}

/* /StdTypes/float */
static void StdTypes_float_dds_to_rte(const DDS_Float* src, float* dst)
{
    *dst = (float)*src;

}

static void StdTypes_float_rte_to_dds(const float* src, DDS_Float* dst)
{
    *dst = (DDS_Float)*src;

}

/* /StdTypes/sint16 */
static void StdTypes_sint16_dds_to_rte(const DDS_Short* src, sint16* dst)
{
    *dst = (sint16)*src;

}

static void StdTypes_sint16_rte_to_dds(const sint16* src, DDS_Short* dst)
{
    *dst = (DDS_Short)*src;

}

/* /StdTypes/sint32 */
static void StdTypes_sint32_dds_to_rte(const DDS_Long* src, sint32* dst)
{
    *dst = (sint32)*src;

}

static void StdTypes_sint32_rte_to_dds(const sint32* src, DDS_Long* dst)
{
    *dst = (DDS_Long)*src;

}

/* /StdTypes/sint64 */
static void StdTypes_sint64_dds_to_rte(const DDS_LongLong* src, sint64* dst)
{
    *dst = (sint64)*src;

}

static void StdTypes_sint64_rte_to_dds(const sint64* src, DDS_LongLong* dst)
{
    *dst = (DDS_LongLong)*src;

}

/* /StdTypes/sint8 */
static void StdTypes_sint8_dds_to_rte(const DDS_Char* src, sint8* dst)
{
    *dst = (sint8)*src;

}

static void StdTypes_sint8_rte_to_dds(const sint8* src, DDS_Char* dst)
{
    *dst = (DDS_Char)*src;

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

/* /StdTypes/uint32 */
static void StdTypes_uint32_dds_to_rte(const DDS_UnsignedLong* src, uint32* dst)
{
    *dst = (uint32)*src;

}

static void StdTypes_uint32_rte_to_dds(const uint32* src, DDS_UnsignedLong* dst)
{
    *dst = (DDS_UnsignedLong)*src;

}

/* /StdTypes/uint64 */
static void StdTypes_uint64_dds_to_rte(const DDS_UnsignedLongLong* src, uint64* dst)
{
    *dst = (uint64)*src;

}

static void StdTypes_uint64_rte_to_dds(const uint64* src, DDS_UnsignedLongLong* dst)
{
    *dst = (DDS_UnsignedLongLong)*src;

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