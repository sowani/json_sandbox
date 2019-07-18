/**
 * Client program to demo vcan library.
 */
#include "vcan.h"

int main (void)
{
  int ret = 0;
  struct can_frame frame;
  struct CANdevice can_dev;
  char devName[] = "vcan0";

  /* Open CAN device. */
  PRINT ("opening device %s\n", devName);
  ret = vcan_init (&can_dev, devName);
  if (ret == -1)
  {
    PRINT ("vcan_init failed, exiting.\n");
    return (ret);
  }

  /* Initialise CAN frame data. */
  frame.can_id = 0x123;
  frame.can_dlc = 2;
  frame.data[0] = 0x11;
  frame.data[1] = 0x22;
  frame.data[2] = frame.data[3] = frame.data[4] = 0x00;
  frame.data[5] = frame.data[6] = frame.data[7] = 0x00;

  /* Send the frame 1 via CAN device. */
  PRINT ("sending frame 1\n");
  ret = vcan_send (&can_dev, &frame);
  if (ret == -1)
  {
    PRINT ("vcan_send failed, exiting.\n");
    vcan_fini (&can_dev);
    return (ret);
  }

  /* Send the frame 2 via CAN device. */
  frame.can_id = 0x999;  /* End of transmission */
  frame.can_dlc = 2;
  frame.data[0] = 0x99;
  frame.data[1] = 0x99;
  PRINT ("sending frame 2\n");
  ret = vcan_send (&can_dev, &frame);
  if (ret == -1)
  {
    PRINT ("vcan_send failed, exiting.\n");
    vcan_fini (&can_dev);
    return (ret);
  }

  /* Close CAN device. */
  ret = vcan_fini (&can_dev);
  if (ret == -1)
  {
    PRINT ("vcan_fini failed, exiting.\n");
    return (ret);
  }

  return (0);
}
