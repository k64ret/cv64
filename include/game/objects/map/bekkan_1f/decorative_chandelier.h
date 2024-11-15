#ifndef BEKKAN_1F_DECORATIVE_CHANDELIER_H
#define BEKKAN_1F_DECORATIVE_CHANDELIER_H

#include "actor.h"

// ID 0x01AE
typedef struct {
    ObjectHeader header;
    u8 field_0x20[4];
    Model* decoration;
    Model* pendant;
    u8 field_0x2C[68];
    ActorConfig* settings;
} DecorativeChandelier;

void DecorativeChandelier_Entrypoint(DecorativeChandelier* self);
void DecorativeChandelier_Init(DecorativeChandelier* self);
void DecorativeChandelier_PauseTransformations(DecorativeChandelier* self);

typedef void (*DecorativeChandelier_func_t)(DecorativeChandelier*);

extern const u32 BEKKAN_1F_SQUARE_DL;
extern const u32 BEKKAN_1F_SQUARE_DL;

#endif
