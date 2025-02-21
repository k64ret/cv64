#ifndef MODEL_INFO_H
#define MODEL_INFO_H

#include "gfx/color.h"
#include "gfx/hierarchy.h"
#include "map_actor_model.h"
#include "math.h"
#include "nisitenma_ichigo.h"
#include "objects/menu/miniScroll.h"
#include "objects/menu/mfds.h"
#include <ultra64.h>

/**
 * This is used sometimes to store variables related to the
 * usage of a mini scroll
 */
typedef struct MiniScrollParameters {
    s32 state;
    s32 after_quit_state; // Where to go (for example, what menu) after the scroll is destroyed
    u32 scroll_init_delay_timer;
    struct miniScroll* scroll;
    struct MfdsState* textbox;
    u8 field_0x14[44];
} MiniScrollParameters;

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
    union {
        Mat4f matrix;
        MiniScrollParameters mini_scroll_params;
    };
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
