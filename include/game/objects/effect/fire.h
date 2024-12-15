#ifndef EFF_FIRE_H
#define EFF_FIRE_H

#include "effect.h"

// ID: 0x00C1
typedef struct Fire {
    ObjectHeader header;
    u8 field_0x04[4];
    Model* model;
    u8 field_0x28[60];
    EffectInfo* info;
    EffectPositionalInfo* positional_info;
    EffectVisualInfo* visual_info;
    ActorConfig* settings;
} Fire;

extern void Fire_Entrypoint(Fire* self);
extern void Fire_Init(Fire* self);
extern void Fire_Loop(Fire* self);
extern void Fire_Destroy(Fire* self);

typedef void (*FireFuncs)(Fire*);

#endif
