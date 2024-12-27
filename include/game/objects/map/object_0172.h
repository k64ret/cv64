#ifndef OBJECT_0172_H
#define OBJECT_0172_H

#include "actor.h"

// ID 0x0172
typedef struct {
    ObjectHeader header;
    u8 field_0x20[4];
    Model* model;
    u8 field_0x28[OBJECT_SIZE - 0x2C];
    ActorConfig* settings;
} object_0172;

void obj0172_entrypoint(object_0172* self);
void obj0172_init(object_0172* self);
void obj0172_loop(object_0172* self);

typedef void (*obj0172Funcs)(object_0172*);

#endif
