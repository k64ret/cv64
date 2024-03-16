#ifndef CAMERA_MGR_H
#define CAMERA_MGR_H

#include "object.h"
#include "gfx/camera.h"
#include "gfx/model_info.h"

// TODO: Add defines / enums for `player_camera_state` and `camera_mode`
typedef struct {
    u32 player_camera_state;
    u32 camera_mode;
    u32 previous_camera_mode;
    camera* camera_player;
    void* ptr_playerCameraController; // playerCameraController*
    cv64_model_inf_t* camera_mode_text;
    vec3f camera_position;
    vec3f camera_look_at_direction;
    f32 field_0x30;
    f32 field_0x34;
    f32 field_0x38;
    f32 field_0x3C;
    f32 field_0x40;
    f32 field_0x44;
    vec3f field_0x48;
    f32 field_0x54;
    f32 field_0x58;
    f32 field_0x5C;
    u8 field_0x60;
    u8 field_0x61[3];
    s32 field_0x64;
    vec3f camera_distance_to_player;
    vec3f first_person_camera_look_at_dir;
    s32 player_angle_yaw;
    vec3f field_0x84;
    s32 field_0x90;
    f32 field_0x94;
    s32 field_0x98; // Maybe a u8 / s32 union?
} cameraMgr_data;

// ID: 0x006A
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[4];
    camera* field_0x24;
    u8 field_0x28[12];
    cameraMgr_data* data;
    u8 field_0x38[OBJECT_SIZE - 0x38];
} cameraMgr;

extern void cameraMgr_entrypoint(cameraMgr* self);
extern void cameraMgr_init(cameraMgr* self);
extern void cameraMgr_loop(cameraMgr* self);
extern void cameraMgr_setReadingTextState(cameraMgr* self, s32 isReadingText);

#endif
