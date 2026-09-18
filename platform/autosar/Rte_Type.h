#ifndef RTE_TYPE_H
#define RTE_TYPE_H

#include "Std_Types.h"

/* --------------------------------------------------------------------------
 * Virtual RTE application data types
 * -------------------------------------------------------------------------- */

typedef struct
{
    uint8 PDIO_FL_Driver_Door_Switch_State;
    uint8 PDIO_FL_Driver_Door_Unlock_State;
    uint8 PDIO_FL_PwrDrAvailability;
    float PDIO_FL_PwrDrAngle;
    uint8 PDIO_FL_PwrDrStatus;
    uint8 PDIO_FL_PwrDrSwingActrStatus;
    uint8 PDIO_FL_PwrDrErrorState;
    uint8 PDIO_FL_PwrDrAntiPinchStatus;
    float PDIO_FL_PwrDrAngleSpeed;
    uint8 PDIO_FL_InsdOpnClsSwStatus;
    uint8 PDIO_FL_OtsdOpnClsSwStatus;
    uint8 PDIO_FL_SleepReady;
    uint8 PDIO_FL_WakeupRequest;
    uint8 PDIO_FL_CinchingStatus;
    uint8 PDIO_FL_ActiveHoldingState;
} Cabin_Door_PDIO_FL_t;

typedef struct
{
    uint8  PwrDrOpnClsCmd_PDIO_FL;
    uint8  PwrDrSnsrStatus_RODS_FL_PDIO_FL;
    float  PwrDrSnsrStopAngle_RODS_FL_PDIO_FL;
    uint8  PwrDrSnsrStopRequest_RODS_FL_PDIO_FL;
    uint8  ACU_CrshActvSta_PDIO_FL;
    uint16 ACU_CrshTyp_PDIO_FL;
    uint8  Door_LockUnlockCmd_PDIO_FL;
    uint8  IMU_LatAccelSigSta_PDIO_FL;
    uint8  IMU_LongAccelSigSta_PDIO_FL;
    float  IMU_LatAccelVal_PDIO_FL;
    float  IMU_LongAccelVal_PDIO_FL;
    uint16 VehicleSpeedState_PDIO_FL;
    uint8  VCU_GearPosSta_PDIO_FL;
    float  PwrDrOpnAngVal_PDIO_FL;
    uint8  SleepRequestTo_PDIO_FL;
    uint8  SleepCommandTo_PDIO_FL;
    uint8  VehiclePowerState_PDIO_FL;
} GCS_LEFT_2_PDIO_FL_t;

#endif /* RTE_TYPE_H */
