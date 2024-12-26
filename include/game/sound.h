#ifndef SOUND_H
#define SOUND_H

#include "math.h"
#include <ultra64.h>

#define STOP_SOUND(sound_ID) (0x8000 | sound_ID)

/**
 * The `type` argument in `audioControlFadeOutType_setType`
 */
#define FADE_OUT_AUDIO_008 0
#define FADE_OUT_AUDIO_007 1
#define FADE_OUT_AUDIO_009 2

extern u8 play_sound(u16 sound_ID);
extern u8 play_sound_in_position(u16 sound_ID, Vec3f* position);
extern u8
play_sound_in_position_and_set_volume(u16 sound_ID, Vec3f* position, f32 volume_multiplier);
extern u8 func_800139D4(u16 sound_ID, f32, f32 volume);
extern u8 isValidBGM(u16 bgm_ID);
extern u8 setBGM(u16 bgm_ID);
extern u8 resetCurrentBGMAndStopBGM();
extern u32 setPreviousBGMAndStopBGM();
extern u32 setNewBGM(u16 bgm_ID);
extern u8 isBGMNotNothing();
extern u32 isBGMPlaying(u16 bgm_ID);
extern u8 wasMusicPlaying();
extern u8 pauseBGM(s32 setAudioToStandby);
extern u8 decreaseBGMVolume(s32 decreaseAudioVolume);
extern u8 increaseBGMSpeed(s32 increaseBGMSpeed);
extern u16 getCurrentBGM();
extern u8 resetCurrentBGM();
extern u32 setPreviousBGM();
extern s32 audioControlFadeOutType_setType(u32 type);
extern u8 isSoundVolumeDecreased();
extern void decreaseSoundVolume(u8 decrease);
extern void prepareSoundForPlay_defaultSettings(u32 sound_ID);

// Sound IDs (officially referred to as "sound codes")
#define SD_INVALID 0x000

// Control sounds
// These are not supposed to play audio. Rather, they do different actions
// if their sound IDs are played.

// Assumption
#define SD_CTRL_RESET_AUDIO_TRACK_STATE 0x001
// Assumption
#define SD_CTRL_RESET_AUDIO_STATE 0x002
// This can be used to stop the music temporarily
#define SD_CTRL_SET_AUDIO_TO_STANDBY 0x003
// Resumes the audio previously set to standby
#define SD_CTRL_RESUME_AUDIO        0x004
#define SD_CTRL_ENABLE_STEREO_AUDIO 0x005
#define SD_CTRL_ENABLE_MONO_AUDIO   0x006
// All of these use different sound IDs, but call the same function
#define SD_CTRL_FADE_OUT_AUDIO_007 0x007
#define SD_CTRL_FADE_OUT_AUDIO_008 0x008
#define SD_CTRL_FADE_OUT_AUDIO_009 0x009
#define SD_CTRL_FADE_OUT_AUDIO_00A 0x00A
// Gradually increases audio speed up to a certain point
#define SD_CTRL_INCREASE_AUDIO_SPEED 0x00B
// The audio speed will go back to normal
#define SD_CTRL_SET_REGULAR_AUDIO_SPEED 0x00C
// Gradually decreases audio volume up to a certain point. Used when going into the Pause Menu.
#define SD_CTRL_DECREASE_AUDIO_VOLUME 0x00D
// Gradually increases audio volume up to a certain point. Used when exiting the Pause Menu.
#define SD_CTRL_INCREASE_AUDIO_VOLUME 0x00E
// Does nothing. Its code is empty
#define SD_CTRL_00F 0x00F

#define SD_TRIGGER_BOTTOM_ELEVATOR_ACTIVATOR 0x119
#define SD_TOU_TURO_DOOR_CLOSE               0x11B
#define SD_LIBRARY_PIECE_SET                 0x1A0
#define SD_RENON_BRIEFCASE_SPIN_1            0x21A
#define SD_RENON_BRIEFCASE_SPIN_2            0x21B
#define SD_REINHARDT_HEALTH_RECOVERY         0x257
#define SD_CARRIE_HEALTH_RECOVERY            0x258
#define SD_ROSE_DOOR_CLOSE                   0x27B
#define SD_ROSE_DOOR_CLOSING                 0x29B
#define SD_CARRIE_BLESSING                   0x2E4
#define SD_REINHARDT_BLESSING                0x2E5
#define SD_2E9                               0x2E9
#define SD_CLOCK_TICKING                     0x2DC

#endif
