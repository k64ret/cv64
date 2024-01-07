#ifndef CV64_H
#define CV64_H

#define CV64_BIT(num) (1 << (num))

#include <ultra64.h>

typedef u8 Addr[];

extern Gfx* gDisplayListHead; // 0x800B49E0

extern void end_master_display_list(void);

#define NPTR 0

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))

#endif // CV64_H
