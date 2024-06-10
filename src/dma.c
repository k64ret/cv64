/**
 * @file dma.c
 *
 * This file defines functions involved with direct memory access with the cartridge.
 */

#include <ultra64.h>
#include "cv64.h"

extern OSIoMesg dmaIoMesgBuf;
extern OSMesgQueue dmaIoMesgQueue;
extern OSPiHandle* gCartHandle;

void dma_init_cart(void) {
    gCartHandle = osCartRomInit();
}

static void dma_read_write(OSPiHandle* piHandle, s32 direction, void* dest, void* src, s32 len) {
    if (direction == OS_READ) {
        osWritebackDCache(dest, len);
        osInvalDCache(dest, len);
        osInvalICache(dest, len);
    } else {
        osWritebackDCache(dest, len);
    }

    dmaIoMesgBuf.hdr.pri      = OS_MESG_PRI_NORMAL;
    dmaIoMesgBuf.hdr.retQueue = &dmaIoMesgQueue;
    dmaIoMesgBuf.dramAddr     = dest;
    dmaIoMesgBuf.devAddr      = (u32) src;
    dmaIoMesgBuf.size         = len;

    osEPiStartDma(piHandle, &dmaIoMesgBuf, direction);
    osRecvMesg(&dmaIoMesgQueue, NULL, OS_MESG_BLOCK);
}

void dma_rom_copy(void* src, void* dest, s32 len) {
    dma_read_write(gCartHandle, OS_READ, dest, src, len);
}
