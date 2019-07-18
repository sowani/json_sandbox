#include <stdio.h>
#include <stdlib.h>
#include "cbtputil.h"

cbtpCommand* createCommandBlock (CBTP_COMMAND cmd, BYTE blkNum, unsigned short blkSize,
                                 BYTE myBlk, BYTE status)
{
  cbtpCommand *newCmdBlk = (cbtpCommand *) malloc (sizeof (cbtpCommand));
  if (newCmdBlk == NULL)
    return ((cbtpCommand *) NULL);
  else
  {
    switch (cmd)
    {
      case CMD_BEGIN_BLOCK_TRANSFER:
        newCmdBlk->cmdBlockNum = blkNum;
        newCmdBlk->cmdOpcode = CMD_BEGIN_BLOCK_TRANSFER;
        newCmdBlk->dataPayload.blockLength = blkSize;
        break;
      case CMD_FINISH_BLOCK_TRANSFER:
        newCmdBlk->cmdBlockNum = blkNum;
        newCmdBlk->cmdOpcode = CMD_FINISH_BLOCK_TRANSFER;
        break;
      case CMD_CANCEL_BLOCK_TRANSFER:
        newCmdBlk->cmdBlockNum = blkNum;
        newCmdBlk->cmdOpcode = CMD_CANCEL_BLOCK_TRANSFER;
        newCmdBlk->dataPayload.myBlock = myBlk;
        break;
      case CMD_SUSPEND_BLOCK_TRANSFER:
        newCmdBlk->cmdBlockNum = blkNum;
        newCmdBlk->cmdOpcode = CMD_SUSPEND_BLOCK_TRANSFER;
        newCmdBlk->dataPayload.myBlock = myBlk;
        break;
      case CMD_RESUME_BLOCK_TRANSFER:
        newCmdBlk->cmdBlockNum = blkNum;
        newCmdBlk->cmdOpcode = CMD_RESUME_BLOCK_TRANSFER;
        newCmdBlk->dataPayload.myBlock = myBlk;
        break;
      case CMD_REQUEST_BLOCK_TRANSFER:
        newCmdBlk->cmdBlockNum = blkNum;
        newCmdBlk->cmdOpcode = CMD_REQUEST_BLOCK_TRANSFER;
        break;
      case CMD_RESULT_OF_BLOCK_TRANSFER:
        newCmdBlk->cmdBlockNum = blkNum;
        newCmdBlk->cmdOpcode = CMD_RESULT_OF_BLOCK_TRANSFER;
        newCmdBlk->dataPayload.myBlock = myBlk;
        newCmdBlk->dataPayload.status = status;
        break;
      default:
        break;
    }
  }
  return (newCmdBlk);
}

cbtpData* createDataBlock (BYTE blkNum, unsigned short offset,
                           BYTE *data, int size)
{
  cbtpData *newDataBlk = (cbtpData *) malloc (sizeof (cbtpData));
  if (newDataBlk == NULL)
    return ((cbtpData *) NULL);
  else
  {
    int i = 0;
    newDataBlk->dataBlockNum = blkNum;
    newDataBlk->dataOffset = offset;
    for (i = 0; i < size; i++)
      newDataBlk->dataPayload[i] = *(data+i);
  }
  return (newDataBlk);
}

cbtpBlock* createCbtpBlock()
{

}
