#ifndef CAMERA_H
#define CAMERA_H

#include "gfx/figure.h"
#include "math.h"

typedef struct {
    s16 screen_width;
    s16 screen_height;
    s16 field2_0x4;
    s16 field3_0x6;
    s16 screen_offset_X;
    s16 screen_offset_Y;
    s16 field6_0xc;
    s16 field7_0xe;
    s16 field8_0x10;
    s16 field9_0x12;
    s16 field10_0x14;
    s16 field11_0x16;
    s16 field12_0x18;
    s16 field13_0x1a;
    s16 field14_0x1c;
    s16 field15_0x1e;
} screen_params;

typedef struct {
    f32 fovy;
    f32 aspect;
    f32 near;
    f32 far;
    f32 scale;
} projection_matrix_params;

// More info: http://n64devkit.square7.ch/n64man/gu/guFrustumF.htm
typedef struct {
    f32 l;
    f32 r;
    f32 b;
    f32 t;
    f32 n;
    f32 f;
    f32 scale;
} projection_matrix_params_ORTHO;

typedef union {
    projection_matrix_params* perspective;
    projection_matrix_params_ORTHO* ortho;
} union_projection_matrix;

typedef struct Camera {
    s16 type;
    u16 flags;
    struct Camera* prev;
    struct Camera* sibling;
    struct Camera* next;
    struct Camera* parent;
    u8 field1_0x14;
    u8 field2_0x15;
    u8 field3_0x16;
    u8 field4_0x17;
    u8 field5_0x18;
    u8 field6_0x19;
    u8 field7_0x1a;
    u8 field8_0x1b;
    u8 field9_0x1c;
    u8 field10_0x1d;
    u8 field11_0x1e;
    u8 field12_0x1f;
    u8 field13_0x20;
    u8 field14_0x21;
    u8 field15_0x22;
    u8 field16_0x23;
    u16 perspNorm;
    u8 field18_0x26;
    u8 field19_0x27;
    u8 field20_0x28;
    u8 field21_0x29;
    u8 field22_0x2a;
    u8 field23_0x2b;
    u8 field24_0x2c;
    u8 field25_0x2d;
    u8 field26_0x2e;
    u8 field27_0x2f;
    screen_params* screen_params;
    union_projection_matrix projection_matrix_params;
    u8 field30_0x38;
    u8 field31_0x39;
    u8 field32_0x3a;
    u8 field33_0x3b;
    Gfx* clip_ratio_dl;
    Vec3f position;
    Vec3 field36_0x4c;
    Angle angle;
    Vec3f look_at_direction;
    u8 field39_0x64;
    u8 field40_0x65;
    u8 field41_0x66;
    u8 field42_0x67;
    Mat4f matrix;
} Camera;

extern Camera* common_camera_8009B430;
extern Camera* common_camera_8009B434;  // Used by the skybox's moon
extern Camera* common_camera_game_view; // 3D view
extern Camera* common_camera_effects;   // Items, shadows, and some other effects
extern Camera* common_camera_8009B440;  // Normal / Action / Battle / Boss view text
extern Camera* common_camera_8009B444;  // Background elements, like in the pause menu
extern Camera* common_camera_8009B448;  // Used for the scrolls?
extern Camera* common_camera_8009B44C;  // Used for the pause menu scroll?
extern Camera* common_camera_HUD;       // Used for the gameplay HUD and text

extern Camera* Camera_Create(u16 type, s32 index);
extern void Camera_SetParams(Camera* self, s32 index);

#endif
