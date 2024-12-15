#ifndef EFF_FIRE_H
#define EFF_FIRE_H

#include "effect.h"
#include "objects/effect/fire_sparkles.h"

// ID: 0x00C1
typedef struct Fire {
    ObjectHeader header;
    u8 field_0x04[4];
    Model* model;
    u8 field_0x28[4];
    FireSparkles* sparkles;
    u8 field_0x30[52];
    EffectInfo* info;
    EffectPositionalInfo* positional_info;
    EffectVisualInfo* visual_info;
    ActorConfig* settings;
} Fire;

extern void Fire_Entrypoint(Fire* self);
extern void Fire_Init(Fire* self);
extern void Fire_Loop(Fire* self);
extern void Fire_Destroy(Fire* self);

typedef enum FireFuncID {
    FIRE_INIT,
    FIRE_LOOP,
    FIRE_DESTROY
} FireFuncID;

extern const u32 FIRE_DLIST;

typedef void (*FireFuncs)(Fire*);

#endif
