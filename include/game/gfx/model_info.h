#ifndef MODEL_INFO_H
#define MODEL_INFO_H

#include "gfx/color.h"
#include "math.h"
#include <ultra64.h>

typedef struct cv64_model_inf {
    s16 type;
    u16 flags;
    struct cv64_model_inf_t* prev;
    struct cv64_model_inf_t* sibling;
    struct cv64_model_inf_t* next;
    struct cv64_model_inf_t* parent;
    cv64_rgba_t primitive_color;
    cv64_rgba_t environment_color;
    cv64_rgba_t blend_color;
    cv64_rgba_t fog_color;
    u16 texture;
    u16 palette;
    u8 field24_0x28;
    u8 field25_0x29;
    u8 field26_0x2a;
    u8 field27_0x2b;
    u8 field28_0x2c;
    u8 field29_0x2d;
    u8 field30_0x2e;
    u8 field31_0x2f;
    u32 material_dlist;
    u32 dlist;
    u32 field34_0x38;
    s32 assets_file_ID;
    vec3f position;
    angle_t angle;
    angle_t field41_0x52;
    vec3f size;
    void* field45_0x64; // map_actor_model*
    mf matrix;
} cv64_model_inf_t;

extern void modelInfo_setPosVec3s(cv64_model_inf_t* self, vec3s* position);
extern cv64_model_inf_t* modelInfo_createRootNode(u32 type, void* parent);
extern cv64_model_inf_t* modelInfo_createNextNode(u32 parent_type,
                                                  void* parent);
extern void modelInfo_showModelAndItsChildren(cv64_model_inf_t*, u16);
extern void modelInfo_hideModelAndItsChildren(cv64_model_inf_t*, u16);

#endif
