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

#endif // CV64_H
