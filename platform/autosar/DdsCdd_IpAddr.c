#include "DdsCdd_IpAddr.h"

/* ============================================================
 * Configuration
 * ============================================================ */

#define DDSCDD_IP_QUEUE_SIZE    (10U)

/* ============================================================
 * Queue item
 * ============================================================ */

typedef struct
{
    TcpIp_LocalAddrIdType LocalAddrId;
    TcpIp_IpAddrStateType State;
} DdsCdd_IpQueueItemType;


/* ============================================================
 * Queue data
 * ============================================================ */

static DdsCdd_IpQueueItemType
    DdsCdd_IpQueue[DDSCDD_IP_QUEUE_SIZE];

static uint8 DdsCdd_IpQueueHead  = 0U;
static uint8 DdsCdd_IpQueueTail  = 0U;
static uint8 DdsCdd_IpQueueCount = 0U;

/* Debug / diagnostic */
static uint32 DdsCdd_IpQueueOverflowCount = 0U;


/* ============================================================
 * Internal Queue Push
 *
 * IMPORTANT:
 * Caller must hold OsResource_DdsIpQueue.
 * ============================================================ */

static Std_ReturnType DdsCdd_IpQueuePush(
    TcpIp_LocalAddrIdType LocalAddrId,
    TcpIp_IpAddrStateType State)
{
    if (DdsCdd_IpQueueCount >= DDSCDD_IP_QUEUE_SIZE)
    {
        DdsCdd_IpQueueOverflowCount++;
        return E_NOT_OK;
    }

    DdsCdd_IpQueue[DdsCdd_IpQueueTail].LocalAddrId = LocalAddrId;
    DdsCdd_IpQueue[DdsCdd_IpQueueTail].State       = State;

    DdsCdd_IpQueueTail++;

    if (DdsCdd_IpQueueTail >= DDSCDD_IP_QUEUE_SIZE)
    {
        DdsCdd_IpQueueTail = 0U;
    }

    DdsCdd_IpQueueCount++;

    return E_OK;
}


/* ============================================================
 * Internal Queue Pop
 *
 * IMPORTANT:
 * Caller must hold OsResource_DdsIpQueue.
 * ============================================================ */

static Std_ReturnType DdsCdd_IpQueuePop(
    DdsCdd_IpQueueItemType *Item)
{
    if ((Item == NULL_PTR) ||
        (DdsCdd_IpQueueCount == 0U))
    {
        return E_NOT_OK;
    }

    *Item = DdsCdd_IpQueue[DdsCdd_IpQueueHead];

    DdsCdd_IpQueueHead++;

    if (DdsCdd_IpQueueHead >= DDSCDD_IP_QUEUE_SIZE)
    {
        DdsCdd_IpQueueHead = 0U;
    }

    DdsCdd_IpQueueCount--;

    return E_OK;
}



void DdsCdd_LocalIpAddrAssignmentChg_Async(
    TcpIp_LocalAddrIdType LocalAddrId,
    TcpIp_IpAddrStateType State)
{
    Std_ReturnType ret;

    GetResource(OsResource_DdsIpQueue);

    ret = DdsCdd_IpQueuePush(
        LocalAddrId,
        State);

    ReleaseResource(OsResource_DdsIpQueue);


    if (ret == E_OK)
    {
        /*
         * Wake DDS task.
         *
         * Replace task/event names with the actual configuration.
         */
        SetEvent(
            DdsCddIpAddr_Task,
            OsEventDdsIpAssignment);
    }
    else
    {
        /*
         * Queue full.
         *
         * Optional:
         * DET / DEM / debug logging.
         */
    }
}

void DdsCdd_ProcessIpAssignmentQueue(void)
{
    DdsCdd_IpQueueItemType item;
    Std_ReturnType ret;

    for (;;)
    {
        /*
         * Queue access only.
         *
         * Priority ceiling applies only inside this section.
         */
        GetResource(OsResource_DdsIpQueue);

        ret = DdsCdd_IpQueuePop(&item);

        ReleaseResource(OsResource_DdsIpQueue);


        if (ret != E_OK)
        {
            /* Queue empty */
            break;
        }


        /*
         * IMPORTANT:
         *
         * OsResource_DdsIpQueue is NOT held here.
         *
         * RTI/DDS may now use its own resources
         * independently.
         */
        printf("[DdsCdd_LocalIpAddrAssignmentChg] LocalAddrId=%d, State=%d\n", item.LocalAddrId, item.State);
        DdsCdd_LocalIpAddrAssignmentChg(
            item.LocalAddrId,
            item.State);
    }
}