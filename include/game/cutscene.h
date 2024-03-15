#ifndef CUTSCENE_H
#define CUTSCENE_H

#include "actor.h"

#define NUM_CUTSCENES 61

#define CUTSCENE_FLAG_PLAYING                    0x01
#define CUTSCENE_FLAG_FILM_REEL_EFFECT           0x04
#define CUTSCENE_FLAG_DISPLAY_WIDESCREEN_BORDERS 0x08 // Assumption
#define CUTSCENE_FLAG_10                         0x10
#define CUTSCENE_FLAG_20                         0x20

// Generic cutscene struct
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[40];
    f32 player_animation_speed;
    u8 field_0x4C[28];
    u16 current_time;
    s16 max_time;
    u8 field_0x6C[4];
    u8 skip_cutscene;
    u8 set_player_anim_speed;
    u8 state;
    u8 field_0x73;
} cutscene;

#define CUTSCENE_OVERLAY_FILM_REEL          1 // Unused
#define CUTSCENE_OVERLAY_WIDESCREEN_BORDERS 2
#define CUTSCENE_OVERLAY_FADE               8

typedef struct {
    u16 object_ID;
    u16 cutscene_ID;
    u16 overlay;
    /**
     * Unused? Set to many values in `cutscene_settings`
     */
    u8 field_0x06;
    u8 make_player_idle_after_cutscene;
    /**
     * Unused? Set to many values in `cutscene_settings`
     */
    u8 field_0x08;
    /**
     * Maybe padding
     */
    u8 field_0x09;
} cutscene_parameters;

extern cutscene_parameters cutscene_settings[NUM_CUTSCENES];

#define FULLSCREEN         0
#define WIDESCREEN_BORDERS 1

extern void cutscene_setCameraClippingAndScissoring(s16 top_edge_coords);
extern cv64_actor_t*
cutscene_setActorStateIfMatchingVariable1(s16 actor_ID, u16 variable_1, u32 state);

#endif
