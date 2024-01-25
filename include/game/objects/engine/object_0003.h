#ifndef OBJECT_0003_H
#define OBJECT_0003_H

#include "object.h"

// ID: 0x0003
// TODO: Fill this
typedef struct {
    u8 field_0x[OBJECT_SIZE];
} Obj_0003;

extern Obj_0003* ptr_Object_0003;
extern s32 func_8000EE18(Obj_0003* self, cv64_object_hdr_t* new_object);

#endif
