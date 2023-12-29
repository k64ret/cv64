#ifndef OBJ_01B5_H
#define OBJ_01B5_H

#include "object.h"

// ID: 0x01B5
typedef struct cv64_meiroteien_obj01B5 {
    cv64_obj_hdr_t header;
    u8 field_0x20[OBJECT_SIZE - 0x20];
} cv64_meiroteien_obj01B5_t;

void cv64_meiroteien_obj01B5_entrypoint(
    cv64_meiroteien_obj01B5_t* self); // 0x8018EB10

#endif
