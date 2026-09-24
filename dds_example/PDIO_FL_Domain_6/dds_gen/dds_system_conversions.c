/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from C:\Users\jpark\Documents\rti_workspace\svc-autosar-patch\projects\test\user_work\dds_system.xml
  using RTI Connext AUTOSAR Runtime CDD Code Generator version 4.0.1.1 (build BUILD_4.0.1.1_20260916T000000Z_RTI_REL, commit unknown, expat 2.8.2).
  RTI Connext AUTOSAR Runtime CDD Code Generator is part of the RTI Connext DDS distribution.
  For more information, consult RTI Connext AUTOSAR Runtime CDD Code Generator User's Manual.
*/

#include "dds_system_conversions.h"


/* /Cabin_Door_PDIO_FL_t */
void Cabin_Door_PDIO_FL_t_dds_to_rte(const dds_Cabin_Door_PDIO_FL_t* src, Cabin_Door_PDIO_FL_t* dst)
{
    StdTypes_uint8_dds_to_rte(&src->PDIO_FL_Driver_Door_Switch_State, &dst->PDIO_FL_Driver_Door_Switch_State);
    StdTypes_uint8_dds_to_rte(&src->PDIO_FL_Driver_Door_Unlock_State, &dst->PDIO_FL_Driver_Door_Unlock_State);
    StdTypes_uint8_dds_to_rte(&src->PDIO_FL_PwrDrAvailability, &dst->PDIO_FL_PwrDrAvailability);
    StdTypes_float_dds_to_rte(&src->PDIO_FL_PwrDrAngle, &dst->PDIO_FL_PwrDrAngle);
    StdTypes_uint8_dds_to_rte(&src->PDIO_FL_PwrDrStatus, &dst->PDIO_FL_PwrDrStatus);
    StdTypes_uint8_dds_to_rte(&src->PDIO_FL_PwrDrSwingActrStatus, &dst->PDIO_FL_PwrDrSwingActrStatus);
    StdTypes_uint8_dds_to_rte(&src->PDIO_FL_PwrDrErrorState, &dst->PDIO_FL_PwrDrErrorState);
    StdTypes_uint8_dds_to_rte(&src->PDIO_FL_PwrDrAntiPinchStatus, &dst->PDIO_FL_PwrDrAntiPinchStatus);
    StdTypes_float_dds_to_rte(&src->PDIO_FL_PwrDrAngleSpeed, &dst->PDIO_FL_PwrDrAngleSpeed);
    StdTypes_uint8_dds_to_rte(&src->PDIO_FL_InsdOpnClsSwStatus, &dst->PDIO_FL_InsdOpnClsSwStatus);
    StdTypes_uint8_dds_to_rte(&src->PDIO_FL_OtsdOpnClsSwStatus, &dst->PDIO_FL_OtsdOpnClsSwStatus);
    StdTypes_uint8_dds_to_rte(&src->PDIO_FL_SleepReady, &dst->PDIO_FL_SleepReady);
    StdTypes_uint8_dds_to_rte(&src->PDIO_FL_WakeupRequest, &dst->PDIO_FL_WakeupRequest);
    StdTypes_uint8_dds_to_rte(&src->PDIO_FL_CinchingStatus, &dst->PDIO_FL_CinchingStatus);
    StdTypes_uint8_dds_to_rte(&src->PDIO_FL_ActiveHoldingState, &dst->PDIO_FL_ActiveHoldingState);

}

