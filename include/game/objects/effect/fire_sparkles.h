#ifndef EFF_FIRE_SPARKLES_H
#define EFF_FIRE_SPARKLES_H

#include "effect.h"

// ID: 0x00E0
typedef struct FireSparkles {
    ObjectHeader header;
    u8 field_0x04[4];
    Model* model;
    u8 field_0x28[60];
    EffectInfo* info;
    EffectPositionalInfo* positional_info;
    EffectVisualInfo* visual_info;
    ActorConfig* settings;
} FireSparkles;

extern void FireSparkles_Entrypoint(FireSparkles* self);
extern void FireSparkles_Init(FireSparkles* self);
extern void FireSparkles_Loop(FireSparkles* self);
extern void FireSparkles_Destroy(FireSparkles* self);

typedef void (*FireSparklesFuncs)(FireSparkles*);

#endif
