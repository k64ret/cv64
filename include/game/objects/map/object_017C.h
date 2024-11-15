#ifndef OBJECT_017C_H
#define OBJECT_017C_H

#include "actor.h"

// ID 0x017C
typedef struct {
    ObjectHeader header;
    u8 field_0x20[4];
    Model* model;
    u8 field_0x28[OBJECT_SIZE - 0x2C];
    ActorConfig* settings;
} object_017C;

void obj017C_Entrypoint(object_017C* self);
void obj017C_Init(object_017C* self);
void obj017C_Loop(object_017C* self);

typedef void (*obj017CFuncs)(object_017C*);

#endif
