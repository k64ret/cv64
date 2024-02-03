#ifndef OBJECT_213F_H
#define OBJECT_213F_H

#include "object.h"

// ID: 0x213F
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[OBJECT_SIZE - OBJECT_HEADER_SIZE];
} object_213F;

void obj213F_entrypoint(object_213F* self);               // 0x0F000000
void obj213F_isDraculaCutsceneWatched(object_213F* self); // 0x0F000070
void obj213F_isPlayerDroppingDown(object_213F* self);     // 0x0F0000DC
void obj213F_playSound(object_213F* self);                // 0x0F000130
void obj213F_destroy(object_213F* self);                  // 0x0F000174

// 0x0F0001A0
void (*obj213F_functions[])(object_213F* self) = {
    obj213F_isDraculaCutsceneWatched, obj213F_isPlayerDroppingDown,
    obj213F_playSound, obj213F_destroy};

#endif
