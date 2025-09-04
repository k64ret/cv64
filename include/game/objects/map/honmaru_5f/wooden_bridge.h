#ifndef HONMARU_5F_WOODEN_BRIDGE_H
#define HONMARU_5F_WOODEN_BRIDGE_H

#include "actor.h"

// ID: 0x01D9
typedef struct WoodenBridge {
    ObjectHeader header;
    u8 field_0x20[4];
    Model* model;
    u8 field_0x28[64];
    MapActorModel* map_actor_model;
    u8 field_0x6C[4];
    ActorConfig* settings;
} WoodenBridge;

void WoodenBridge_Entrypoint(WoodenBridge* self);
void WoodenBridge_Init(WoodenBridge* self);
void WoodenBridge_Loop(WoodenBridge* self);

typedef void (*WoodenBridgeFunc)(WoodenBridge*);

extern const u32 HONMARU_5F_WOODEN_BRIDGE_FULL;
extern const u32 HONMARU_5F_WOODEN_BRIDGE_BROKEN;

#endif
