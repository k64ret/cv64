#ifndef OBJECT_20A5_H
#define OBJECT_20A5_H

#include "object.h"

// ID: 0x20A5
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[OBJECT_SIZE - 0x20];
} object_20A5;

void obj20A5_entrypoint(object_20A5* self);

#endif
