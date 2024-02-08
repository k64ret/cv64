#ifndef OBJECT_20A3_H
#define OBJECT_20A3_H

#include "object.h"

// ID: 0x20A3
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[OBJECT_SIZE - 0x20];
} object_20A3;

void obj20A3_entrypoint(object_20A3* self);

#endif
