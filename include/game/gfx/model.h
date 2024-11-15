#ifndef MODEL_INFO_H
#define MODEL_INFO_H

#include "gfx/color.h"
#include "gfx/hierarchy.h"
#include "map_actor_model.h"
#include "math.h"
#include "nisitenma_ichigo.h"
#include <ultra64.h>

typedef struct Model {
    s16 type;
    u16 flags;
    struct Model* prev;
    struct Model* sibling;
    struct Model* next;
    struct Model* parent;
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
    NIFileID assets_file;
    Vec3f position;
    Angle angle;
    Angle field41_0x52;
    Vec3f size;
    MapActorModel* map_actor_model;
    Mat4f matrix;
} Model;

typedef struct actorPositionalData {
    Vec3f position;
    Angle angle;
} actorPositionalData;

extern void Model_setPosVec3s(Model* self, Vec3* position);
extern void Model_copyPositionalData(Model*, actorPositionalData*);
extern void Model_setMapActorModelNoCollision(Model*, u32*);
extern Model* Model_createAndSetChild(u32 type, void* parent);
extern Model* Model_createNextNode(u32 parent_type, void* parent);
extern Model* Model_buildHierarchy(u32 type, Model* self, Hierarchy* mdl_hierarchy);

#endif
