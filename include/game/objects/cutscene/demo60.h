#ifndef DEMO60_H
#define DEMO60_H

#include "cutscene.h"

enum Demo60State {
    DEMO60_RUNNING,
    DEMO60_FADE_OUT,
    DEMO60_FADE_IN,
    DEMO60_WAIT_UNTIL_FADE_IN_IS_OVER,
    DEMO60_RESET_BORDERS,
    DEMO60_SET_MAP_CAMERA_PARAMETERS
};

typedef struct Demo60Data {
    Camera* cutscene_camera;
    Model* player_model;
    Camera* game_camera;
    CutsceneCurrentCameraMovement current_camera_movement;
    CutsceneCameraMovementState cam_mov_state_turn_and_move_to_player;
    CutsceneCameraMovementState cam_mov_state_init;
    CutsceneCameraMovementState cam_mov_state_blessing;
} Demo60Data;

// ID: 0x205D
typedef struct Demo60 {
    ObjectHeader header;
    u8 field_0x20[4];
    Camera* cutscene_camera;
    u8 field_0x28[16];
    Demo60Data* data;
    u8 field_0x3C[44];
    u16 current_time;
    s16 max_time;
    u8 field_0x6C[4];
    u8 skip_cutscene;
    u8 set_player_anim_speed;
    u8 state;
    u8 field_0x73;
} Demo60;

void Demo60_Entrypoint(Demo60* self);
void Demo60_Init(Demo60* self);
void Demo60_CreateCutsceneCamera(Demo60* self);
void Demo60_GetPlayerModelAndSetBorders(Demo60* self);
void Demo60_Loop(Demo60* self);
void Demo60_Destroy(Demo60* self);
void Demo60_PlayPlayerBlessingAnim(Demo60* self, CutsceneCoordinatesConfig* coords);

typedef void (*Demo60Func)(Demo60*);

#endif
