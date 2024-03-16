#ifndef SOUND_H
#define SOUND_H

#include "math.h"
#include <ultra64.h>

#define STOP_SOUND(sound_ID) (0x8000 | sound_ID)

extern u8 play_sound(u16 sound_ID);
extern u8 play_sound_in_position(u16 sound_ID, vec3f* position);
extern u8
play_sound_in_position_and_set_volume(u16 sound_ID, vec3f* position, f32 volume_multiplier);

// Sound IDs (officially referred to as "sound codes")
#define SD_INVALID             0x000

// Control sounds
// These are not supposed to play audio. Rather, they do different actions
// if their sound IDs are played.

// Assumption
#define SD_CTRL_RESET_AUDIO_TRACK_STATE             0x001
// Assumption
#define SD_CTRL_RESET_AUDIO_STATE             0x002
// This can be used to stop the music temporarily
#define SD_CTRL_SET_AUDIO_TO_STANDBY             0x003
// Resumes the audio set to standby in the entry above
#define SD_CTRL_RESUME_AUDIO             0x004
#define SD_CTRL_ENABLE_STEREO_AUDIO             0x005
#define SD_CTRL_ENABLE_MONO_AUDIO             0x006
// All of these use different sound IDs, but call the same function
#define SD_CTRL_FADE_OUT_AUDIO             0x007
#define SD_CTRL_FADE_OUT_AUDIO             0x008
#define SD_CTRL_FADE_OUT_AUDIO             0x009
#define SD_CTRL_FADE_OUT_AUDIO                 0x00A
// Gradually increases audio speed up to a certain point
#define SD_CTRL_INCREASE_AUDIO_SPEED             0x00B
// If the audio is still increasing speed, this will stop the speed increase
#define SD_CTRL_STOP_AUDIO_INCREASE             0x00C
// Gradually decreases audio volume up to a certain point. Used when going into the Pause Menu.
#define SD_CTRL_DECREASE_AUDIO_VOLUME             0x00D
// Gradually increases audio volume up to a certain point. Used when exiting the Pause Menu.
#define SD_CTRL_INCREASE_AUDIO_VOLUME             0x00E
// Does nothing. Its code is empty
#define SD_CTRL_00F             0x00F

#define SD_TOU_TURO_DOOR_CLOSE 0x11B
#define SD_ROSE_DOOR_CLOSE     0x27B
#define SD_ROSE_DOOR_CLOSING   0x29B
#define SD_2E9                 0x2E9

#endif
