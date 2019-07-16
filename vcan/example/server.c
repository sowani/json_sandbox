/**
 * Server program to demo vcan library.
 */
#include "vcan.h"

int run = 1;

/* Message processing function to be registered for CAN device. */
int printMsg (struct can_frame *frame)
{
  int i = 0;
  printf ("message id = %x\n", frame->can_id);
  printf ("message data = ");
  for (i = 0; i < 8; i++)
    printf ("%x ", frame->data[i]);
  printf ("\n");
  if (frame->can_id == 0x999)
    run = 0;
  return (0);
}

int main (void)
{
  struct CANdevice can_dev;
  char devName[] = "vcan0";
  int ret = 0;

  /* Open CAN device. */
  PRINT ("opening device %s\n", devName);
  ret = vcan_init (&can_dev, devName);
  if (ret == -1)
  {
    PRINT ("vcan_init failed, exiting.\n");
    return ret;
  }

  /* Register message processor function for the device. */
  ret = vcan_registerFn (&can_dev, printMsg);
  if (ret == -1)
  {
    PRINT ("vcan_registerFn failed, exiting.\n");
    /* Try to close CAN device. */
    vcan_fini (&can_dev);
    return ret;
  }

  /* Receive CAN messages until asked to stop. */
  while (run == 1)
  {
    PRINT ("receiving message\n");
    ret = vcan_receive (&can_dev);
    if (ret == -1)
    {
      PRINT ("vcan_receive failed, exiting.\n");
      /* Try to close CAN device. */
      vcan_fini (&can_dev);
      return (ret);
    }
  }

  /* Close CAN device. */
  PRINT ("closing device\n");
  ret = vcan_fini (&can_dev);
  if (ret == -1)
  {
    PRINT ("vcan_fini failed, exiting.\n");
    return ret;
  }

  return (0);
}
