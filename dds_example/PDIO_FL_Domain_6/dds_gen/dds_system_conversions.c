/*
  WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

  This file was generated from C:\Users\jpark\Documents\rti_workspace\svc-autosar-patch\projects\test\user_work\dds_system.xml
  using RTI Connext AUTOSAR Runtime CDD Code Generator version 4.0.0.0 (build BUILD_4.0.0.0_20251016T000000Z_RTI_REL, commit unknown, expat 2.7.1).
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

/* /Cabin_Seat_PSUIO_DRV_t */
/* void Cabin_Seat_PSUIO_DRV_t_dds_to_rte(const dds_Cabin_Seat_PSUIO_DRV_t* src, Cabin_Seat_PSUIO_DRV_t* dst) */
/* { */
/*     StdTypes_uint16_dds_to_rte(&src->Drive_Slide_CurrentPosition, &dst->Drive_Slide_CurrentPosition); */
/*     StdTypes_uint16_dds_to_rte(&src->Drive_Recline_CurrentPosition, &dst->Drive_Recline_CurrentPosition); */
/*     StdTypes_uint16_dds_to_rte(&src->Drive_Height_CurrentPosition, &dst->Drive_Height_CurrentPosition); */
/*     StdTypes_uint16_dds_to_rte(&src->Drive_Tilt_CurrentPosition, &dst->Drive_Tilt_CurrentPosition); */
/*     StdTypes_uint16_dds_to_rte(&src->Drive_RelaxTilt_CurrentPosition, &dst->Drive_RelaxTilt_CurrentPosition); */
/*     StdTypes_uint16_dds_to_rte(&src->Drive_Legrest_CurrentPosition, &dst->Drive_Legrest_CurrentPosition); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Seat_MotorIntegratedMove_FeedbackInitial, &dst->Drive_Seat_MotorIntegratedMove_FeedbackInitial); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Slide_VirtualLimitReach_State, &dst->Drive_Slide_VirtualLimitReach_State); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Recline_VirtualLimitReach_State, &dst->Drive_Recline_VirtualLimitReach_State); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Tilt_VirtualLimitReach_State, &dst->Drive_Tilt_VirtualLimitReach_State); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_RelaxTilt_VirtualLimitReach_State, &dst->Drive_RelaxTilt_VirtualLimitReach_State); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Height_VirtualLimitReach_State, &dst->Drive_Height_VirtualLimitReach_State); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Legrest_VirtualLimitReach_State, &dst->Drive_Legrest_VirtualLimitReach_State); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Slide_Sensor_ErrorState, &dst->Drive_Slide_Sensor_ErrorState); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Recline_Sensor_ErrorState, &dst->Drive_Recline_Sensor_ErrorState); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Tilt_Sensor_ErrorState, &dst->Drive_Tilt_Sensor_ErrorState); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_RelaxTilt_Sensor_ErrorState, &dst->Drive_RelaxTilt_Sensor_ErrorState); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Height_Sensor_ErrorState, &dst->Drive_Height_Sensor_ErrorState); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Legrest_Sensor_ErrorState, &dst->Drive_Legrest_Sensor_ErrorState); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Slide_EndLimit_ReachState, &dst->Drive_Slide_EndLimit_ReachState); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Recline_EndLimit_ReachState, &dst->Drive_Recline_EndLimit_ReachState); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Tilt_EndLimit_ReachState, &dst->Drive_Tilt_EndLimit_ReachState); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_RlxTilt_EndLimit_ReachState, &dst->Drive_RlxTilt_EndLimit_ReachState); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Height_EndLimit_ReachState, &dst->Drive_Height_EndLimit_ReachState); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Legrest_EndLimit_ReachState, &dst->Drive_Legrest_EndLimit_ReachState); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_UnitAppliedOption, &dst->Drive_UnitAppliedOption); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_AllSeat_Motor_FailState, &dst->Drive_AllSeat_Motor_FailState); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Slide_MotorMove_State, &dst->Drive_Slide_MotorMove_State); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Recline_MotorMove_State, &dst->Drive_Recline_MotorMove_State); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Tilt_MotorMove_State, &dst->Drive_Tilt_MotorMove_State); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_RelaxTilt_MotorMove_State, &dst->Drive_RelaxTilt_MotorMove_State); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Height_MotorMove_State, &dst->Drive_Height_MotorMove_State); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Legrest_MotorMove_State, &dst->Drive_Legrest_MotorMove_State); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Slide_MotorMove_StateInitial, &dst->Drive_Slide_MotorMove_StateInitial); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Recline_MotorMove_StateInitial, &dst->Drive_Recline_MotorMove_StateInitial); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Tilt_MotorMove_StateInitial, &dst->Drive_Tilt_MotorMove_StateInitial); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_RelaxTilt_MotorMove_StateInitial, &dst->Drive_RelaxTilt_MotorMove_StateInitial); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Height_MotorMove_StateInitial, &dst->Drive_Height_MotorMove_StateInitial); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Legrest_MotorMove_StateInitial, &dst->Drive_Legrest_MotorMove_StateInitial); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Slide_MotorVirtualLimitSet_State, &dst->Drive_Slide_MotorVirtualLimitSet_State); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Recline_MotorVirtualLimitSet_State, &dst->Drive_Recline_MotorVirtualLimitSet_State); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Tilt_MotorVirtualLimitSet_State, &dst->Drive_Tilt_MotorVirtualLimitSet_State); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_RelaxTilt_MotorVirtualLimitSet_State, &dst->Drive_RelaxTilt_MotorVirtualLimitSet_State); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Height_MotorVirtualLimitSet_State, &dst->Drive_Height_MotorVirtualLimitSet_State); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Legrest_MotorVirtualLimitSet_State, &dst->Drive_Legrest_MotorVirtualLimitSet_State); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Seat_EasyAccess_Option, &dst->Drive_Seat_EasyAccess_Option); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Slide_ForwardMotor_Output, &dst->Drive_Slide_ForwardMotor_Output); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Slide_BackwardMotor_Output, &dst->Drive_Slide_BackwardMotor_Output); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Recline_ForwardMotor_Output, &dst->Drive_Recline_ForwardMotor_Output); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Recline_BackwardMotor_Output, &dst->Drive_Recline_BackwardMotor_Output); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Tilt_ForwardMotor_Output, &dst->Drive_Tilt_ForwardMotor_Output); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Tilt_BackwardMotor_Output, &dst->Drive_Tilt_BackwardMotor_Output); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_RlxTilt_ForwardMotor_Output, &dst->Drive_RlxTilt_ForwardMotor_Output); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_RlxTilt_BackwardMotor_Output, &dst->Drive_RlxTilt_BackwardMotor_Output); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Height_ForwardMotor_Output, &dst->Drive_Height_ForwardMotor_Output); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Height_BackwardMotor_Output, &dst->Drive_Height_BackwardMotor_Output); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Legrest_ForwardMotor_Output, &dst->Drive_Legrest_ForwardMotor_Output); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_Legrest_BackwardMotor_Output, &dst->Drive_Legrest_BackwardMotor_Output); */
/*     StdTypes_uint8_dds_to_rte(&src->DPSS_StSldFwdMvBtn_PSUIO_DRV, &dst->DPSS_StSldFwdMvBtn_PSUIO_DRV); */
/*     StdTypes_uint8_dds_to_rte(&src->DPSS_StSldBwdMvBtn_PSUIO_DRV, &dst->DPSS_StSldBwdMvBtn_PSUIO_DRV); */
/*     StdTypes_uint8_dds_to_rte(&src->DPSS_StRclFwdMvBtn_PSUIO_DRV, &dst->DPSS_StRclFwdMvBtn_PSUIO_DRV); */
/*     StdTypes_uint8_dds_to_rte(&src->DPSS_StRclBwdMvBtn_PSUIO_DRV, &dst->DPSS_StRclBwdMvBtn_PSUIO_DRV); */
/*     StdTypes_uint8_dds_to_rte(&src->DPSS_StTltUpMvBtn_PSUIO_DRV, &dst->DPSS_StTltUpMvBtn_PSUIO_DRV); */
/*     StdTypes_uint8_dds_to_rte(&src->DPSS_StTltDnMvBtn_PSUIO_DRV, &dst->DPSS_StTltDnMvBtn_PSUIO_DRV); */
/*     StdTypes_uint8_dds_to_rte(&src->DPSS_StRlxTltUpMvBtn_PSUIO_DRV, &dst->DPSS_StRlxTltUpMvBtn_PSUIO_DRV); */
/*     StdTypes_uint8_dds_to_rte(&src->DPSS_StRlxTltDnMvBtn_PSUIO_DRV, &dst->DPSS_StRlxTltDnMvBtn_PSUIO_DRV); */
/*     StdTypes_uint8_dds_to_rte(&src->DPSS_StHgtUpMvBtn_PSUIO_DRV, &dst->DPSS_StHgtUpMvBtn_PSUIO_DRV); */
/*     StdTypes_uint8_dds_to_rte(&src->DPSS_StHgtDnMvBtn_PSUIO_DRV, &dst->DPSS_StHgtDnMvBtn_PSUIO_DRV); */
/*     StdTypes_uint8_dds_to_rte(&src->DPSS_StLegUpMvBtn_PSUIO_DRV, &dst->DPSS_StLegUpMvBtn_PSUIO_DRV); */
/*     StdTypes_uint8_dds_to_rte(&src->DPSS_StLegDnMvBtn_PSUIO_DRV, &dst->DPSS_StLegDnMvBtn_PSUIO_DRV); */
/*     StdTypes_uint8_dds_to_rte(&src->DPSS_StRlxModeBtn_PSUIO_DRV, &dst->DPSS_StRlxModeBtn_PSUIO_DRV); */
/*     StdTypes_uint8_dds_to_rte(&src->DPSS_StRlxReturnBtn_PSUIO_DRV, &dst->DPSS_StRlxReturnBtn_PSUIO_DRV); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_PSU_Slide_Fail_State_PSUIO_DRV, &dst->Drive_PSU_Slide_Fail_State_PSUIO_DRV); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_PSU_Recline_Fail_State_PSUIO_DRV, &dst->Drive_PSU_Recline_Fail_State_PSUIO_DRV); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_PSU_Tilt_Fail_State_PSUIO_DRV, &dst->Drive_PSU_Tilt_Fail_State_PSUIO_DRV); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_PSU_RlxTilt_Fail_State_PSUIO_DRV, &dst->Drive_PSU_RlxTilt_Fail_State_PSUIO_DRV); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_PSU_Height_Fail_State_PSUIO_DRV, &dst->Drive_PSU_Height_Fail_State_PSUIO_DRV); */
/*     StdTypes_uint8_dds_to_rte(&src->Drive_PSU_Legrest_Fail_State_PSUIO_DRV, &dst->Drive_PSU_Legrest_Fail_State_PSUIO_DRV); */
/*     StdTypes_uint8_dds_to_rte(&src->PSUIO_DRV_SleepReady, &dst->PSUIO_DRV_SleepReady); */
/*  */
/* } */
/*  */
/* void Cabin_Seat_PSUIO_DRV_t_rte_to_dds(const Cabin_Seat_PSUIO_DRV_t* src, dds_Cabin_Seat_PSUIO_DRV_t* dst) */
/* { */
/*     StdTypes_uint16_rte_to_dds(&src->Drive_Slide_CurrentPosition, &dst->Drive_Slide_CurrentPosition); */
/*     StdTypes_uint16_rte_to_dds(&src->Drive_Recline_CurrentPosition, &dst->Drive_Recline_CurrentPosition); */
/*     StdTypes_uint16_rte_to_dds(&src->Drive_Height_CurrentPosition, &dst->Drive_Height_CurrentPosition); */
/*     StdTypes_uint16_rte_to_dds(&src->Drive_Tilt_CurrentPosition, &dst->Drive_Tilt_CurrentPosition); */
/*     StdTypes_uint16_rte_to_dds(&src->Drive_RelaxTilt_CurrentPosition, &dst->Drive_RelaxTilt_CurrentPosition); */
/*     StdTypes_uint16_rte_to_dds(&src->Drive_Legrest_CurrentPosition, &dst->Drive_Legrest_CurrentPosition); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Seat_MotorIntegratedMove_FeedbackInitial, &dst->Drive_Seat_MotorIntegratedMove_FeedbackInitial); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Slide_VirtualLimitReach_State, &dst->Drive_Slide_VirtualLimitReach_State); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Recline_VirtualLimitReach_State, &dst->Drive_Recline_VirtualLimitReach_State); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Tilt_VirtualLimitReach_State, &dst->Drive_Tilt_VirtualLimitReach_State); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_RelaxTilt_VirtualLimitReach_State, &dst->Drive_RelaxTilt_VirtualLimitReach_State); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Height_VirtualLimitReach_State, &dst->Drive_Height_VirtualLimitReach_State); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Legrest_VirtualLimitReach_State, &dst->Drive_Legrest_VirtualLimitReach_State); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Slide_Sensor_ErrorState, &dst->Drive_Slide_Sensor_ErrorState); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Recline_Sensor_ErrorState, &dst->Drive_Recline_Sensor_ErrorState); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Tilt_Sensor_ErrorState, &dst->Drive_Tilt_Sensor_ErrorState); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_RelaxTilt_Sensor_ErrorState, &dst->Drive_RelaxTilt_Sensor_ErrorState); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Height_Sensor_ErrorState, &dst->Drive_Height_Sensor_ErrorState); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Legrest_Sensor_ErrorState, &dst->Drive_Legrest_Sensor_ErrorState); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Slide_EndLimit_ReachState, &dst->Drive_Slide_EndLimit_ReachState); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Recline_EndLimit_ReachState, &dst->Drive_Recline_EndLimit_ReachState); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Tilt_EndLimit_ReachState, &dst->Drive_Tilt_EndLimit_ReachState); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_RlxTilt_EndLimit_ReachState, &dst->Drive_RlxTilt_EndLimit_ReachState); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Height_EndLimit_ReachState, &dst->Drive_Height_EndLimit_ReachState); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Legrest_EndLimit_ReachState, &dst->Drive_Legrest_EndLimit_ReachState); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_UnitAppliedOption, &dst->Drive_UnitAppliedOption); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_AllSeat_Motor_FailState, &dst->Drive_AllSeat_Motor_FailState); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Slide_MotorMove_State, &dst->Drive_Slide_MotorMove_State); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Recline_MotorMove_State, &dst->Drive_Recline_MotorMove_State); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Tilt_MotorMove_State, &dst->Drive_Tilt_MotorMove_State); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_RelaxTilt_MotorMove_State, &dst->Drive_RelaxTilt_MotorMove_State); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Height_MotorMove_State, &dst->Drive_Height_MotorMove_State); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Legrest_MotorMove_State, &dst->Drive_Legrest_MotorMove_State); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Slide_MotorMove_StateInitial, &dst->Drive_Slide_MotorMove_StateInitial); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Recline_MotorMove_StateInitial, &dst->Drive_Recline_MotorMove_StateInitial); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Tilt_MotorMove_StateInitial, &dst->Drive_Tilt_MotorMove_StateInitial); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_RelaxTilt_MotorMove_StateInitial, &dst->Drive_RelaxTilt_MotorMove_StateInitial); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Height_MotorMove_StateInitial, &dst->Drive_Height_MotorMove_StateInitial); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Legrest_MotorMove_StateInitial, &dst->Drive_Legrest_MotorMove_StateInitial); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Slide_MotorVirtualLimitSet_State, &dst->Drive_Slide_MotorVirtualLimitSet_State); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Recline_MotorVirtualLimitSet_State, &dst->Drive_Recline_MotorVirtualLimitSet_State); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Tilt_MotorVirtualLimitSet_State, &dst->Drive_Tilt_MotorVirtualLimitSet_State); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_RelaxTilt_MotorVirtualLimitSet_State, &dst->Drive_RelaxTilt_MotorVirtualLimitSet_State); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Height_MotorVirtualLimitSet_State, &dst->Drive_Height_MotorVirtualLimitSet_State); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Legrest_MotorVirtualLimitSet_State, &dst->Drive_Legrest_MotorVirtualLimitSet_State); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Seat_EasyAccess_Option, &dst->Drive_Seat_EasyAccess_Option); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Slide_ForwardMotor_Output, &dst->Drive_Slide_ForwardMotor_Output); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Slide_BackwardMotor_Output, &dst->Drive_Slide_BackwardMotor_Output); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Recline_ForwardMotor_Output, &dst->Drive_Recline_ForwardMotor_Output); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Recline_BackwardMotor_Output, &dst->Drive_Recline_BackwardMotor_Output); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Tilt_ForwardMotor_Output, &dst->Drive_Tilt_ForwardMotor_Output); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Tilt_BackwardMotor_Output, &dst->Drive_Tilt_BackwardMotor_Output); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_RlxTilt_ForwardMotor_Output, &dst->Drive_RlxTilt_ForwardMotor_Output); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_RlxTilt_BackwardMotor_Output, &dst->Drive_RlxTilt_BackwardMotor_Output); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Height_ForwardMotor_Output, &dst->Drive_Height_ForwardMotor_Output); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Height_BackwardMotor_Output, &dst->Drive_Height_BackwardMotor_Output); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Legrest_ForwardMotor_Output, &dst->Drive_Legrest_ForwardMotor_Output); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_Legrest_BackwardMotor_Output, &dst->Drive_Legrest_BackwardMotor_Output); */
/*     StdTypes_uint8_rte_to_dds(&src->DPSS_StSldFwdMvBtn_PSUIO_DRV, &dst->DPSS_StSldFwdMvBtn_PSUIO_DRV); */
/*     StdTypes_uint8_rte_to_dds(&src->DPSS_StSldBwdMvBtn_PSUIO_DRV, &dst->DPSS_StSldBwdMvBtn_PSUIO_DRV); */
/*     StdTypes_uint8_rte_to_dds(&src->DPSS_StRclFwdMvBtn_PSUIO_DRV, &dst->DPSS_StRclFwdMvBtn_PSUIO_DRV); */
/*     StdTypes_uint8_rte_to_dds(&src->DPSS_StRclBwdMvBtn_PSUIO_DRV, &dst->DPSS_StRclBwdMvBtn_PSUIO_DRV); */
/*     StdTypes_uint8_rte_to_dds(&src->DPSS_StTltUpMvBtn_PSUIO_DRV, &dst->DPSS_StTltUpMvBtn_PSUIO_DRV); */
/*     StdTypes_uint8_rte_to_dds(&src->DPSS_StTltDnMvBtn_PSUIO_DRV, &dst->DPSS_StTltDnMvBtn_PSUIO_DRV); */
/*     StdTypes_uint8_rte_to_dds(&src->DPSS_StRlxTltUpMvBtn_PSUIO_DRV, &dst->DPSS_StRlxTltUpMvBtn_PSUIO_DRV); */
/*     StdTypes_uint8_rte_to_dds(&src->DPSS_StRlxTltDnMvBtn_PSUIO_DRV, &dst->DPSS_StRlxTltDnMvBtn_PSUIO_DRV); */
/*     StdTypes_uint8_rte_to_dds(&src->DPSS_StHgtUpMvBtn_PSUIO_DRV, &dst->DPSS_StHgtUpMvBtn_PSUIO_DRV); */
/*     StdTypes_uint8_rte_to_dds(&src->DPSS_StHgtDnMvBtn_PSUIO_DRV, &dst->DPSS_StHgtDnMvBtn_PSUIO_DRV); */
/*     StdTypes_uint8_rte_to_dds(&src->DPSS_StLegUpMvBtn_PSUIO_DRV, &dst->DPSS_StLegUpMvBtn_PSUIO_DRV); */
/*     StdTypes_uint8_rte_to_dds(&src->DPSS_StLegDnMvBtn_PSUIO_DRV, &dst->DPSS_StLegDnMvBtn_PSUIO_DRV); */
/*     StdTypes_uint8_rte_to_dds(&src->DPSS_StRlxModeBtn_PSUIO_DRV, &dst->DPSS_StRlxModeBtn_PSUIO_DRV); */
/*     StdTypes_uint8_rte_to_dds(&src->DPSS_StRlxReturnBtn_PSUIO_DRV, &dst->DPSS_StRlxReturnBtn_PSUIO_DRV); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_PSU_Slide_Fail_State_PSUIO_DRV, &dst->Drive_PSU_Slide_Fail_State_PSUIO_DRV); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_PSU_Recline_Fail_State_PSUIO_DRV, &dst->Drive_PSU_Recline_Fail_State_PSUIO_DRV); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_PSU_Tilt_Fail_State_PSUIO_DRV, &dst->Drive_PSU_Tilt_Fail_State_PSUIO_DRV); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_PSU_RlxTilt_Fail_State_PSUIO_DRV, &dst->Drive_PSU_RlxTilt_Fail_State_PSUIO_DRV); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_PSU_Height_Fail_State_PSUIO_DRV, &dst->Drive_PSU_Height_Fail_State_PSUIO_DRV); */
/*     StdTypes_uint8_rte_to_dds(&src->Drive_PSU_Legrest_Fail_State_PSUIO_DRV, &dst->Drive_PSU_Legrest_Fail_State_PSUIO_DRV); */
/*     StdTypes_uint8_rte_to_dds(&src->PSUIO_DRV_SleepReady, &dst->PSUIO_DRV_SleepReady); */
/*  */
/* } */
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

