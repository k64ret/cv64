#ifndef OBJECT_01B5_H
#define OBJECT_01B5_H

#include "object.h"

// ID: 0x01B5
typedef struct {
    ObjectHeader header;
    u8 field_0x20[OBJECT_SIZE - 0x20];
} object_01B5;

void obj01B5_entrypoint(object_01B5* self);

#endif
