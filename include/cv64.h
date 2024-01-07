#ifndef CV64_H
#define CV64_H

#define CV64_BIT(num) (1 << (num))

#include "math.h"
#include <ultra64.h>

typedef u8 Addr[];

extern Gfx* gDisplayListHead; // 0x800B49E0

extern void end_master_display_list(void);
extern u8 play_sound(s16 sound_ID);
extern u8 play_sound_in_position(s16 sound_ID, vec3f* position);
extern u8 play_sound_in_position_and_set_volume(s16 sound_ID, vec3f* position,
                                                f32 volume_multiplier);
extern s32 rand(void);
extern f32 rand_f32(void);
extern void random_initSeed(void);
extern u16 random_range(u16 limit);

#define NPTR 0

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))

#endif // CV64_H
