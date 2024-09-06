#ifndef CONTROLLER_PAK_H
#define CONTROLLER_PAK_H

#include "controller.h"

void contpak_get_ins_status(OSContStatus cont_status[]);
void contpak_init_all(void);
s32 contpak_init(u8 cont_no);
s32 contpak_alloc_file(u8 cont_no, OSPfsState* pfs_state, int file_size, s32* file_no);
s32 contpak_del_file(u8 cont_no, OSPfsState* pfs_state);
s32 contpak_find_file(u8 cont_no, OSPfsState* pfs_state, s32* file_no);
s32 contpak_get_file_state(u8 cont_no, s32 file_no, OSPfsState* pfs_state);
s32 contpak_get_num_files(u8 cont_no, s32* max_files, s32* files_used);
s32 contpak_get_free_blks(u8 cont_no, s32* remaining);
s32 contpak_is_plug(u8* bitpattern);
s32 contpak_read_file(u8 cont_no, s32 file_no, int offset, int nbytes, u8* buf);
s32 contpak_write_file(u8 cont_no, s32 file_no, int offset, int nbytes, u8* buf);
s32 contpak_check_rumble_pak(u8 cont_no);
s32 contpak_check_ins_err(u8 cont_no);
void contpak_8001AAA8(u8 cont_no);
void contpak_8001AB18(u8 cont_no);
s32 contpak_repair_id(u8 cont_no);

#endif
