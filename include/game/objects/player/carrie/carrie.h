#ifndef CARRIE_H
#define CARRIE_H

#include "gfx/model.h"
#include "object.h"
#include "objects/player/player.h"

// ID: 0x0074 / 0x0075
typedef struct {
    ObjectHeader header;
    u8 field_0x20[4];
    Model* model;
    playerData* data;
    playerMovingAttack* movingAttack;
    u8 field_0x30[OBJECT_SIZE - 0x30];
} Carrie;

#endif
