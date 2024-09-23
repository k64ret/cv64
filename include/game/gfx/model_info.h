#ifndef MODEL_INFO_H
#define MODEL_INFO_H

#include "gfx/color.h"
#include "gfx/hierarchy.h"
#include "map_actor_model.h"
#include "math.h"
#include <ultra64.h>

typedef struct cv64_model_inf {
    s16 type;
    u16 flags;
    struct cv64_model_inf_t* prev;
    struct cv64_model_inf_t* sibling;
    struct cv64_model_inf_t* next;
    struct cv64_model_inf_t* parent;
    RGBA primitive_color;
    RGBA environment_color;
    RGBA blend_color;
    RGBA fog_color;
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
    Vec3f position;
    Angle angle;
    Angle field41_0x52;
    Vec3f size;
    cv64_map_actor_model_t* map_actor_model;
    Mat4f matrix;
} cv64_model_inf_t;

typedef struct actorPositionalData {
    Vec3f position;
    Angle angle;
} actorPositionalData;

extern void modelInfo_setPosVec3s(cv64_model_inf_t* self, Vec3* position);
extern void modelInfo_copyPositionalData(cv64_model_inf_t*, actorPositionalData*);
extern void modelInfo_setMapActorModel(cv64_model_inf_t*, u32*);
extern cv64_model_inf_t* modelInfo_createAndSetChild(u32 type, void* parent);
extern cv64_model_inf_t* modelInfo_createNextNode(u32 parent_type, void* parent);
extern cv64_model_inf_t*
modelInfo_buildHierarchy(u32 type, cv64_model_inf_t* self, Hierarchy* mdl_hierarchy);

#endif
