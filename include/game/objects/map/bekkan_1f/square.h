#ifndef BEKKAN_1F_SQUARE_H
#define BEKKAN_1F_SQUARE_H

#include "actor.h"

// ID 0x01AF
typedef struct {
    ObjectHeader header;
    u8 field_0x20[4];
    Model* model;
    u8 field_0x28[72];
    ActorConfig* settings;
} Bekkan1FSquare;

void Bekkan1FSquare_Entrypoint(Bekkan1FSquare* self);
void Bekkan1FSquare_Init(Bekkan1FSquare* self);
void Bekkan1FSquare_PauseTransformations(Bekkan1FSquare* self);
void Bekkan1FSquare_Loop(Bekkan1FSquare* self);

typedef void (*Bekkan1FSquareFuncs)(Bekkan1FSquare*);

extern const u32 BEKKAN_1F_SQUARE_DL;

#endif
