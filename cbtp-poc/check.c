/* Test program to check createCommandBlock() */
#include "cbtputil.c"

void checkCommands (void)
{
  cbtpCommand *cmd;

  printf ("createCommandBlock() tests:\n");

  cmd = createCommandBlock (CMD_BEGIN_BLOCK_TRANSFER, 7, 10, 0, 0);
  printf ("block num = %x\n", cmd->cmdBlockNum);
  printf ("cmd opcode = %x\n", cmd->cmdOpcode);
  printf ("block length = %d\n\n", cmd->dataPayload.blockLength);

  cmd = createCommandBlock (CMD_FINISH_BLOCK_TRANSFER, 7, 0, 0, 0);
  printf ("block num = %x\n", cmd->cmdBlockNum);
  printf ("cmd opcode = %x\n\n", cmd->cmdOpcode);

  cmd = createCommandBlock (CMD_CANCEL_BLOCK_TRANSFER, 7, 0, 0xFF, 0);
  printf ("block num = %x\n", cmd->cmdBlockNum);
  printf ("cmd opcode = %x\n", cmd->cmdOpcode);
  printf ("myblock = %x\n\n", cmd->dataPayload.myBlock);

  cmd = createCommandBlock (CMD_SUSPEND_BLOCK_TRANSFER, 7, 0, 0xFF, 0);
  printf ("block num = %x\n", cmd->cmdBlockNum);
  printf ("cmd opcode = %x\n", cmd->cmdOpcode);
  printf ("myblock = %x\n\n", cmd->dataPayload.myBlock);

  cmd = createCommandBlock (CMD_RESUME_BLOCK_TRANSFER, 7, 0, 0xFF, 0);
  printf ("block num = %x\n", cmd->cmdBlockNum);
  printf ("cmd opcode = %x\n", cmd->cmdOpcode);
  printf ("myblock = %x\n\n", cmd->dataPayload.myBlock);

  cmd = createCommandBlock (CMD_REQUEST_BLOCK_TRANSFER, 7, 0, 0, 0);
  printf ("block num = %x\n", cmd->cmdBlockNum);
  printf ("cmd opcode = %x\n\n", cmd->cmdOpcode);

  cmd = createCommandBlock (CMD_RESULT_OF_BLOCK_TRANSFER, 7, 0, 0xFF, 1);
  printf ("block num = %x\n", cmd->cmdBlockNum);
  printf ("cmd opcode = %x\n", cmd->cmdOpcode);
  printf ("status = %x\n", cmd->dataPayload.status);
}

void checkData()
{
  int i = 0;
  cbtpData *data;
  BYTE bytes[] = { 0x0a, 0x0b, 0x0c, 0x0d, 0x0e };

  printf ("createDataBlock() tests:\n");

  data = createDataBlock (10, 0, bytes, 5);
  printf ("block number = %d\n", data->dataBlockNum);
  printf ("data offset = %d\n", data->dataOffset);
  printf ("data = ");
  for (i = 0; i < 5; i++)
    printf ("%x ", data->dataPayload[i]);
  printf ("\n");
}

int main (void)
{
  checkCommands();
  checkData();
  return (0);
}