void Cabin_Door_PDIO_FL_t_rte_to_dds(const Cabin_Door_PDIO_FL_t* src, dds_Cabin_Door_PDIO_FL_t* dst)
{
    StdTypes_uint8_rte_to_dds(&src->PDIO_FL_Driver_Door_Switch_State, &dst->PDIO_FL_Driver_Door_Switch_State);
    StdTypes_uint8_rte_to_dds(&src->PDIO_FL_Driver_Door_Unlock_State, &dst->PDIO_FL_Driver_Door_Unlock_State);
    StdTypes_uint8_rte_to_dds(&src->PDIO_FL_PwrDrAvailability, &dst->PDIO_FL_PwrDrAvailability);
    StdTypes_float_rte_to_dds(&src->PDIO_FL_PwrDrAngle, &dst->PDIO_FL_PwrDrAngle);
    StdTypes_uint8_rte_to_dds(&src->PDIO_FL_PwrDrStatus, &dst->PDIO_FL_PwrDrStatus);
    StdTypes_uint8_rte_to_dds(&src->PDIO_FL_PwrDrSwingActrStatus, &dst->PDIO_FL_PwrDrSwingActrStatus);
    StdTypes_uint8_rte_to_dds(&src->PDIO_FL_PwrDrErrorState, &dst->PDIO_FL_PwrDrErrorState);
    StdTypes_uint8_rte_to_dds(&src->PDIO_FL_PwrDrAntiPinchStatus, &dst->PDIO_FL_PwrDrAntiPinchStatus);
    StdTypes_float_rte_to_dds(&src->PDIO_FL_PwrDrAngleSpeed, &dst->PDIO_FL_PwrDrAngleSpeed);
    StdTypes_uint8_rte_to_dds(&src->PDIO_FL_InsdOpnClsSwStatus, &dst->PDIO_FL_InsdOpnClsSwStatus);
    StdTypes_uint8_rte_to_dds(&src->PDIO_FL_OtsdOpnClsSwStatus, &dst->PDIO_FL_OtsdOpnClsSwStatus);
    StdTypes_uint8_rte_to_dds(&src->PDIO_FL_SleepReady, &dst->PDIO_FL_SleepReady);
    StdTypes_uint8_rte_to_dds(&src->PDIO_FL_WakeupRequest, &dst->PDIO_FL_WakeupRequest);
    StdTypes_uint8_rte_to_dds(&src->PDIO_FL_CinchingStatus, &dst->PDIO_FL_CinchingStatus);
    StdTypes_uint8_rte_to_dds(&src->PDIO_FL_ActiveHoldingState, &dst->PDIO_FL_ActiveHoldingState);

}

/* /GCS_LEFT_2_PDIO_FL_t */
void GCS_LEFT_2_PDIO_FL_t_dds_to_rte(const dds_GCS_LEFT_2_PDIO_FL_t* src, GCS_LEFT_2_PDIO_FL_t* dst)
{
    StdTypes_uint8_dds_to_rte(&src->PwrDrOpnClsCmd_PDIO_FL, &dst->PwrDrOpnClsCmd_PDIO_FL);
    StdTypes_uint8_dds_to_rte(&src->PwrDrSnsrStatus_RODS_FL_PDIO_FL, &dst->PwrDrSnsrStatus_RODS_FL_PDIO_FL);
    StdTypes_float_dds_to_rte(&src->PwrDrSnsrStopAngle_RODS_FL_PDIO_FL, &dst->PwrDrSnsrStopAngle_RODS_FL_PDIO_FL);
    StdTypes_uint8_dds_to_rte(&src->PwrDrSnsrStopRequest_RODS_FL_PDIO_FL, &dst->PwrDrSnsrStopRequest_RODS_FL_PDIO_FL);
    StdTypes_uint8_dds_to_rte(&src->ACU_CrshActvSta_PDIO_FL, &dst->ACU_CrshActvSta_PDIO_FL);
    StdTypes_uint16_dds_to_rte(&src->ACU_CrshTyp_PDIO_FL, &dst->ACU_CrshTyp_PDIO_FL);
    StdTypes_uint8_dds_to_rte(&src->Door_LockUnlockCmd_PDIO_FL, &dst->Door_LockUnlockCmd_PDIO_FL);
    StdTypes_uint8_dds_to_rte(&src->IMU_LatAccelSigSta_PDIO_FL, &dst->IMU_LatAccelSigSta_PDIO_FL);
    StdTypes_uint8_dds_to_rte(&src->IMU_LongAccelSigSta_PDIO_FL, &dst->IMU_LongAccelSigSta_PDIO_FL);
    StdTypes_float_dds_to_rte(&src->IMU_LatAccelVal_PDIO_FL, &dst->IMU_LatAccelVal_PDIO_FL);
    StdTypes_float_dds_to_rte(&src->IMU_LongAccelVal_PDIO_FL, &dst->IMU_LongAccelVal_PDIO_FL);
    StdTypes_uint16_dds_to_rte(&src->VehicleSpeedState_PDIO_FL, &dst->VehicleSpeedState_PDIO_FL);
    StdTypes_uint8_dds_to_rte(&src->VCU_GearPosSta_PDIO_FL, &dst->VCU_GearPosSta_PDIO_FL);
    StdTypes_float_dds_to_rte(&src->PwrDrOpnAngVal_PDIO_FL, &dst->PwrDrOpnAngVal_PDIO_FL);
    StdTypes_uint8_dds_to_rte(&src->SleepRequestTo_PDIO_FL, &dst->SleepRequestTo_PDIO_FL);
    StdTypes_uint8_dds_to_rte(&src->SleepCommandTo_PDIO_FL, &dst->SleepCommandTo_PDIO_FL);
    StdTypes_uint8_dds_to_rte(&src->VehiclePowerState_PDIO_FL, &dst->VehiclePowerState_PDIO_FL);

}

