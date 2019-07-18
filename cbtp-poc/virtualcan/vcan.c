/*
 *  vcan.c
 *
 *  Created on: 15-Jul-2019
 *  Author: Atul Sowani
 */
#include "vcan.h"

/**
 * @brief vcan_init: Initialise CAN device.
 *
 * @param struct CANdevice* vcan - CAN device to be opened.
 * @param const char *canDeviceName - Name the CAN device should be
 *        identified with.
 *
 * @return int - 0 on success, -1 on failure.
 *
 */
int vcan_init (struct CANdevice *vcan, const char *canDeviceName)
{
    int i = 0;
    int zero = 0;
	struct ifreq ifr;

    PRINT ("initializing device %s\n", canDeviceName);
    vcan->canRawSock = 0;
    memcpy ((struct sockaddr_can *) &vcan->addr, (const void *) &zero,
            sizeof (struct sockaddr_can));
    for (i = 0; i < MAX_CAN_RECEIVERS; i++)
        vcan->canReceivers[i] = 0;
    vcan->currentClientsCount = 0;
    bzero (vcan->errMsg, (ERRMSG_SIZE * sizeof(char)));
    bzero (vcan->deviceName, (CAN_DEVICENAME_SIZE * sizeof(char)));

	strncpy(vcan->deviceName, canDeviceName, CAN_DEVICENAME_SIZE-1);
	vcan->deviceName[CAN_DEVICENAME_SIZE-1] = '\0';
    PRINT ("can device name = %s\n", vcan->deviceName);

	strncpy(ifr.ifr_name, vcan->deviceName, IFNAMSIZ - 1);
	ifr.ifr_name[IFNAMSIZ - 1] = '\0';
	ifr.ifr_ifindex = if_nametoindex(ifr.ifr_name);
	if (!ifr.ifr_ifindex)
    {
		PRINT ("ERROR: %d\n", strerror_r(errno, vcan->errMsg,
                                         sizeof(vcan->errMsg)));
		return (-1);
	}
	vcan->addr.can_family = AF_CAN;
	vcan->addr.can_ifindex = ifr.ifr_ifindex;

	if ((vcan->canRawSock = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0)
    {
		PRINT ("ERROR: %d\n", strerror_r(errno, vcan->errMsg,
                                         sizeof(vcan->errMsg)));
		return (-1);
	}

	if (bind(vcan->canRawSock, (struct sockaddr *) &vcan->addr,
              sizeof(vcan->addr)) < 0)
    {
		PRINT ("ERROR: %d\n", strerror_r(errno, vcan->errMsg,
                                         sizeof(vcan->errMsg)));
		return (-1);
	}

	return (0);
}

/**
 * @brief vcan_send: Transmit a CAN frame via CAN device.
 *
 * @param struct CANdevice* vcan - CAN device to be used.
 * @param struct can_frame* canDeviceName - CAN frame to be transmitted.
 *
 * @return int - 0 on success, -1 on failure.
 *
 */
int vcan_send (struct CANdevice *vcan, struct can_frame *frame)
{
	if (write(vcan->canRawSock, frame, CANFRAMESIZE) != CANFRAMESIZE)
    {
        PRINT ("ERROR: %d\n", strerror_r(errno, vcan->errMsg,
                                         sizeof(vcan->errMsg)));
		return (-1);
	}
	return (0);
}

/**
 * @brief vcan_receive: Receive a CAN frame via CAN device and invoke
 *                      registered frame processor function.
 *
 * @param struct CANdevice* vcan - CAN device to be used.
 *
 * @return int - 0 on success, -1 on failure.
 *
 */
int vcan_receive(struct CANdevice *vcan)
{
	struct can_frame frame;
	fd_set rdfs;

	sigset_t sigmask;
	struct timespec timeout;
	timeout.tv_nsec = 0;
	timeout.tv_sec = 60; // was 0
	memset(&sigmask, 0, sizeof(sigset_t));

	FD_ZERO(&rdfs);
	FD_SET(vcan->canRawSock, &rdfs);

    PRINT ("in vcan_receive\n");
	if ((pselect(vcan->canRawSock+1, &rdfs, NULL, NULL, &timeout, &sigmask)) <= 0)
		return (-1);

	if (FD_ISSET(vcan->canRawSock, &rdfs))
    {
        int nBytes = 0;
        int clientIndex = 0;
		nBytes = read(vcan->canRawSock, &frame, CAN_MTU);
        PRINT ("%d bytes read\n", nBytes);
		if (nBytes <= 0)
        {
			PRINT ("ERROR: %s: %d\n", vcan->deviceName,
                   strerror_r(errno, vcan->errMsg, sizeof(vcan->errMsg)));
			return (-1);
		}

		for(clientIndex=0; clientIndex<vcan->currentClientsCount; clientIndex++)
        {
            PRINT ("calling registered function\n");
			vcan->canReceivers[clientIndex](&frame);
		}
	}
    else
        PRINT ("FD_ISSET failed\n");

	return (0);
}

/**
 * @brief vcan_registerFn: Frame processor function (every device must
 *                         register one).
 *
 * @param struct CANdevice* vcan - CAN device to be used.
 * @param struct can_frame* canDeviceName - CAN frame to be transmitted.
 *
 * @return int - 0 on success, -1 on failure.
 *
 */
int vcan_registerFn(struct CANdevice *vcan, CAN_MESSAGE_RX_FUNCTION fun)
{
	if (fun == NULL)
		return (-1);

	if (vcan->currentClientsCount >= MAX_CAN_RECEIVERS)
    {
		PRINT ("ERROR: registerFn: Max number of clients reached!\n");
		return (-1);
	}

	vcan->canReceivers[vcan->currentClientsCount] = fun;
	vcan->currentClientsCount += 1;
	return (0);
}

/**
 * @brief vcan_fini: Shutdown CAN device.
 *
 * @param struct CANdevice* vcan - CAN device to be used.
 *
 * @return int - 0 on success, -1 on failure.
 *
 */
int vcan_fini (struct CANdevice *vcan)
{
    return close(vcan->canRawSock);
}
