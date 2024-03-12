#ifndef CV64_H
#define CV64_H

#include "gfx/model_info.h"
#include "math.h"
#include <ultra64.h>

#define CV64_BIT(num) (1 << (num))
/**
 * Check if `bits` is set in `value`.
 */
#define BITS_HAS(value, bits) ((value) & (bits))
/**
 * Set `bit` in `value`.
 */
#define BITS_SET(value, bits) ((value) |= (bits))
/**
 * Unset `bit` in `value`.
 */
#define BITS_UNSET(value, bits) ((value) &= ~(bits))

typedef u8 Addr[];

extern Gfx* gDisplayListHead; // 0x800B49E0

extern void end_master_display_list();
extern s32
menuButton_selectNextOption(s32* option, s16* param_2, s16 number_of_options);
extern u32 NisitenmaIchigo_checkAndStoreLoadedFile(u32 file_ID);
extern void func_800010A0_1CA0();
extern void func_8001248C_1308C();
extern void func_8000C6D0();
extern void func_80012400();
extern void func_80005658();
extern u32 getMapEventFlagID(s16 stage_ID);

#define NPTR             0
#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))
#define ARRAY_START(arr) &arr[0]                // Get start address of array
#define ARRAY_END(arr)   &arr[ARRAY_COUNT(arr)] // Get end address of array

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

// clang-format off

/**
 * Obtain the un-mapped address of data from a Nisitenma-Ichigo file
 * This is needed if data is trying to be accessed when said data is not mapped by the TLB
 * (which usually happens with data within overlays)
 */
#define GET_UNMAPPED_ADDRESS(file_ID, data_ptr)                                                     \
    (u32) sys.Nisitenma_Ichigo_loaded_files_ptr[file_ID] + ((u32) data_ptr & 0xFFFFFF)

// clang-format on

extern const u32 MENU_RED_BACKGROUND_DL;
#define NI_ASSETS_MENU_BUFFER_SIZE 0x30000

// Nisitenma-Ichigo file IDs
#define NI_ASSETS_KONAMI_KCEK_LOGOS 0x5D
#define NI_ASSETS_MENU              0x60
#define NI_ASSETS_FILE_SELECT       0x65
#define NI_OVL_EASY_MODE_ENDING_MSG 0xBB

#endif // CV64_H
