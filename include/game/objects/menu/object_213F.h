#ifndef OBJECT_213F_H
#define OBJECT_213F_H

#include "object.h"

// ID: 0x213F
typedef struct {
    ObjectHeader header;
    u8 field_0x20[OBJECT_SIZE - OBJECT_HEADER_SIZE];
} object_213F;

void obj213F_entrypoint(object_213F* self);               // 0x0F000000
void obj213F_isDraculaCutsceneWatched(object_213F* self); // 0x0F000070
void obj213F_isPlayerDroppingDown(object_213F* self);     // 0x0F0000DC
void obj213F_playSound(object_213F* self);                // 0x0F000130
void obj213F_destroy(object_213F* self);                  // 0x0F000174

typedef void (*cv64_ovl_obj213F_func_t)(object_213F*);

#endif
