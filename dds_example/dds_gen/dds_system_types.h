/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from dds_system_types.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Data Distribution Service distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Data Distribution Service manual.
*/

#ifndef dds_system_types_1690667057_h
#define dds_system_types_1690667057_h

#ifndef rti_me_c_h
#include "rti_me_c.h"
#endif

#if DDS_XTYPES_IS_ENABLED
#include "dds_c/dds_c_typecode.h"
#include "xcdr/xcdr_dds_interpreter.h"
#endif

#if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols. */
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifdef __cplusplus
extern "C" {
    #endif

    typedef struct dds_Cabin_Door_PDIO_FL_t

    {

        DDS_Octet PDIO_FL_Driver_Door_Switch_State;
        DDS_Octet PDIO_FL_Driver_Door_Unlock_State;
        DDS_Octet PDIO_FL_PwrDrAvailability;
        DDS_Float PDIO_FL_PwrDrAngle;
        DDS_Octet PDIO_FL_PwrDrStatus;
        DDS_Octet PDIO_FL_PwrDrSwingActrStatus;
        DDS_Octet PDIO_FL_PwrDrErrorState;
        DDS_Octet PDIO_FL_PwrDrAntiPinchStatus;
        DDS_Float PDIO_FL_PwrDrAngleSpeed;
        DDS_Octet PDIO_FL_InsdOpnClsSwStatus;
        DDS_Octet PDIO_FL_OtsdOpnClsSwStatus;
        DDS_Octet PDIO_FL_SleepReady;
        DDS_Octet PDIO_FL_WakeupRequest;
        DDS_Octet PDIO_FL_CinchingStatus;
        DDS_Octet PDIO_FL_ActiveHoldingState;

    } dds_Cabin_Door_PDIO_FL_t ;

    NDDSUSERDllExport extern const char *dds_Cabin_Door_PDIO_FL_tTYPENAME;

    #define REDA_SEQUENCE_USER_API
    #define T dds_Cabin_Door_PDIO_FL_t
    #define TSeq dds_Cabin_Door_PDIO_FL_tSeq
    #define REDA_SEQUENCE_EXCLUDE_C_METHODS
    #define REDA_SEQUENCE_USER_CPP
    #include <reda/reda_sequence_decl.h>

    #define REDA_SEQUENCE_USER_API
    #define T dds_Cabin_Door_PDIO_FL_t
    #define TSeq dds_Cabin_Door_PDIO_FL_tSeq
    #define REDA_SEQUENCE_EXCLUDE_STRUCT
    #define REDA_SEQUENCE_USER_CPP
    #include <reda/reda_sequence_decl.h>

    NDDSUSERDllExport extern RTI_BOOL
    dds_Cabin_Door_PDIO_FL_t_initialize(dds_Cabin_Door_PDIO_FL_t* sample);

    NDDSUSERDllExport extern dds_Cabin_Door_PDIO_FL_t*
    dds_Cabin_Door_PDIO_FL_t_create(void);

    #ifndef RTI_CERT
    NDDSUSERDllExport extern RTI_BOOL
    dds_Cabin_Door_PDIO_FL_t_finalize(dds_Cabin_Door_PDIO_FL_t* sample);

    NDDSUSERDllExport extern void
    dds_Cabin_Door_PDIO_FL_t_delete(dds_Cabin_Door_PDIO_FL_t* sample);
    #endif

    NDDSUSERDllExport extern RTI_BOOL
    dds_Cabin_Door_PDIO_FL_t_copy(dds_Cabin_Door_PDIO_FL_t* dst, const dds_Cabin_Door_PDIO_FL_t* src);

    typedef struct dds_Cabin_Seat_PSUIO_DRV_t

    {

        DDS_UnsignedShort Drive_Slide_CurrentPosition;
        DDS_UnsignedShort Drive_Recline_CurrentPosition;
        DDS_UnsignedShort Drive_Height_CurrentPosition;
        DDS_UnsignedShort Drive_Tilt_CurrentPosition;
        DDS_UnsignedShort Drive_RelaxTilt_CurrentPosition;
        DDS_UnsignedShort Drive_Legrest_CurrentPosition;
        DDS_Octet Drive_Seat_MotorIntegratedMove_FeedbackInitial;
        DDS_Octet Drive_Slide_VirtualLimitReach_State;
        DDS_Octet Drive_Recline_VirtualLimitReach_State;
        DDS_Octet Drive_Tilt_VirtualLimitReach_State;
        DDS_Octet Drive_RelaxTilt_VirtualLimitReach_State;
        DDS_Octet Drive_Height_VirtualLimitReach_State;
        DDS_Octet Drive_Legrest_VirtualLimitReach_State;
        DDS_Octet Drive_Slide_Sensor_ErrorState;
        DDS_Octet Drive_Recline_Sensor_ErrorState;
        DDS_Octet Drive_Tilt_Sensor_ErrorState;
        DDS_Octet Drive_RelaxTilt_Sensor_ErrorState;
        DDS_Octet Drive_Height_Sensor_ErrorState;
        DDS_Octet Drive_Legrest_Sensor_ErrorState;
        DDS_Octet Drive_Slide_EndLimit_ReachState;
        DDS_Octet Drive_Recline_EndLimit_ReachState;
        DDS_Octet Drive_Tilt_EndLimit_ReachState;
        DDS_Octet Drive_RlxTilt_EndLimit_ReachState;
        DDS_Octet Drive_Height_EndLimit_ReachState;
        DDS_Octet Drive_Legrest_EndLimit_ReachState;
        DDS_Octet Drive_UnitAppliedOption;
        DDS_Octet Drive_AllSeat_Motor_FailState;
        DDS_Octet Drive_Slide_MotorMove_State;
        DDS_Octet Drive_Recline_MotorMove_State;
        DDS_Octet Drive_Tilt_MotorMove_State;
        DDS_Octet Drive_RelaxTilt_MotorMove_State;
        DDS_Octet Drive_Height_MotorMove_State;
        DDS_Octet Drive_Legrest_MotorMove_State;
        DDS_Octet Drive_Slide_MotorMove_StateInitial;
        DDS_Octet Drive_Recline_MotorMove_StateInitial;
        DDS_Octet Drive_Tilt_MotorMove_StateInitial;
        DDS_Octet Drive_RelaxTilt_MotorMove_StateInitial;
        DDS_Octet Drive_Height_MotorMove_StateInitial;
        DDS_Octet Drive_Legrest_MotorMove_StateInitial;
        DDS_Octet Drive_Slide_MotorVirtualLimitSet_State;
        DDS_Octet Drive_Recline_MotorVirtualLimitSet_State;
        DDS_Octet Drive_Tilt_MotorVirtualLimitSet_State;
        DDS_Octet Drive_RelaxTilt_MotorVirtualLimitSet_State;
        DDS_Octet Drive_Height_MotorVirtualLimitSet_State;
        DDS_Octet Drive_Legrest_MotorVirtualLimitSet_State;
        DDS_Octet Drive_Seat_EasyAccess_Option;
        DDS_Octet Drive_Slide_ForwardMotor_Output;
        DDS_Octet Drive_Slide_BackwardMotor_Output;
        DDS_Octet Drive_Recline_ForwardMotor_Output;
        DDS_Octet Drive_Recline_BackwardMotor_Output;
        DDS_Octet Drive_Tilt_ForwardMotor_Output;
        DDS_Octet Drive_Tilt_BackwardMotor_Output;
        DDS_Octet Drive_RlxTilt_ForwardMotor_Output;
        DDS_Octet Drive_RlxTilt_BackwardMotor_Output;
        DDS_Octet Drive_Height_ForwardMotor_Output;
        DDS_Octet Drive_Height_BackwardMotor_Output;
        DDS_Octet Drive_Legrest_ForwardMotor_Output;
        DDS_Octet Drive_Legrest_BackwardMotor_Output;
        DDS_Octet DPSS_StSldFwdMvBtn_PSUIO_DRV;
        DDS_Octet DPSS_StSldBwdMvBtn_PSUIO_DRV;
        DDS_Octet DPSS_StRclFwdMvBtn_PSUIO_DRV;
        DDS_Octet DPSS_StRclBwdMvBtn_PSUIO_DRV;
        DDS_Octet DPSS_StTltUpMvBtn_PSUIO_DRV;
        DDS_Octet DPSS_StTltDnMvBtn_PSUIO_DRV;
        DDS_Octet DPSS_StRlxTltUpMvBtn_PSUIO_DRV;
        DDS_Octet DPSS_StRlxTltDnMvBtn_PSUIO_DRV;
        DDS_Octet DPSS_StHgtUpMvBtn_PSUIO_DRV;
        DDS_Octet DPSS_StHgtDnMvBtn_PSUIO_DRV;
        DDS_Octet DPSS_StLegUpMvBtn_PSUIO_DRV;
        DDS_Octet DPSS_StLegDnMvBtn_PSUIO_DRV;
        DDS_Octet DPSS_StRlxModeBtn_PSUIO_DRV;
        DDS_Octet DPSS_StRlxReturnBtn_PSUIO_DRV;
        DDS_Octet Drive_PSU_Slide_Fail_State_PSUIO_DRV;
        DDS_Octet Drive_PSU_Recline_Fail_State_PSUIO_DRV;
        DDS_Octet Drive_PSU_Tilt_Fail_State_PSUIO_DRV;
        DDS_Octet Drive_PSU_RlxTilt_Fail_State_PSUIO_DRV;
        DDS_Octet Drive_PSU_Height_Fail_State_PSUIO_DRV;
        DDS_Octet Drive_PSU_Legrest_Fail_State_PSUIO_DRV;
        DDS_Octet PSUIO_DRV_SleepReady;

    } dds_Cabin_Seat_PSUIO_DRV_t ;

    NDDSUSERDllExport extern const char *dds_Cabin_Seat_PSUIO_DRV_tTYPENAME;

    #define REDA_SEQUENCE_USER_API
    #define T dds_Cabin_Seat_PSUIO_DRV_t
    #define TSeq dds_Cabin_Seat_PSUIO_DRV_tSeq
    #define REDA_SEQUENCE_EXCLUDE_C_METHODS
    #define REDA_SEQUENCE_USER_CPP
    #include <reda/reda_sequence_decl.h>

    #define REDA_SEQUENCE_USER_API
    #define T dds_Cabin_Seat_PSUIO_DRV_t
    #define TSeq dds_Cabin_Seat_PSUIO_DRV_tSeq
    #define REDA_SEQUENCE_EXCLUDE_STRUCT
    #define REDA_SEQUENCE_USER_CPP
    #include <reda/reda_sequence_decl.h>

    NDDSUSERDllExport extern RTI_BOOL
    dds_Cabin_Seat_PSUIO_DRV_t_initialize(dds_Cabin_Seat_PSUIO_DRV_t* sample);

    NDDSUSERDllExport extern dds_Cabin_Seat_PSUIO_DRV_t*
    dds_Cabin_Seat_PSUIO_DRV_t_create(void);

    #ifndef RTI_CERT
    NDDSUSERDllExport extern RTI_BOOL
    dds_Cabin_Seat_PSUIO_DRV_t_finalize(dds_Cabin_Seat_PSUIO_DRV_t* sample);

    NDDSUSERDllExport extern void
    dds_Cabin_Seat_PSUIO_DRV_t_delete(dds_Cabin_Seat_PSUIO_DRV_t* sample);
    #endif

    NDDSUSERDllExport extern RTI_BOOL
    dds_Cabin_Seat_PSUIO_DRV_t_copy(dds_Cabin_Seat_PSUIO_DRV_t* dst, const dds_Cabin_Seat_PSUIO_DRV_t* src);

    typedef struct dds_GCS_LEFT_2_PDIO_FL_t

    {

        DDS_Octet PwrDrOpnClsCmd_PDIO_FL;
        DDS_Octet PwrDrSnsrStatus_RODS_FL_PDIO_FL;
        DDS_Float PwrDrSnsrStopAngle_RODS_FL_PDIO_FL;
        DDS_Octet PwrDrSnsrStopRequest_RODS_FL_PDIO_FL;
        DDS_Octet ACU_CrshActvSta_PDIO_FL;
        DDS_UnsignedShort ACU_CrshTyp_PDIO_FL;
        DDS_Octet Door_LockUnlockCmd_PDIO_FL;
        DDS_Octet IMU_LatAccelSigSta_PDIO_FL;
        DDS_Octet IMU_LongAccelSigSta_PDIO_FL;
        DDS_Float IMU_LatAccelVal_PDIO_FL;
        DDS_Float IMU_LongAccelVal_PDIO_FL;
        DDS_UnsignedShort VehicleSpeedState_PDIO_FL;
        DDS_Octet VCU_GearPosSta_PDIO_FL;
        DDS_Float PwrDrOpnAngVal_PDIO_FL;
        DDS_Octet SleepRequestTo_PDIO_FL;
        DDS_Octet SleepCommandTo_PDIO_FL;
        DDS_Octet VehiclePowerState_PDIO_FL;

    } dds_GCS_LEFT_2_PDIO_FL_t ;

    NDDSUSERDllExport extern const char *dds_GCS_LEFT_2_PDIO_FL_tTYPENAME;

    #define REDA_SEQUENCE_USER_API
    #define T dds_GCS_LEFT_2_PDIO_FL_t
    #define TSeq dds_GCS_LEFT_2_PDIO_FL_tSeq
    #define REDA_SEQUENCE_EXCLUDE_C_METHODS
    #define REDA_SEQUENCE_USER_CPP
    #include <reda/reda_sequence_decl.h>

    #define REDA_SEQUENCE_USER_API
    #define T dds_GCS_LEFT_2_PDIO_FL_t
    #define TSeq dds_GCS_LEFT_2_PDIO_FL_tSeq
    #define REDA_SEQUENCE_EXCLUDE_STRUCT
    #define REDA_SEQUENCE_USER_CPP
    #include <reda/reda_sequence_decl.h>

    NDDSUSERDllExport extern RTI_BOOL
    dds_GCS_LEFT_2_PDIO_FL_t_initialize(dds_GCS_LEFT_2_PDIO_FL_t* sample);

    NDDSUSERDllExport extern dds_GCS_LEFT_2_PDIO_FL_t*
    dds_GCS_LEFT_2_PDIO_FL_t_create(void);

    #ifndef RTI_CERT
    NDDSUSERDllExport extern RTI_BOOL
    dds_GCS_LEFT_2_PDIO_FL_t_finalize(dds_GCS_LEFT_2_PDIO_FL_t* sample);

    NDDSUSERDllExport extern void
    dds_GCS_LEFT_2_PDIO_FL_t_delete(dds_GCS_LEFT_2_PDIO_FL_t* sample);
    #endif

    NDDSUSERDllExport extern RTI_BOOL
    dds_GCS_LEFT_2_PDIO_FL_t_copy(dds_GCS_LEFT_2_PDIO_FL_t* dst, const dds_GCS_LEFT_2_PDIO_FL_t* src);

    typedef struct dds_GCS_LEFT_2_PSUIO_DRV_t

    {

        DDS_Octet PSeat_DrvInitializationPlayCmd_PSUIO_DRV;
        DDS_Octet PSeat_DrvSlideManualPlayCmd_PSUIO_DRV;
        DDS_Octet PSeat_DrvReclineManualPlayCmd_PSUIO_DRV;
        DDS_Octet PSeat_DrvTiltManualPlayCmd_PSUIO_DRV;
        DDS_Octet PSeat_DrvRlxTiltManualPlayCmd_PSUIO_DRV;
        DDS_Octet PSeat_DrvHeightManualPlayCmd_PSUIO_DRV;
        DDS_Octet PSeat_DrvLegrestManualPlayCmd_PSUIO_DRV;
        DDS_Octet Pseat_DrvAutoCmdTargetPos_PSUIO_DRV;
        DDS_Octet Pseat_DrvAutoCmdTargetPos_Percentage_PSUIO_DRV;
        DDS_UnsignedShort Driver_Recline_TargetPlayCmd_PSUIO_DRV;
        DDS_UnsignedShort Driver_Slide_TargetPlayCmd_PSUIO_DRV;
        DDS_UnsignedShort Driver_Tilt_TargetPlayCmd_PSUIO_DRV;
        DDS_UnsignedShort Driver_RlxTilt_TargetPlayCmd_PSUIO_DRV;
        DDS_UnsignedShort Driver_Height_TargetPlayCmd_PSUIO_DRV;
        DDS_UnsignedShort Driver_Legrest_TargetPlayCmd_PSUIO_DRV;
        DDS_Octet DriveTypeOption_PSUIO_DRV;
        DDS_Octet ICU_PowerAutoCutModSta_PSUIO_DRV;
        DDS_Octet SleepRequestTo_PSUIO_DRV;
        DDS_Octet VehicePowerState_PSUIO_DRV;

    } dds_GCS_LEFT_2_PSUIO_DRV_t ;

    NDDSUSERDllExport extern const char *dds_GCS_LEFT_2_PSUIO_DRV_tTYPENAME;

    #define REDA_SEQUENCE_USER_API
    #define T dds_GCS_LEFT_2_PSUIO_DRV_t
    #define TSeq dds_GCS_LEFT_2_PSUIO_DRV_tSeq
    #define REDA_SEQUENCE_EXCLUDE_C_METHODS
    #define REDA_SEQUENCE_USER_CPP
    #include <reda/reda_sequence_decl.h>

    #define REDA_SEQUENCE_USER_API
    #define T dds_GCS_LEFT_2_PSUIO_DRV_t
    #define TSeq dds_GCS_LEFT_2_PSUIO_DRV_tSeq
    #define REDA_SEQUENCE_EXCLUDE_STRUCT
    #define REDA_SEQUENCE_USER_CPP
    #include <reda/reda_sequence_decl.h>

    NDDSUSERDllExport extern RTI_BOOL
    dds_GCS_LEFT_2_PSUIO_DRV_t_initialize(dds_GCS_LEFT_2_PSUIO_DRV_t* sample);

    NDDSUSERDllExport extern dds_GCS_LEFT_2_PSUIO_DRV_t*
    dds_GCS_LEFT_2_PSUIO_DRV_t_create(void);

    #ifndef RTI_CERT
    NDDSUSERDllExport extern RTI_BOOL
    dds_GCS_LEFT_2_PSUIO_DRV_t_finalize(dds_GCS_LEFT_2_PSUIO_DRV_t* sample);

    NDDSUSERDllExport extern void
    dds_GCS_LEFT_2_PSUIO_DRV_t_delete(dds_GCS_LEFT_2_PSUIO_DRV_t* sample);
    #endif

    NDDSUSERDllExport extern RTI_BOOL
    dds_GCS_LEFT_2_PSUIO_DRV_t_copy(dds_GCS_LEFT_2_PSUIO_DRV_t* dst, const dds_GCS_LEFT_2_PSUIO_DRV_t* src);

    #if (defined(RTI_WIN32) || defined(RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
    /* If the code is building on Windows, stop exporting symbols. */
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif

    #ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* dds_system_types */

