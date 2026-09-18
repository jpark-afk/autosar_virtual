/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from dds_system_types.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#include "dds_system_types.h"

#ifndef UNUSED_ARG
#define UNUSED_ARG(x) (void)(x)
#endif

#if DDS_XTYPES_IS_ENABLED
#include "dds_c/dds_c_typecode.h"
#endif
#ifndef NDDS_STANDALONE_TYPE
#include "osapi/osapi_atomic.h"
#endif

/*** SOURCE_BEGIN ***/

/* ========================================================================= */

const char *dds_Cabin_Door_PDIO_FL_tTYPENAME = "dds::Cabin_Door_PDIO_FL_t";

RTI_BOOL
dds_Cabin_Door_PDIO_FL_t_initialize(dds_Cabin_Door_PDIO_FL_t* sample)
{
    if (sample == NULL)
    {
        return RTI_FALSE;
    }

    DDS_Primitive_init(&sample->PDIO_FL_Driver_Door_Switch_State);
    DDS_Primitive_init(&sample->PDIO_FL_Driver_Door_Unlock_State);
    DDS_Primitive_init(&sample->PDIO_FL_PwrDrAvailability);
    DDS_Primitive_init(&sample->PDIO_FL_PwrDrAngle);
    DDS_Primitive_init(&sample->PDIO_FL_PwrDrStatus);
    DDS_Primitive_init(&sample->PDIO_FL_PwrDrSwingActrStatus);
    DDS_Primitive_init(&sample->PDIO_FL_PwrDrErrorState);
    DDS_Primitive_init(&sample->PDIO_FL_PwrDrAntiPinchStatus);
    DDS_Primitive_init(&sample->PDIO_FL_PwrDrAngleSpeed);
    DDS_Primitive_init(&sample->PDIO_FL_InsdOpnClsSwStatus);
    DDS_Primitive_init(&sample->PDIO_FL_OtsdOpnClsSwStatus);
    DDS_Primitive_init(&sample->PDIO_FL_SleepReady);
    DDS_Primitive_init(&sample->PDIO_FL_WakeupRequest);
    DDS_Primitive_init(&sample->PDIO_FL_CinchingStatus);
    DDS_Primitive_init(&sample->PDIO_FL_ActiveHoldingState);
    return RTI_TRUE;
}

