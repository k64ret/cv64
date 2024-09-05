#ifndef CONTROLLER_PAK_H
#define CONTROLLER_PAK_H

#include "controller.h"

s32 contPak_getInsertedStatus(OSContStatus cont_status[]);
void contPak_initAllPaks();
s32 contPak_initPak(u8 cont_number);
s32 contPak_allocateFile(u8 cont_number, OSPfsState* pfs_state, int file_size, s32* file_no);
s32 contPak_deleteFile(u8 cont_number, OSPfsState* pfs_state);
s32 contPak_findFile(u8 cont_number, OSPfsState* pfs_state, s32* file_no);
s32 contPak_getFileState(u8 cont_number, s32 file_no, OSPfsState* pfs_state);
s32 contPak_getNumFiles(u8 cont_number, s32* max_files, s32* files_used);
s32 contPak_getFreeBlocks(u8 cont_number, s32* remaining);
s32 contPak_IsPlug(u8* bitpattern);
s32 contPak_readFile(u8 cont_number, s32 file_no, int offset, int nbytes, u8* data_buffer);
s32 contPak_writeFile(u8 cont_number, s32 file_no, int offset, int nbytes, u8* data_buffer);
s32 contPak_checkRumblePak(u8 cont_number);
s32 contPak_checkInsertedStatus(u8 cont_number);
void contPak_8001aaa8(u8 cont_number);
void contPak_8001ab18(u8 cont_number);
s32 contPak_repairID(u8 cont_number);

#endif
