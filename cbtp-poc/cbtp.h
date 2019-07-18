#ifndef CBTP_H
#define CBTP_H

/* For creating library, some of the content will need re-location */

#define BLOCK_INDEX_VERSION 0

#define BLOCKINDEX 0
#define BLOCKALL 255

typedef unsigned char BYTE;

typedef enum
{
  CMD_BEGIN_BLOCK_TRANSFER = 0,
  CMD_FINISH_BLOCK_TRANSFER,
  CMD_CANCEL_BLOCK_TRANSFER,
  CMD_SUSPEND_BLOCK_TRANSFER,
  CMD_RESUME_BLOCK_TRANSFER,
  CMD_REQUEST_BLOCK_TRANSFER,
  CMD_RESULT_OF_BLOCK_TRANSFER,
  CMD_MAX_COMMANDS
} CBTP_COMMAND;

enum CBTP_DESC_FLAGS
{
  CBTP_DESC_PUSH_ALLOWED = 0,
  CBTP_DESC_PULL_ALLOWED,
  CBTP_DESC_AUTOPUSH,
  CBTP_DESC_STARTS_RESUMED,
  CBTP_DESC_MAX_FLAGS
};

typedef enum
{
  CBTP_CMDSTAT_SUCCESS = 0,
  CBTP_CMDSTAT_CANCELLED,
  CBTP_CMDSTAT_DATA_OUT_OF_SEQUENCE,
  CBTP_CMDSTAT_NOT_ENOUGH_DATA,
  CBTP_CMDSTAT_TOO_MUCH_DATA,
  CBTP_CMDSTAT_NO_SUCH_BLOCK,
  CBTP_CMDSTAT_BUSY,
  CBTP_CMDSTAT_PUSH_NOT_ALLOWED,
  CBTP_CMDSTAT_PULL_NOT_ALLOWED,
  CBTP_CMDSTAT_MAX_STATUS
} CBTP_COMMAND_STATUS;

enum CBTP_BLOCK_REF
{
  CBTP_MY_BLOCK = 0,
  CBTP_YOUR_BLOCK,
  CBTP_MAX_BLOCK_REF
};

typedef struct CBTP_COMMAND
{
  BYTE cmdBlockNum;
  BYTE cmdOpcode;      /* One of CBTP_COMMANDS */
  union DataPayload
  {
    unsigned short blockLength;
    struct
    {
      BYTE myBlock;
      BYTE status;
    };
  } dataPayload;
} cbtpCommand;

typedef struct CBTP_DATA
{
  BYTE dataBlockNum;
  unsigned short dataOffset;  /* Defines max block size 2^16 == 64K */
  BYTE dataPayload[5];
} cbtpData;

typedef struct BLOCK_HEADER
{
  BYTE BlockIndexVersionCode;
  BYTE BlockCount;
} blockHeader;

typedef struct BLOCK_DESCRIPTOR
{
  unsigned short blockType;
  unsigned short flags;
  unsigned short maxSize;
  unsigned short currentSize;
  unsigned short burstSize;
} blockDescriptor;

typedef struct CBTP_BLOCK
{
  struct BLOCK_HEADER blockHeader;
  struct BLOCK_DESCRIPTOR blockDescriptor;
  /* TODO - Data will follow here? */
} cbtpBlock;

int sendCBTPCommand (struct CBTP_BLOCK *blk);
int sendCBTPData (struct CBTP_BLOCK *blk);
int pushCBTPBlock (struct CBTP_BLOCK *blk);
int pullCBTPBlock (int blockNum);

#endif /* CBTP_H */
