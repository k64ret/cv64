#ifndef DMAMGR_H
#define DMAMGR_H

#include "object.h"

typedef struct {
    u8* data_ROM_start_address;
    u8* data_RAM_start_address;
    u32 compressed_data_size;
    s32 file_ID;
    void* field_0x10;
} DMAMgr_file_info;

typedef struct {
    u8 chunk_buffer[2048];
    u8* ROM_address_chunk;
    u8* ROM_address_chunk_current_byte_to_load; // Added by +1
    s32 data_chunk_read_limit;    // Ex. 0xA800, Substracted by -800 when
                                  // "file_bytes_left_to_read" is equal to this
                                  // variable
    s32 data_bytes_left_to_read;  // Ex. 0xAFFF, Substracted by -1
    s32 chunk_bytes_left_to_read; // Substracted by -1
    u16 field_0x814;
    u16 field_0x816;
    u8* ptr_byte_to_load_from_chunk_buffer;
    u8* field_0x81C;
    u8* field_0x820;
    u32 field_0x824;
    u8* data_ROM_start_address;
    u8* data_RAM_start_address;
    u32 data_size;
    u32 field_0x834;
    u32 data_alignment;
    u32 field_0x83C;
    s32 file_ID;
    u16 field_0x844;
    u16 field_0x846;
    DMAMgr_file_info file_info[16];
} DMAChunkMgr_t;

// ID: 0x0004
// Real name: obj_decode (based on leftover strings from LoD)
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[20];
    DMAChunkMgr_t* DMAChunkMgr;
    u8 field_0x38[60];
} DMAMgr;

extern DMAMgr* ptr_DMAMgr;
extern void* DMAMgr_loadNisitenmaIchigoFile(DMAMgr* this, s32 file_ID,
                                            u32 dest_start, void* param_4);

#endif