dds_Cabin_Door_PDIO_FL_t *
dds_Cabin_Door_PDIO_FL_t_create(void)
{
    dds_Cabin_Door_PDIO_FL_t* sample;
    OSAPI_Heap_allocate_struct(&sample, dds_Cabin_Door_PDIO_FL_t);
    if (sample != NULL)
    {
        if (!dds_Cabin_Door_PDIO_FL_t_initialize(sample))
        {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}

#ifndef RTI_CERT

RTI_BOOL
dds_Cabin_Door_PDIO_FL_t_finalize(dds_Cabin_Door_PDIO_FL_t* sample)
{
    if (sample == NULL)
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

#ifndef RTI_CERT
void
dds_Cabin_Door_PDIO_FL_t_delete(dds_Cabin_Door_PDIO_FL_t* sample)
{
    if (sample != NULL)
    {
        /* dds_Cabin_Door_PDIO_FL_t_finalize() always
        returns RTI_TRUE when called with sample != NULL */
        dds_Cabin_Door_PDIO_FL_t_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}
#endif
#endif

RTI_BOOL
dds_Cabin_Door_PDIO_FL_t_copy(dds_Cabin_Door_PDIO_FL_t* dst,const dds_Cabin_Door_PDIO_FL_t* src)
{
    if ((dst == NULL) || (src == NULL))
    {
        return RTI_FALSE;
    }
    DDS_Primitive_copy(&dst->PDIO_FL_Driver_Door_Switch_State, &src->PDIO_FL_Driver_Door_Switch_State);
    DDS_Primitive_copy(&dst->PDIO_FL_Driver_Door_Unlock_State, &src->PDIO_FL_Driver_Door_Unlock_State);
    DDS_Primitive_copy(&dst->PDIO_FL_PwrDrAvailability, &src->PDIO_FL_PwrDrAvailability);
    DDS_Primitive_copy(&dst->PDIO_FL_PwrDrAngle, &src->PDIO_FL_PwrDrAngle);
    DDS_Primitive_copy(&dst->PDIO_FL_PwrDrStatus, &src->PDIO_FL_PwrDrStatus);
    DDS_Primitive_copy(&dst->PDIO_FL_PwrDrSwingActrStatus, &src->PDIO_FL_PwrDrSwingActrStatus);
    DDS_Primitive_copy(&dst->PDIO_FL_PwrDrErrorState, &src->PDIO_FL_PwrDrErrorState);
    DDS_Primitive_copy(&dst->PDIO_FL_PwrDrAntiPinchStatus, &src->PDIO_FL_PwrDrAntiPinchStatus);
    DDS_Primitive_copy(&dst->PDIO_FL_PwrDrAngleSpeed, &src->PDIO_FL_PwrDrAngleSpeed);
    DDS_Primitive_copy(&dst->PDIO_FL_InsdOpnClsSwStatus, &src->PDIO_FL_InsdOpnClsSwStatus);
    DDS_Primitive_copy(&dst->PDIO_FL_OtsdOpnClsSwStatus, &src->PDIO_FL_OtsdOpnClsSwStatus);
    DDS_Primitive_copy(&dst->PDIO_FL_SleepReady, &src->PDIO_FL_SleepReady);
    DDS_Primitive_copy(&dst->PDIO_FL_WakeupRequest, &src->PDIO_FL_WakeupRequest);
    DDS_Primitive_copy(&dst->PDIO_FL_CinchingStatus, &src->PDIO_FL_CinchingStatus);
    DDS_Primitive_copy(&dst->PDIO_FL_ActiveHoldingState, &src->PDIO_FL_ActiveHoldingState);
    return RTI_TRUE;
}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'dds_Cabin_Door_PDIO_FL_t' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T dds_Cabin_Door_PDIO_FL_t
#define TSeq dds_Cabin_Door_PDIO_FL_tSeq
#define T_initialize dds_Cabin_Door_PDIO_FL_t_initialize
#define T_finalize   dds_Cabin_Door_PDIO_FL_t_finalize
#define T_copy       dds_Cabin_Door_PDIO_FL_t_copy
#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

/* ========================================================================= */

const char *dds_Cabin_Seat_PSUIO_DRV_tTYPENAME = "dds::Cabin_Seat_PSUIO_DRV_t";

RTI_BOOL
dds_Cabin_Seat_PSUIO_DRV_t_initialize(dds_Cabin_Seat_PSUIO_DRV_t* sample)
{
    if (sample == NULL)
    {
        return RTI_FALSE;
    }

    DDS_Primitive_init(&sample->Drive_Slide_CurrentPosition);
    DDS_Primitive_init(&sample->Drive_Recline_CurrentPosition);
    DDS_Primitive_init(&sample->Drive_Height_CurrentPosition);
    DDS_Primitive_init(&sample->Drive_Tilt_CurrentPosition);
    DDS_Primitive_init(&sample->Drive_RelaxTilt_CurrentPosition);
    DDS_Primitive_init(&sample->Drive_Legrest_CurrentPosition);
    DDS_Primitive_init(&sample->Drive_Seat_MotorIntegratedMove_FeedbackInitial);
    DDS_Primitive_init(&sample->Drive_Slide_VirtualLimitReach_State);
    DDS_Primitive_init(&sample->Drive_Recline_VirtualLimitReach_State);
    DDS_Primitive_init(&sample->Drive_Tilt_VirtualLimitReach_State);
    DDS_Primitive_init(&sample->Drive_RelaxTilt_VirtualLimitReach_State);
    DDS_Primitive_init(&sample->Drive_Height_VirtualLimitReach_State);
    DDS_Primitive_init(&sample->Drive_Legrest_VirtualLimitReach_State);
    DDS_Primitive_init(&sample->Drive_Slide_Sensor_ErrorState);
    DDS_Primitive_init(&sample->Drive_Recline_Sensor_ErrorState);
    DDS_Primitive_init(&sample->Drive_Tilt_Sensor_ErrorState);
    DDS_Primitive_init(&sample->Drive_RelaxTilt_Sensor_ErrorState);
    DDS_Primitive_init(&sample->Drive_Height_Sensor_ErrorState);
    DDS_Primitive_init(&sample->Drive_Legrest_Sensor_ErrorState);
    DDS_Primitive_init(&sample->Drive_Slide_EndLimit_ReachState);
    DDS_Primitive_init(&sample->Drive_Recline_EndLimit_ReachState);
    DDS_Primitive_init(&sample->Drive_Tilt_EndLimit_ReachState);
    DDS_Primitive_init(&sample->Drive_RlxTilt_EndLimit_ReachState);
    DDS_Primitive_init(&sample->Drive_Height_EndLimit_ReachState);
    DDS_Primitive_init(&sample->Drive_Legrest_EndLimit_ReachState);
    DDS_Primitive_init(&sample->Drive_UnitAppliedOption);
    DDS_Primitive_init(&sample->Drive_AllSeat_Motor_FailState);
    DDS_Primitive_init(&sample->Drive_Slide_MotorMove_State);
    DDS_Primitive_init(&sample->Drive_Recline_MotorMove_State);
    DDS_Primitive_init(&sample->Drive_Tilt_MotorMove_State);
    DDS_Primitive_init(&sample->Drive_RelaxTilt_MotorMove_State);
    DDS_Primitive_init(&sample->Drive_Height_MotorMove_State);
    DDS_Primitive_init(&sample->Drive_Legrest_MotorMove_State);
    DDS_Primitive_init(&sample->Drive_Slide_MotorMove_StateInitial);
    DDS_Primitive_init(&sample->Drive_Recline_MotorMove_StateInitial);
    DDS_Primitive_init(&sample->Drive_Tilt_MotorMove_StateInitial);
    DDS_Primitive_init(&sample->Drive_RelaxTilt_MotorMove_StateInitial);
    DDS_Primitive_init(&sample->Drive_Height_MotorMove_StateInitial);
    DDS_Primitive_init(&sample->Drive_Legrest_MotorMove_StateInitial);
    DDS_Primitive_init(&sample->Drive_Slide_MotorVirtualLimitSet_State);
    DDS_Primitive_init(&sample->Drive_Recline_MotorVirtualLimitSet_State);
    DDS_Primitive_init(&sample->Drive_Tilt_MotorVirtualLimitSet_State);
    DDS_Primitive_init(&sample->Drive_RelaxTilt_MotorVirtualLimitSet_State);
    DDS_Primitive_init(&sample->Drive_Height_MotorVirtualLimitSet_State);
    DDS_Primitive_init(&sample->Drive_Legrest_MotorVirtualLimitSet_State);
    DDS_Primitive_init(&sample->Drive_Seat_EasyAccess_Option);
    DDS_Primitive_init(&sample->Drive_Slide_ForwardMotor_Output);
    DDS_Primitive_init(&sample->Drive_Slide_BackwardMotor_Output);
    DDS_Primitive_init(&sample->Drive_Recline_ForwardMotor_Output);
    DDS_Primitive_init(&sample->Drive_Recline_BackwardMotor_Output);
    DDS_Primitive_init(&sample->Drive_Tilt_ForwardMotor_Output);
    DDS_Primitive_init(&sample->Drive_Tilt_BackwardMotor_Output);
    DDS_Primitive_init(&sample->Drive_RlxTilt_ForwardMotor_Output);
    DDS_Primitive_init(&sample->Drive_RlxTilt_BackwardMotor_Output);
    DDS_Primitive_init(&sample->Drive_Height_ForwardMotor_Output);
    DDS_Primitive_init(&sample->Drive_Height_BackwardMotor_Output);
    DDS_Primitive_init(&sample->Drive_Legrest_ForwardMotor_Output);
    DDS_Primitive_init(&sample->Drive_Legrest_BackwardMotor_Output);
    DDS_Primitive_init(&sample->DPSS_StSldFwdMvBtn_PSUIO_DRV);
    DDS_Primitive_init(&sample->DPSS_StSldBwdMvBtn_PSUIO_DRV);
    DDS_Primitive_init(&sample->DPSS_StRclFwdMvBtn_PSUIO_DRV);
    DDS_Primitive_init(&sample->DPSS_StRclBwdMvBtn_PSUIO_DRV);
    DDS_Primitive_init(&sample->DPSS_StTltUpMvBtn_PSUIO_DRV);
    DDS_Primitive_init(&sample->DPSS_StTltDnMvBtn_PSUIO_DRV);
    DDS_Primitive_init(&sample->DPSS_StRlxTltUpMvBtn_PSUIO_DRV);
    DDS_Primitive_init(&sample->DPSS_StRlxTltDnMvBtn_PSUIO_DRV);
    DDS_Primitive_init(&sample->DPSS_StHgtUpMvBtn_PSUIO_DRV);
    DDS_Primitive_init(&sample->DPSS_StHgtDnMvBtn_PSUIO_DRV);
    DDS_Primitive_init(&sample->DPSS_StLegUpMvBtn_PSUIO_DRV);
    DDS_Primitive_init(&sample->DPSS_StLegDnMvBtn_PSUIO_DRV);
    DDS_Primitive_init(&sample->DPSS_StRlxModeBtn_PSUIO_DRV);
    DDS_Primitive_init(&sample->DPSS_StRlxReturnBtn_PSUIO_DRV);
    DDS_Primitive_init(&sample->Drive_PSU_Slide_Fail_State_PSUIO_DRV);
    DDS_Primitive_init(&sample->Drive_PSU_Recline_Fail_State_PSUIO_DRV);
    DDS_Primitive_init(&sample->Drive_PSU_Tilt_Fail_State_PSUIO_DRV);
    DDS_Primitive_init(&sample->Drive_PSU_RlxTilt_Fail_State_PSUIO_DRV);
    DDS_Primitive_init(&sample->Drive_PSU_Height_Fail_State_PSUIO_DRV);
    DDS_Primitive_init(&sample->Drive_PSU_Legrest_Fail_State_PSUIO_DRV);
    DDS_Primitive_init(&sample->PSUIO_DRV_SleepReady);
    return RTI_TRUE;
}

dds_Cabin_Seat_PSUIO_DRV_t *
dds_Cabin_Seat_PSUIO_DRV_t_create(void)
{
    dds_Cabin_Seat_PSUIO_DRV_t* sample;
    OSAPI_Heap_allocate_struct(&sample, dds_Cabin_Seat_PSUIO_DRV_t);
    if (sample != NULL)
    {
        if (!dds_Cabin_Seat_PSUIO_DRV_t_initialize(sample))
        {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}

#ifndef RTI_CERT

RTI_BOOL
dds_Cabin_Seat_PSUIO_DRV_t_finalize(dds_Cabin_Seat_PSUIO_DRV_t* sample)
{
    if (sample == NULL)
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

#ifndef RTI_CERT
void
dds_Cabin_Seat_PSUIO_DRV_t_delete(dds_Cabin_Seat_PSUIO_DRV_t* sample)
{
    if (sample != NULL)
    {
        /* dds_Cabin_Seat_PSUIO_DRV_t_finalize() always
        returns RTI_TRUE when called with sample != NULL */
        dds_Cabin_Seat_PSUIO_DRV_t_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}
#endif
#endif

RTI_BOOL
dds_Cabin_Seat_PSUIO_DRV_t_copy(dds_Cabin_Seat_PSUIO_DRV_t* dst,const dds_Cabin_Seat_PSUIO_DRV_t* src)
{
    if ((dst == NULL) || (src == NULL))
    {
        return RTI_FALSE;
    }
    DDS_Primitive_copy(&dst->Drive_Slide_CurrentPosition, &src->Drive_Slide_CurrentPosition);
    DDS_Primitive_copy(&dst->Drive_Recline_CurrentPosition, &src->Drive_Recline_CurrentPosition);
    DDS_Primitive_copy(&dst->Drive_Height_CurrentPosition, &src->Drive_Height_CurrentPosition);
    DDS_Primitive_copy(&dst->Drive_Tilt_CurrentPosition, &src->Drive_Tilt_CurrentPosition);
    DDS_Primitive_copy(&dst->Drive_RelaxTilt_CurrentPosition, &src->Drive_RelaxTilt_CurrentPosition);
    DDS_Primitive_copy(&dst->Drive_Legrest_CurrentPosition, &src->Drive_Legrest_CurrentPosition);
    DDS_Primitive_copy(&dst->Drive_Seat_MotorIntegratedMove_FeedbackInitial, &src->Drive_Seat_MotorIntegratedMove_FeedbackInitial);
    DDS_Primitive_copy(&dst->Drive_Slide_VirtualLimitReach_State, &src->Drive_Slide_VirtualLimitReach_State);
    DDS_Primitive_copy(&dst->Drive_Recline_VirtualLimitReach_State, &src->Drive_Recline_VirtualLimitReach_State);
    DDS_Primitive_copy(&dst->Drive_Tilt_VirtualLimitReach_State, &src->Drive_Tilt_VirtualLimitReach_State);
    DDS_Primitive_copy(&dst->Drive_RelaxTilt_VirtualLimitReach_State, &src->Drive_RelaxTilt_VirtualLimitReach_State);
    DDS_Primitive_copy(&dst->Drive_Height_VirtualLimitReach_State, &src->Drive_Height_VirtualLimitReach_State);
    DDS_Primitive_copy(&dst->Drive_Legrest_VirtualLimitReach_State, &src->Drive_Legrest_VirtualLimitReach_State);
    DDS_Primitive_copy(&dst->Drive_Slide_Sensor_ErrorState, &src->Drive_Slide_Sensor_ErrorState);
    DDS_Primitive_copy(&dst->Drive_Recline_Sensor_ErrorState, &src->Drive_Recline_Sensor_ErrorState);
    DDS_Primitive_copy(&dst->Drive_Tilt_Sensor_ErrorState, &src->Drive_Tilt_Sensor_ErrorState);
    DDS_Primitive_copy(&dst->Drive_RelaxTilt_Sensor_ErrorState, &src->Drive_RelaxTilt_Sensor_ErrorState);
    DDS_Primitive_copy(&dst->Drive_Height_Sensor_ErrorState, &src->Drive_Height_Sensor_ErrorState);
    DDS_Primitive_copy(&dst->Drive_Legrest_Sensor_ErrorState, &src->Drive_Legrest_Sensor_ErrorState);
    DDS_Primitive_copy(&dst->Drive_Slide_EndLimit_ReachState, &src->Drive_Slide_EndLimit_ReachState);
    DDS_Primitive_copy(&dst->Drive_Recline_EndLimit_ReachState, &src->Drive_Recline_EndLimit_ReachState);
    DDS_Primitive_copy(&dst->Drive_Tilt_EndLimit_ReachState, &src->Drive_Tilt_EndLimit_ReachState);
    DDS_Primitive_copy(&dst->Drive_RlxTilt_EndLimit_ReachState, &src->Drive_RlxTilt_EndLimit_ReachState);
    DDS_Primitive_copy(&dst->Drive_Height_EndLimit_ReachState, &src->Drive_Height_EndLimit_ReachState);
    DDS_Primitive_copy(&dst->Drive_Legrest_EndLimit_ReachState, &src->Drive_Legrest_EndLimit_ReachState);
    DDS_Primitive_copy(&dst->Drive_UnitAppliedOption, &src->Drive_UnitAppliedOption);
    DDS_Primitive_copy(&dst->Drive_AllSeat_Motor_FailState, &src->Drive_AllSeat_Motor_FailState);
    DDS_Primitive_copy(&dst->Drive_Slide_MotorMove_State, &src->Drive_Slide_MotorMove_State);
    DDS_Primitive_copy(&dst->Drive_Recline_MotorMove_State, &src->Drive_Recline_MotorMove_State);
    DDS_Primitive_copy(&dst->Drive_Tilt_MotorMove_State, &src->Drive_Tilt_MotorMove_State);
    DDS_Primitive_copy(&dst->Drive_RelaxTilt_MotorMove_State, &src->Drive_RelaxTilt_MotorMove_State);
    DDS_Primitive_copy(&dst->Drive_Height_MotorMove_State, &src->Drive_Height_MotorMove_State);
    DDS_Primitive_copy(&dst->Drive_Legrest_MotorMove_State, &src->Drive_Legrest_MotorMove_State);
    DDS_Primitive_copy(&dst->Drive_Slide_MotorMove_StateInitial, &src->Drive_Slide_MotorMove_StateInitial);
    DDS_Primitive_copy(&dst->Drive_Recline_MotorMove_StateInitial, &src->Drive_Recline_MotorMove_StateInitial);
    DDS_Primitive_copy(&dst->Drive_Tilt_MotorMove_StateInitial, &src->Drive_Tilt_MotorMove_StateInitial);
    DDS_Primitive_copy(&dst->Drive_RelaxTilt_MotorMove_StateInitial, &src->Drive_RelaxTilt_MotorMove_StateInitial);
    DDS_Primitive_copy(&dst->Drive_Height_MotorMove_StateInitial, &src->Drive_Height_MotorMove_StateInitial);
    DDS_Primitive_copy(&dst->Drive_Legrest_MotorMove_StateInitial, &src->Drive_Legrest_MotorMove_StateInitial);
    DDS_Primitive_copy(&dst->Drive_Slide_MotorVirtualLimitSet_State, &src->Drive_Slide_MotorVirtualLimitSet_State);
    DDS_Primitive_copy(&dst->Drive_Recline_MotorVirtualLimitSet_State, &src->Drive_Recline_MotorVirtualLimitSet_State);
    DDS_Primitive_copy(&dst->Drive_Tilt_MotorVirtualLimitSet_State, &src->Drive_Tilt_MotorVirtualLimitSet_State);
    DDS_Primitive_copy(&dst->Drive_RelaxTilt_MotorVirtualLimitSet_State, &src->Drive_RelaxTilt_MotorVirtualLimitSet_State);
    DDS_Primitive_copy(&dst->Drive_Height_MotorVirtualLimitSet_State, &src->Drive_Height_MotorVirtualLimitSet_State);
    DDS_Primitive_copy(&dst->Drive_Legrest_MotorVirtualLimitSet_State, &src->Drive_Legrest_MotorVirtualLimitSet_State);
    DDS_Primitive_copy(&dst->Drive_Seat_EasyAccess_Option, &src->Drive_Seat_EasyAccess_Option);
    DDS_Primitive_copy(&dst->Drive_Slide_ForwardMotor_Output, &src->Drive_Slide_ForwardMotor_Output);
    DDS_Primitive_copy(&dst->Drive_Slide_BackwardMotor_Output, &src->Drive_Slide_BackwardMotor_Output);
    DDS_Primitive_copy(&dst->Drive_Recline_ForwardMotor_Output, &src->Drive_Recline_ForwardMotor_Output);
    DDS_Primitive_copy(&dst->Drive_Recline_BackwardMotor_Output, &src->Drive_Recline_BackwardMotor_Output);
    DDS_Primitive_copy(&dst->Drive_Tilt_ForwardMotor_Output, &src->Drive_Tilt_ForwardMotor_Output);
    DDS_Primitive_copy(&dst->Drive_Tilt_BackwardMotor_Output, &src->Drive_Tilt_BackwardMotor_Output);
    DDS_Primitive_copy(&dst->Drive_RlxTilt_ForwardMotor_Output, &src->Drive_RlxTilt_ForwardMotor_Output);
    DDS_Primitive_copy(&dst->Drive_RlxTilt_BackwardMotor_Output, &src->Drive_RlxTilt_BackwardMotor_Output);
    DDS_Primitive_copy(&dst->Drive_Height_ForwardMotor_Output, &src->Drive_Height_ForwardMotor_Output);
    DDS_Primitive_copy(&dst->Drive_Height_BackwardMotor_Output, &src->Drive_Height_BackwardMotor_Output);
    DDS_Primitive_copy(&dst->Drive_Legrest_ForwardMotor_Output, &src->Drive_Legrest_ForwardMotor_Output);
    DDS_Primitive_copy(&dst->Drive_Legrest_BackwardMotor_Output, &src->Drive_Legrest_BackwardMotor_Output);
    DDS_Primitive_copy(&dst->DPSS_StSldFwdMvBtn_PSUIO_DRV, &src->DPSS_StSldFwdMvBtn_PSUIO_DRV);
    DDS_Primitive_copy(&dst->DPSS_StSldBwdMvBtn_PSUIO_DRV, &src->DPSS_StSldBwdMvBtn_PSUIO_DRV);
    DDS_Primitive_copy(&dst->DPSS_StRclFwdMvBtn_PSUIO_DRV, &src->DPSS_StRclFwdMvBtn_PSUIO_DRV);
    DDS_Primitive_copy(&dst->DPSS_StRclBwdMvBtn_PSUIO_DRV, &src->DPSS_StRclBwdMvBtn_PSUIO_DRV);
    DDS_Primitive_copy(&dst->DPSS_StTltUpMvBtn_PSUIO_DRV, &src->DPSS_StTltUpMvBtn_PSUIO_DRV);
    DDS_Primitive_copy(&dst->DPSS_StTltDnMvBtn_PSUIO_DRV, &src->DPSS_StTltDnMvBtn_PSUIO_DRV);
    DDS_Primitive_copy(&dst->DPSS_StRlxTltUpMvBtn_PSUIO_DRV, &src->DPSS_StRlxTltUpMvBtn_PSUIO_DRV);
    DDS_Primitive_copy(&dst->DPSS_StRlxTltDnMvBtn_PSUIO_DRV, &src->DPSS_StRlxTltDnMvBtn_PSUIO_DRV);
    DDS_Primitive_copy(&dst->DPSS_StHgtUpMvBtn_PSUIO_DRV, &src->DPSS_StHgtUpMvBtn_PSUIO_DRV);
    DDS_Primitive_copy(&dst->DPSS_StHgtDnMvBtn_PSUIO_DRV, &src->DPSS_StHgtDnMvBtn_PSUIO_DRV);
    DDS_Primitive_copy(&dst->DPSS_StLegUpMvBtn_PSUIO_DRV, &src->DPSS_StLegUpMvBtn_PSUIO_DRV);
    DDS_Primitive_copy(&dst->DPSS_StLegDnMvBtn_PSUIO_DRV, &src->DPSS_StLegDnMvBtn_PSUIO_DRV);
    DDS_Primitive_copy(&dst->DPSS_StRlxModeBtn_PSUIO_DRV, &src->DPSS_StRlxModeBtn_PSUIO_DRV);
    DDS_Primitive_copy(&dst->DPSS_StRlxReturnBtn_PSUIO_DRV, &src->DPSS_StRlxReturnBtn_PSUIO_DRV);
    DDS_Primitive_copy(&dst->Drive_PSU_Slide_Fail_State_PSUIO_DRV, &src->Drive_PSU_Slide_Fail_State_PSUIO_DRV);
    DDS_Primitive_copy(&dst->Drive_PSU_Recline_Fail_State_PSUIO_DRV, &src->Drive_PSU_Recline_Fail_State_PSUIO_DRV);
    DDS_Primitive_copy(&dst->Drive_PSU_Tilt_Fail_State_PSUIO_DRV, &src->Drive_PSU_Tilt_Fail_State_PSUIO_DRV);
    DDS_Primitive_copy(&dst->Drive_PSU_RlxTilt_Fail_State_PSUIO_DRV, &src->Drive_PSU_RlxTilt_Fail_State_PSUIO_DRV);
    DDS_Primitive_copy(&dst->Drive_PSU_Height_Fail_State_PSUIO_DRV, &src->Drive_PSU_Height_Fail_State_PSUIO_DRV);
    DDS_Primitive_copy(&dst->Drive_PSU_Legrest_Fail_State_PSUIO_DRV, &src->Drive_PSU_Legrest_Fail_State_PSUIO_DRV);
    DDS_Primitive_copy(&dst->PSUIO_DRV_SleepReady, &src->PSUIO_DRV_SleepReady);
    return RTI_TRUE;
}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'dds_Cabin_Seat_PSUIO_DRV_t' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T dds_Cabin_Seat_PSUIO_DRV_t
#define TSeq dds_Cabin_Seat_PSUIO_DRV_tSeq
#define T_initialize dds_Cabin_Seat_PSUIO_DRV_t_initialize
#define T_finalize   dds_Cabin_Seat_PSUIO_DRV_t_finalize
#define T_copy       dds_Cabin_Seat_PSUIO_DRV_t_copy
#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

/* ========================================================================= */

const char *dds_GCS_LEFT_2_PDIO_FL_tTYPENAME = "dds::GCS_LEFT_2_PDIO_FL_t";

RTI_BOOL
dds_GCS_LEFT_2_PDIO_FL_t_initialize(dds_GCS_LEFT_2_PDIO_FL_t* sample)
{
    if (sample == NULL)
    {
        return RTI_FALSE;
    }

    DDS_Primitive_init(&sample->PwrDrOpnClsCmd_PDIO_FL);
    DDS_Primitive_init(&sample->PwrDrSnsrStatus_RODS_FL_PDIO_FL);
    DDS_Primitive_init(&sample->PwrDrSnsrStopAngle_RODS_FL_PDIO_FL);
    DDS_Primitive_init(&sample->PwrDrSnsrStopRequest_RODS_FL_PDIO_FL);
    DDS_Primitive_init(&sample->ACU_CrshActvSta_PDIO_FL);
    DDS_Primitive_init(&sample->ACU_CrshTyp_PDIO_FL);
    DDS_Primitive_init(&sample->Door_LockUnlockCmd_PDIO_FL);
    DDS_Primitive_init(&sample->IMU_LatAccelSigSta_PDIO_FL);
    DDS_Primitive_init(&sample->IMU_LongAccelSigSta_PDIO_FL);
    DDS_Primitive_init(&sample->IMU_LatAccelVal_PDIO_FL);
    DDS_Primitive_init(&sample->IMU_LongAccelVal_PDIO_FL);
    DDS_Primitive_init(&sample->VehicleSpeedState_PDIO_FL);
    DDS_Primitive_init(&sample->VCU_GearPosSta_PDIO_FL);
    DDS_Primitive_init(&sample->PwrDrOpnAngVal_PDIO_FL);
    DDS_Primitive_init(&sample->SleepRequestTo_PDIO_FL);
    DDS_Primitive_init(&sample->SleepCommandTo_PDIO_FL);
    DDS_Primitive_init(&sample->VehiclePowerState_PDIO_FL);
    return RTI_TRUE;
}

dds_GCS_LEFT_2_PDIO_FL_t *
dds_GCS_LEFT_2_PDIO_FL_t_create(void)
{
    dds_GCS_LEFT_2_PDIO_FL_t* sample;
    OSAPI_Heap_allocate_struct(&sample, dds_GCS_LEFT_2_PDIO_FL_t);
    if (sample != NULL)
    {
        if (!dds_GCS_LEFT_2_PDIO_FL_t_initialize(sample))
        {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}

#ifndef RTI_CERT

RTI_BOOL
dds_GCS_LEFT_2_PDIO_FL_t_finalize(dds_GCS_LEFT_2_PDIO_FL_t* sample)
{
    if (sample == NULL)
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

#ifndef RTI_CERT
void
dds_GCS_LEFT_2_PDIO_FL_t_delete(dds_GCS_LEFT_2_PDIO_FL_t* sample)
{
    if (sample != NULL)
    {
        /* dds_GCS_LEFT_2_PDIO_FL_t_finalize() always
        returns RTI_TRUE when called with sample != NULL */
        dds_GCS_LEFT_2_PDIO_FL_t_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}
#endif
#endif

RTI_BOOL
dds_GCS_LEFT_2_PDIO_FL_t_copy(dds_GCS_LEFT_2_PDIO_FL_t* dst,const dds_GCS_LEFT_2_PDIO_FL_t* src)
{
    if ((dst == NULL) || (src == NULL))
    {
        return RTI_FALSE;
    }
    DDS_Primitive_copy(&dst->PwrDrOpnClsCmd_PDIO_FL, &src->PwrDrOpnClsCmd_PDIO_FL);
    DDS_Primitive_copy(&dst->PwrDrSnsrStatus_RODS_FL_PDIO_FL, &src->PwrDrSnsrStatus_RODS_FL_PDIO_FL);
    DDS_Primitive_copy(&dst->PwrDrSnsrStopAngle_RODS_FL_PDIO_FL, &src->PwrDrSnsrStopAngle_RODS_FL_PDIO_FL);
    DDS_Primitive_copy(&dst->PwrDrSnsrStopRequest_RODS_FL_PDIO_FL, &src->PwrDrSnsrStopRequest_RODS_FL_PDIO_FL);
    DDS_Primitive_copy(&dst->ACU_CrshActvSta_PDIO_FL, &src->ACU_CrshActvSta_PDIO_FL);
    DDS_Primitive_copy(&dst->ACU_CrshTyp_PDIO_FL, &src->ACU_CrshTyp_PDIO_FL);
    DDS_Primitive_copy(&dst->Door_LockUnlockCmd_PDIO_FL, &src->Door_LockUnlockCmd_PDIO_FL);
    DDS_Primitive_copy(&dst->IMU_LatAccelSigSta_PDIO_FL, &src->IMU_LatAccelSigSta_PDIO_FL);
    DDS_Primitive_copy(&dst->IMU_LongAccelSigSta_PDIO_FL, &src->IMU_LongAccelSigSta_PDIO_FL);
    DDS_Primitive_copy(&dst->IMU_LatAccelVal_PDIO_FL, &src->IMU_LatAccelVal_PDIO_FL);
    DDS_Primitive_copy(&dst->IMU_LongAccelVal_PDIO_FL, &src->IMU_LongAccelVal_PDIO_FL);
    DDS_Primitive_copy(&dst->VehicleSpeedState_PDIO_FL, &src->VehicleSpeedState_PDIO_FL);
    DDS_Primitive_copy(&dst->VCU_GearPosSta_PDIO_FL, &src->VCU_GearPosSta_PDIO_FL);
    DDS_Primitive_copy(&dst->PwrDrOpnAngVal_PDIO_FL, &src->PwrDrOpnAngVal_PDIO_FL);
    DDS_Primitive_copy(&dst->SleepRequestTo_PDIO_FL, &src->SleepRequestTo_PDIO_FL);
    DDS_Primitive_copy(&dst->SleepCommandTo_PDIO_FL, &src->SleepCommandTo_PDIO_FL);
    DDS_Primitive_copy(&dst->VehiclePowerState_PDIO_FL, &src->VehiclePowerState_PDIO_FL);
    return RTI_TRUE;
}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'dds_GCS_LEFT_2_PDIO_FL_t' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T dds_GCS_LEFT_2_PDIO_FL_t
#define TSeq dds_GCS_LEFT_2_PDIO_FL_tSeq
#define T_initialize dds_GCS_LEFT_2_PDIO_FL_t_initialize
#define T_finalize   dds_GCS_LEFT_2_PDIO_FL_t_finalize
#define T_copy       dds_GCS_LEFT_2_PDIO_FL_t_copy
#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

/* ========================================================================= */

const char *dds_GCS_LEFT_2_PSUIO_DRV_tTYPENAME = "dds::GCS_LEFT_2_PSUIO_DRV_t";

RTI_BOOL
dds_GCS_LEFT_2_PSUIO_DRV_t_initialize(dds_GCS_LEFT_2_PSUIO_DRV_t* sample)
{
    if (sample == NULL)
    {
        return RTI_FALSE;
    }

    DDS_Primitive_init(&sample->PSeat_DrvInitializationPlayCmd_PSUIO_DRV);
    DDS_Primitive_init(&sample->PSeat_DrvSlideManualPlayCmd_PSUIO_DRV);
    DDS_Primitive_init(&sample->PSeat_DrvReclineManualPlayCmd_PSUIO_DRV);
    DDS_Primitive_init(&sample->PSeat_DrvTiltManualPlayCmd_PSUIO_DRV);
    DDS_Primitive_init(&sample->PSeat_DrvRlxTiltManualPlayCmd_PSUIO_DRV);
    DDS_Primitive_init(&sample->PSeat_DrvHeightManualPlayCmd_PSUIO_DRV);
    DDS_Primitive_init(&sample->PSeat_DrvLegrestManualPlayCmd_PSUIO_DRV);
    DDS_Primitive_init(&sample->Pseat_DrvAutoCmdTargetPos_PSUIO_DRV);
    DDS_Primitive_init(&sample->Pseat_DrvAutoCmdTargetPos_Percentage_PSUIO_DRV);
    DDS_Primitive_init(&sample->Driver_Recline_TargetPlayCmd_PSUIO_DRV);
    DDS_Primitive_init(&sample->Driver_Slide_TargetPlayCmd_PSUIO_DRV);
    DDS_Primitive_init(&sample->Driver_Tilt_TargetPlayCmd_PSUIO_DRV);
    DDS_Primitive_init(&sample->Driver_RlxTilt_TargetPlayCmd_PSUIO_DRV);
    DDS_Primitive_init(&sample->Driver_Height_TargetPlayCmd_PSUIO_DRV);
    DDS_Primitive_init(&sample->Driver_Legrest_TargetPlayCmd_PSUIO_DRV);
    DDS_Primitive_init(&sample->DriveTypeOption_PSUIO_DRV);
    DDS_Primitive_init(&sample->ICU_PowerAutoCutModSta_PSUIO_DRV);
    DDS_Primitive_init(&sample->SleepRequestTo_PSUIO_DRV);
    DDS_Primitive_init(&sample->VehicePowerState_PSUIO_DRV);
    return RTI_TRUE;
}

dds_GCS_LEFT_2_PSUIO_DRV_t *
dds_GCS_LEFT_2_PSUIO_DRV_t_create(void)
{
    dds_GCS_LEFT_2_PSUIO_DRV_t* sample;
    OSAPI_Heap_allocate_struct(&sample, dds_GCS_LEFT_2_PSUIO_DRV_t);
    if (sample != NULL)
    {
        if (!dds_GCS_LEFT_2_PSUIO_DRV_t_initialize(sample))
        {
            OSAPI_Heap_free_struct(sample);
            sample = NULL;
        }
    }
    return sample;
}

#ifndef RTI_CERT

RTI_BOOL
dds_GCS_LEFT_2_PSUIO_DRV_t_finalize(dds_GCS_LEFT_2_PSUIO_DRV_t* sample)
{
    if (sample == NULL)
    {
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

#ifndef RTI_CERT
void
dds_GCS_LEFT_2_PSUIO_DRV_t_delete(dds_GCS_LEFT_2_PSUIO_DRV_t* sample)
{
    if (sample != NULL)
    {
        /* dds_GCS_LEFT_2_PSUIO_DRV_t_finalize() always
        returns RTI_TRUE when called with sample != NULL */
        dds_GCS_LEFT_2_PSUIO_DRV_t_finalize(sample);
        OSAPI_Heap_free_struct(sample);
    }
}
#endif
#endif

RTI_BOOL
dds_GCS_LEFT_2_PSUIO_DRV_t_copy(dds_GCS_LEFT_2_PSUIO_DRV_t* dst,const dds_GCS_LEFT_2_PSUIO_DRV_t* src)
{
    if ((dst == NULL) || (src == NULL))
    {
        return RTI_FALSE;
    }
    DDS_Primitive_copy(&dst->PSeat_DrvInitializationPlayCmd_PSUIO_DRV, &src->PSeat_DrvInitializationPlayCmd_PSUIO_DRV);
    DDS_Primitive_copy(&dst->PSeat_DrvSlideManualPlayCmd_PSUIO_DRV, &src->PSeat_DrvSlideManualPlayCmd_PSUIO_DRV);
    DDS_Primitive_copy(&dst->PSeat_DrvReclineManualPlayCmd_PSUIO_DRV, &src->PSeat_DrvReclineManualPlayCmd_PSUIO_DRV);
    DDS_Primitive_copy(&dst->PSeat_DrvTiltManualPlayCmd_PSUIO_DRV, &src->PSeat_DrvTiltManualPlayCmd_PSUIO_DRV);
    DDS_Primitive_copy(&dst->PSeat_DrvRlxTiltManualPlayCmd_PSUIO_DRV, &src->PSeat_DrvRlxTiltManualPlayCmd_PSUIO_DRV);
    DDS_Primitive_copy(&dst->PSeat_DrvHeightManualPlayCmd_PSUIO_DRV, &src->PSeat_DrvHeightManualPlayCmd_PSUIO_DRV);
    DDS_Primitive_copy(&dst->PSeat_DrvLegrestManualPlayCmd_PSUIO_DRV, &src->PSeat_DrvLegrestManualPlayCmd_PSUIO_DRV);
    DDS_Primitive_copy(&dst->Pseat_DrvAutoCmdTargetPos_PSUIO_DRV, &src->Pseat_DrvAutoCmdTargetPos_PSUIO_DRV);
    DDS_Primitive_copy(&dst->Pseat_DrvAutoCmdTargetPos_Percentage_PSUIO_DRV, &src->Pseat_DrvAutoCmdTargetPos_Percentage_PSUIO_DRV);
    DDS_Primitive_copy(&dst->Driver_Recline_TargetPlayCmd_PSUIO_DRV, &src->Driver_Recline_TargetPlayCmd_PSUIO_DRV);
    DDS_Primitive_copy(&dst->Driver_Slide_TargetPlayCmd_PSUIO_DRV, &src->Driver_Slide_TargetPlayCmd_PSUIO_DRV);
    DDS_Primitive_copy(&dst->Driver_Tilt_TargetPlayCmd_PSUIO_DRV, &src->Driver_Tilt_TargetPlayCmd_PSUIO_DRV);
    DDS_Primitive_copy(&dst->Driver_RlxTilt_TargetPlayCmd_PSUIO_DRV, &src->Driver_RlxTilt_TargetPlayCmd_PSUIO_DRV);
    DDS_Primitive_copy(&dst->Driver_Height_TargetPlayCmd_PSUIO_DRV, &src->Driver_Height_TargetPlayCmd_PSUIO_DRV);
    DDS_Primitive_copy(&dst->Driver_Legrest_TargetPlayCmd_PSUIO_DRV, &src->Driver_Legrest_TargetPlayCmd_PSUIO_DRV);
    DDS_Primitive_copy(&dst->DriveTypeOption_PSUIO_DRV, &src->DriveTypeOption_PSUIO_DRV);
    DDS_Primitive_copy(&dst->ICU_PowerAutoCutModSta_PSUIO_DRV, &src->ICU_PowerAutoCutModSta_PSUIO_DRV);
    DDS_Primitive_copy(&dst->SleepRequestTo_PSUIO_DRV, &src->SleepRequestTo_PSUIO_DRV);
    DDS_Primitive_copy(&dst->VehicePowerState_PSUIO_DRV, &src->VehicePowerState_PSUIO_DRV);
    return RTI_TRUE;
}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'dds_GCS_LEFT_2_PSUIO_DRV_t' sequence class.
*/
#define REDA_SEQUENCE_USER_API
#define T dds_GCS_LEFT_2_PSUIO_DRV_t
#define TSeq dds_GCS_LEFT_2_PSUIO_DRV_tSeq
#define T_initialize dds_GCS_LEFT_2_PSUIO_DRV_t_initialize
#define T_finalize   dds_GCS_LEFT_2_PSUIO_DRV_t_finalize
#define T_copy       dds_GCS_LEFT_2_PSUIO_DRV_t_copy
#include "reda/reda_sequence_defn.h"
#undef T_copy
#undef T_finalize
#undef T_initialize