/* /GCS_LEFT_2_PSUIO_DRV_t */
/* void GCS_LEFT_2_PSUIO_DRV_t_dds_to_rte(const dds_GCS_LEFT_2_PSUIO_DRV_t* src, GCS_LEFT_2_PSUIO_DRV_t* dst) */
/* { */
/*     StdTypes_uint8_dds_to_rte(&src->PSeat_DrvInitializationPlayCmd_PSUIO_DRV, &dst->PSeat_DrvInitializationPlayCmd_PSUIO_DRV); */
/*     StdTypes_uint8_dds_to_rte(&src->PSeat_DrvSlideManualPlayCmd_PSUIO_DRV, &dst->PSeat_DrvSlideManualPlayCmd_PSUIO_DRV); */
/*     StdTypes_uint8_dds_to_rte(&src->PSeat_DrvReclineManualPlayCmd_PSUIO_DRV, &dst->PSeat_DrvReclineManualPlayCmd_PSUIO_DRV); */
/*     StdTypes_uint8_dds_to_rte(&src->PSeat_DrvTiltManualPlayCmd_PSUIO_DRV, &dst->PSeat_DrvTiltManualPlayCmd_PSUIO_DRV); */
/*     StdTypes_uint8_dds_to_rte(&src->PSeat_DrvRlxTiltManualPlayCmd_PSUIO_DRV, &dst->PSeat_DrvRlxTiltManualPlayCmd_PSUIO_DRV); */
/*     StdTypes_uint8_dds_to_rte(&src->PSeat_DrvHeightManualPlayCmd_PSUIO_DRV, &dst->PSeat_DrvHeightManualPlayCmd_PSUIO_DRV); */
/*     StdTypes_uint8_dds_to_rte(&src->PSeat_DrvLegrestManualPlayCmd_PSUIO_DRV, &dst->PSeat_DrvLegrestManualPlayCmd_PSUIO_DRV); */
/*     StdTypes_uint8_dds_to_rte(&src->Pseat_DrvAutoCmdTargetPos_PSUIO_DRV, &dst->Pseat_DrvAutoCmdTargetPos_PSUIO_DRV); */
/*     StdTypes_uint8_dds_to_rte(&src->Pseat_DrvAutoCmdTargetPos_Percentage_PSUIO_DRV, &dst->Pseat_DrvAutoCmdTargetPos_Percentage_PSUIO_DRV); */
/*     StdTypes_uint16_dds_to_rte(&src->Driver_Recline_TargetPlayCmd_PSUIO_DRV, &dst->Driver_Recline_TargetPlayCmd_PSUIO_DRV); */
/*     StdTypes_uint16_dds_to_rte(&src->Driver_Slide_TargetPlayCmd_PSUIO_DRV, &dst->Driver_Slide_TargetPlayCmd_PSUIO_DRV); */
/*     StdTypes_uint16_dds_to_rte(&src->Driver_Tilt_TargetPlayCmd_PSUIO_DRV, &dst->Driver_Tilt_TargetPlayCmd_PSUIO_DRV); */
/*     StdTypes_uint16_dds_to_rte(&src->Driver_RlxTilt_TargetPlayCmd_PSUIO_DRV, &dst->Driver_RlxTilt_TargetPlayCmd_PSUIO_DRV); */
/*     StdTypes_uint16_dds_to_rte(&src->Driver_Height_TargetPlayCmd_PSUIO_DRV, &dst->Driver_Height_TargetPlayCmd_PSUIO_DRV); */
/*     StdTypes_uint16_dds_to_rte(&src->Driver_Legrest_TargetPlayCmd_PSUIO_DRV, &dst->Driver_Legrest_TargetPlayCmd_PSUIO_DRV); */
/*     StdTypes_uint8_dds_to_rte(&src->DriveTypeOption_PSUIO_DRV, &dst->DriveTypeOption_PSUIO_DRV); */
/*     StdTypes_uint8_dds_to_rte(&src->ICU_PowerAutoCutModSta_PSUIO_DRV, &dst->ICU_PowerAutoCutModSta_PSUIO_DRV); */
/*     StdTypes_uint8_dds_to_rte(&src->SleepRequestTo_PSUIO_DRV, &dst->SleepRequestTo_PSUIO_DRV); */
/*     StdTypes_uint8_dds_to_rte(&src->VehicePowerState_PSUIO_DRV, &dst->VehicePowerState_PSUIO_DRV); */
/*  */
/* } */
/*  */
/* void GCS_LEFT_2_PSUIO_DRV_t_rte_to_dds(const GCS_LEFT_2_PSUIO_DRV_t* src, dds_GCS_LEFT_2_PSUIO_DRV_t* dst) */
/* { */
/*     StdTypes_uint8_rte_to_dds(&src->PSeat_DrvInitializationPlayCmd_PSUIO_DRV, &dst->PSeat_DrvInitializationPlayCmd_PSUIO_DRV); */
/*     StdTypes_uint8_rte_to_dds(&src->PSeat_DrvSlideManualPlayCmd_PSUIO_DRV, &dst->PSeat_DrvSlideManualPlayCmd_PSUIO_DRV); */
/*     StdTypes_uint8_rte_to_dds(&src->PSeat_DrvReclineManualPlayCmd_PSUIO_DRV, &dst->PSeat_DrvReclineManualPlayCmd_PSUIO_DRV); */
/*     StdTypes_uint8_rte_to_dds(&src->PSeat_DrvTiltManualPlayCmd_PSUIO_DRV, &dst->PSeat_DrvTiltManualPlayCmd_PSUIO_DRV); */
/*     StdTypes_uint8_rte_to_dds(&src->PSeat_DrvRlxTiltManualPlayCmd_PSUIO_DRV, &dst->PSeat_DrvRlxTiltManualPlayCmd_PSUIO_DRV); */
/*     StdTypes_uint8_rte_to_dds(&src->PSeat_DrvHeightManualPlayCmd_PSUIO_DRV, &dst->PSeat_DrvHeightManualPlayCmd_PSUIO_DRV); */
/*     StdTypes_uint8_rte_to_dds(&src->PSeat_DrvLegrestManualPlayCmd_PSUIO_DRV, &dst->PSeat_DrvLegrestManualPlayCmd_PSUIO_DRV); */
/*     StdTypes_uint8_rte_to_dds(&src->Pseat_DrvAutoCmdTargetPos_PSUIO_DRV, &dst->Pseat_DrvAutoCmdTargetPos_PSUIO_DRV); */
/*     StdTypes_uint8_rte_to_dds(&src->Pseat_DrvAutoCmdTargetPos_Percentage_PSUIO_DRV, &dst->Pseat_DrvAutoCmdTargetPos_Percentage_PSUIO_DRV); */
/*     StdTypes_uint16_rte_to_dds(&src->Driver_Recline_TargetPlayCmd_PSUIO_DRV, &dst->Driver_Recline_TargetPlayCmd_PSUIO_DRV); */
/*     StdTypes_uint16_rte_to_dds(&src->Driver_Slide_TargetPlayCmd_PSUIO_DRV, &dst->Driver_Slide_TargetPlayCmd_PSUIO_DRV); */
/*     StdTypes_uint16_rte_to_dds(&src->Driver_Tilt_TargetPlayCmd_PSUIO_DRV, &dst->Driver_Tilt_TargetPlayCmd_PSUIO_DRV); */
/*     StdTypes_uint16_rte_to_dds(&src->Driver_RlxTilt_TargetPlayCmd_PSUIO_DRV, &dst->Driver_RlxTilt_TargetPlayCmd_PSUIO_DRV); */
/*     StdTypes_uint16_rte_to_dds(&src->Driver_Height_TargetPlayCmd_PSUIO_DRV, &dst->Driver_Height_TargetPlayCmd_PSUIO_DRV); */
/*     StdTypes_uint16_rte_to_dds(&src->Driver_Legrest_TargetPlayCmd_PSUIO_DRV, &dst->Driver_Legrest_TargetPlayCmd_PSUIO_DRV); */
/*     StdTypes_uint8_rte_to_dds(&src->DriveTypeOption_PSUIO_DRV, &dst->DriveTypeOption_PSUIO_DRV); */
/*     StdTypes_uint8_rte_to_dds(&src->ICU_PowerAutoCutModSta_PSUIO_DRV, &dst->ICU_PowerAutoCutModSta_PSUIO_DRV); */
/*     StdTypes_uint8_rte_to_dds(&src->SleepRequestTo_PSUIO_DRV, &dst->SleepRequestTo_PSUIO_DRV); */
/*     StdTypes_uint8_rte_to_dds(&src->VehicePowerState_PSUIO_DRV, &dst->VehicePowerState_PSUIO_DRV); */
/*  */
/* } */
