#ifndef EFFECT_MGR_H
#define EFFECT_MGR_H

#include "gfx/camera.h"
#include "object.h"

// ID: 0x00C0
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[4];
    camera* display_camera;
    u8 field_0x28[14];
    s16 number_of_effects_created;
    u8 field_0x38[OBJECT_SIZE - 0x38];
} effectMgr;

void effectMgr_entrypoint(effectMgr* self);
void effectMgr_init(effectMgr* self);
void effectMgr_loop(effectMgr* self);
void func_8005AF8C();
void func_8005AF94();

typedef void (*cv64_effectMgr_func_t)(effectMgr*);

extern effectMgr* ptr_effectMgr;

#endif
