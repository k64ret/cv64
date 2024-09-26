#ifndef CUTSCENE_H
#define CUTSCENE_H

#include "actor.h"
#include "gfx/camera.h"
#include "cutscene_ID.h"

#define NUM_CUTSCENES 61

#define CUTSCENE_FLAG_PLAYING                    0x01
#define CUTSCENE_FLAG_FILM_REEL_EFFECT           0x04
#define CUTSCENE_FLAG_DISPLAY_WIDESCREEN_BORDERS 0x08 // Assumption
#define CUTSCENE_FLAG_10                         0x10
#define CUTSCENE_FLAG_20                         0x20

/**
 * The argument of function `cutscene_setCameraClippingAndScissoring`
 */
enum DLScissoringSetting {
    DL_SCISSORING_FULLSCREEN = 0,
    DL_SCISSORING_BORDERS    = 1
};

typedef struct CutsceneCoordinatesConfig {
    u8 field_0x00; // See the switches at 0x8012a130 and 0x8012a2b8
    u8 field_0x01;
    s8 player_anims_array_index; // Index at arrays 0x8016c884 and 0x8016c75c
    u8 field_0x03;
    Vec3 start_coords;
    Vec3 end_coords;
    s16 angle;
    s16 start_time; // Time in frames during the cutscene run time where this camera settings are going to be used
    s16 end_time; // Time in frames during the cutscene run time where this camera settings stop being used
} CutsceneCoordinatesConfig;

typedef struct CutsceneCurrentCameraMovement {
    Vec3f* cam_position;
    Angle* cam_angle;
    Vec3f cam_look_at_dir_offset;
} CutsceneCurrentCameraMovement;

typedef struct CutsceneCameraMovementState {
    Vec3f start_end_distance;
    f32 time_left;
    Vec3f speed;
} CutsceneCameraMovementState;

// Generic cutscene struct
typedef struct {
    ObjectHeader header;
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
extern Actor* cutscene_setActorStateIfMatchingVariable1(s16 actor_ID, u16 variable_1, u32 state);
extern void
Cutscene_UpdateCameraLookAtDir(Camera* camera, CutsceneCurrentCameraMovement* camera_movement);
extern void
func_801299A4(u32, Model*, CutsceneCoordinatesConfig*, CutsceneCameraMovementState*, u8);
extern void func_80128D20(u32, Camera*, Camera*, CutsceneCoordinatesConfig*, void*, u8);
extern void
func_8012A130(void*, Model*, CutsceneCoordinatesConfig*, CutsceneCameraMovementState*, u8, u32);
extern void Cutscene_SetCameraPosToEndCoords(CutsceneCoordinatesConfig*, Camera*);
extern void Cutscene_SetEndCoordsToActor(CutsceneCoordinatesConfig*, Model*);

#endif
