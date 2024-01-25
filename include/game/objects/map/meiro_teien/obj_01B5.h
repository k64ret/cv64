#ifndef OBJ_01B5_H
#define OBJ_01B5_H

#include "object.h"

// ID: 0x01B5
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[OBJECT_SIZE - 0x20];
} obj_01B5;

void obj01B5_entrypoint(obj_01B5* self); // 0x8018EB10

#endif
