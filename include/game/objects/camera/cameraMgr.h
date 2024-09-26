#ifndef CAMERA_MGR_H
#define CAMERA_MGR_H

#include "object.h"
#include "gfx/camera.h"
#include "gfx/model.h"

// TODO: Add defines / enums for `player_camera_state` and `camera_mode`
typedef struct {
    u32 player_camera_state;
    u32 camera_mode;
    u32 previous_camera_mode;
    Camera* camera_player;
    void* ptr_playerCameraController; // playerCameraController*
    Model* camera_mode_text;
    Vec3f camera_position;
    Vec3f camera_look_at_direction;
    f32 field_0x30;
    f32 field_0x34;
    f32 field_0x38;
    f32 field_0x3C;
    f32 field_0x40;
    f32 field_0x44;
    Vec3f field_0x48;
    f32 field_0x54;
    f32 field_0x58;
    f32 field_0x5C;
    u8 field_0x60;
    u8 field_0x61[3];
    s32 field_0x64;
    Vec3f camera_distance_to_player;
    Vec3f first_person_camera_look_at_dir;
    s32 player_angle_yaw;
    Vec3f field_0x84;
    s32 field_0x90;
    f32 field_0x94;
    s32 field_0x98; // Maybe a u8 / s32 union?
} cameraMgr_data;

// ID: 0x006A
typedef struct {
    ObjectHeader header;
    u8 field_0x20[4];
    Camera* field_0x24;
    u8 field_0x28[12];
    cameraMgr_data* data;
    u8 field_0x38[OBJECT_SIZE - 0x38];
} cameraMgr;

extern void cameraMgr_entrypoint(cameraMgr* self);
extern void cameraMgr_init(cameraMgr* self);
extern void cameraMgr_loop(cameraMgr* self);
extern void cameraMgr_setReadingTextState(cameraMgr* self, s32 isReadingText);
extern void cameraMgr_setLockCameraAtPointState(cameraMgr* self, s32 shouldLockCameraAtPoint);

#endif
