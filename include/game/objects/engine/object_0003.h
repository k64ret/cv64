#ifndef OBJECT_0003_H
#define OBJECT_0003_H

#include "object.h"

// ID: 0x0003
// TODO: Fill this
typedef struct {
    u8 field_0x00[OBJECT_SIZE];
} object_0003;

extern object_0003* ptr_Object_0003;
extern s32 func_8000EE18(object_0003* self, ObjectHeader* new_object);

#endif
