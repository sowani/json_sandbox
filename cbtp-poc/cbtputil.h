#ifndef CBTPUTIL_H
#define CBTPUTIL_H

#include "cbtp.h"

cbtpCommand* createCommandBlock (CBTP_COMMAND cmd, BYTE blkNum,
                                 unsigned short blkSize,
                                 BYTE myBlk, BYTE status);
cbtpData* createDataBlock (BYTE blkNum, unsigned short offset,
                           BYTE *data, int size);
cbtpBlock* createCbtpBlock();

#endif /* CBTPUTIL_H */