void GCS_LEFT_2_PDIO_FL_t_rte_to_dds(const GCS_LEFT_2_PDIO_FL_t* src, dds_GCS_LEFT_2_PDIO_FL_t* dst)
{
    StdTypes_uint8_rte_to_dds(&src->PwrDrOpnClsCmd_PDIO_FL, &dst->PwrDrOpnClsCmd_PDIO_FL);
    StdTypes_uint8_rte_to_dds(&src->PwrDrSnsrStatus_RODS_FL_PDIO_FL, &dst->PwrDrSnsrStatus_RODS_FL_PDIO_FL);
    StdTypes_float_rte_to_dds(&src->PwrDrSnsrStopAngle_RODS_FL_PDIO_FL, &dst->PwrDrSnsrStopAngle_RODS_FL_PDIO_FL);
    StdTypes_uint8_rte_to_dds(&src->PwrDrSnsrStopRequest_RODS_FL_PDIO_FL, &dst->PwrDrSnsrStopRequest_RODS_FL_PDIO_FL);
    StdTypes_uint8_rte_to_dds(&src->ACU_CrshActvSta_PDIO_FL, &dst->ACU_CrshActvSta_PDIO_FL);
    StdTypes_uint16_rte_to_dds(&src->ACU_CrshTyp_PDIO_FL, &dst->ACU_CrshTyp_PDIO_FL);
    StdTypes_uint8_rte_to_dds(&src->Door_LockUnlockCmd_PDIO_FL, &dst->Door_LockUnlockCmd_PDIO_FL);
    StdTypes_uint8_rte_to_dds(&src->IMU_LatAccelSigSta_PDIO_FL, &dst->IMU_LatAccelSigSta_PDIO_FL);
    StdTypes_uint8_rte_to_dds(&src->IMU_LongAccelSigSta_PDIO_FL, &dst->IMU_LongAccelSigSta_PDIO_FL);
    StdTypes_float_rte_to_dds(&src->IMU_LatAccelVal_PDIO_FL, &dst->IMU_LatAccelVal_PDIO_FL);
    StdTypes_float_rte_to_dds(&src->IMU_LongAccelVal_PDIO_FL, &dst->IMU_LongAccelVal_PDIO_FL);
    StdTypes_uint16_rte_to_dds(&src->VehicleSpeedState_PDIO_FL, &dst->VehicleSpeedState_PDIO_FL);
    StdTypes_uint8_rte_to_dds(&src->VCU_GearPosSta_PDIO_FL, &dst->VCU_GearPosSta_PDIO_FL);
    StdTypes_float_rte_to_dds(&src->PwrDrOpnAngVal_PDIO_FL, &dst->PwrDrOpnAngVal_PDIO_FL);
    StdTypes_uint8_rte_to_dds(&src->SleepRequestTo_PDIO_FL, &dst->SleepRequestTo_PDIO_FL);
    StdTypes_uint8_rte_to_dds(&src->SleepCommandTo_PDIO_FL, &dst->SleepCommandTo_PDIO_FL);
    StdTypes_uint8_rte_to_dds(&src->VehiclePowerState_PDIO_FL, &dst->VehiclePowerState_PDIO_FL);

}

