#ifndef SOUND_H
#define SOUND_H

#include "math.h"
#include <ultra64.h>

#define STOP_SOUND(sound_ID) (0x8000 | sound_ID)

extern u8 play_sound(u16 sound_ID);
extern u8 play_sound_in_position(u16 sound_ID, vec3f* position);
extern u8 play_sound_in_position_and_set_volume(u16 sound_ID, vec3f* position,
                                                f32 volume_multiplier);

// Sound IDs (officially referred to as "sound codes")
#define SD_TOU_TURO_DOOR_CLOSE 0x11B
#define SD_ROSE_DOOR_CLOSING   0x29B
#define SD_ROSE_DOOR_CLOSE     0x27B

#endif
