#ifndef CV64_H
#define CV64_H

#include "gfx/model_info.h"
#include "math.h"
#include <ultra64.h>

#define CV64_BIT(num) (1 << (num))

typedef u8 Addr[];

extern Gfx* gDisplayListHead; // 0x800B49E0

extern void end_master_display_list();

#define NPTR             0
#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))
#define ARRAY_START(arr) &arr[0]                // Get start address of array
#define ARRAY_END(arr)   &arr[ARRAY_COUNT(arr)] // Get end address of array

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

// clang-format off

// Obtain the un-mapped address of data from a Nisitenma-Ichigo file
// This is needed if data is trying to be accessed when said data is not mapped by the TLB
// (which usually happens with data within overlays)
#define GET_UNMAPPED_ADDRESS(file_ID, data_ptr)                                                     \
    (u32) sys.Nisitenma_Ichigo_loaded_files_ptr[file_ID] + ((u32) data_ptr & 0xFFFFFF)

// clang-format on

// Nisitenma-Ichigo file IDs
#define NI_ASSETS_KONAMI_KCEK_LOGOS 0x5D
#define NI_ASSETS_FILE_SELECT       0x65
#define NI_OVL_EASY_MODE_ENDING_MSG 0xBB

#endif // CV64_H
