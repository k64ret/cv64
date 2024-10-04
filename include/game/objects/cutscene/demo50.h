#ifndef DEMO50_H
#define DEMO50_H

#include "cutscene.h"
#include "animation.h"
#include "objects/enemy/death.h"

typedef struct Demo50Data {
    Model* death_model;
    animationMgr* death_anim_mgr;
    Camera* cutscene_camera;
    Model* player_model;
    Camera* game_camera;
    CutsceneCurrentCameraMovement current_camera_movement;
    CutsceneCameraMovementState cam_mov_states[4];
    DeathData* death_data;
} Demo50Data;

// ID: 0x2059
typedef struct Demo50 {
    ObjectHeader header;
    u8 field_0x20[4];
    Camera* cutscene_camera;
    Death* death;
    u8 field_0x2C[8];
    Demo50Data* data;
    u8 field_0x38[48];
    u16 current_time;
    s16 max_time;
    u8 field_0x6C[4];
    u8 skip_cutscene;
    u8 set_player_anim_speed;
    u8 state;
    u8 field_0x73;
} Demo50;

void Demo50_Entrypoint(Demo50* self);
void Demo50_Init(Demo50* self);
void Demo50_CreateCutsceneCamera(Demo50* self);
void Demo50_GetPlayerModelAndSetBorders(Demo50* self);
extern void Demo50_Loop(Demo50* self);
void Demo50_Restart(Demo50* self);
extern void Demo50_PlayDeathAnimations(Demo50* self, CutsceneCoordinatesConfig* coords);

typedef void (*Demo50Func)(Demo50*);

typedef enum Demo50FuncId {
    DEMO50_INIT,
    DEMO50_CREATE_CUTSCENE_CAMERA,
    DEMO50_GET_PLAYER_MODEL_AND_SET_BORDERS,
    DEMO50_LOOP,
    DEMO50_RESTART
} Demo50FuncId;

#endif
