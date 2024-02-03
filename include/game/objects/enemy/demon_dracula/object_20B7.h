#ifndef OBJECT_20B7_H
#define OBJECT_20B7_H

#include "object.h"

// ID: 0x20B7
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[OBJECT_SIZE - 0x20];
} object_20B7;

void obj20B7_entrypoint(object_20B7* self);

#endif
