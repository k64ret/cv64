#ifndef OBJECT_20A4_H
#define OBJECT_20A4_H

#include "object.h"

// ID: 0x20A4
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[OBJECT_SIZE - 0x20];
} object_20A4;

void obj20A4_entrypoint(object_20A4* self);

#endif
