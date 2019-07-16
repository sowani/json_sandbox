#ifndef VIRTUAL_CAN_H
#define VIRTUAL_CAN_H

#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can.h>
#include <linux/can/raw.h>

/**
 * CAN message constants.
 */
#define PRINT               printf
#define ERRMSG_SIZE         100
#define CAN_BUFFER_SIZE     20 
#define MAX_CAN_RECEIVERS   10
#define CAN_DEVICENAME_SIZE 8
#define CANPAYLOADLEN	    8
#define CANFRAMESIZE	    16

//typedef unsigned char uint8_t;
typedef int (*CAN_MESSAGE_RX_FUNCTION)(struct can_frame *frame);

/**
 * CAN device definition.
 */
struct CANdevice
{
    int canRawSock; // can raw socket
    struct sockaddr_can addr;
    CAN_MESSAGE_RX_FUNCTION canReceivers[MAX_CAN_RECEIVERS];
    int currentClientsCount;
    char errMsg[ERRMSG_SIZE];
    char deviceName[CAN_DEVICENAME_SIZE];
};

/**
 * CAN helper functions.
 */
int vcan_init (struct CANdevice*, const char *canDeviceName);
int vcan_send (struct CANdevice*, struct can_frame *frame);
int vcan_receive (struct CANdevice*);
int vcan_registerFn (struct CANdevice*, CAN_MESSAGE_RX_FUNCTION fun);
int vcan_fini (struct CANdevice*);
#endif
