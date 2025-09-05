#ifndef HONMARU_1F_ELEVATOR_SWITCH_EFFECT_SPAWNER_H
#define HONMARU_1F_ELEVATOR_SWITCH_EFFECT_SPAWNER_H

#include "actor.h"

// ID: 0x01CD
typedef struct ElevatorSwitchEffectSpawner {
    ObjectHeader header;
    u8 field_0x20[20];
    s32 time_before_spawning_effect;
    u8 field_0x38[56];
    ActorConfig* settings;
} ElevatorSwitchEffectSpawner;

void ElevatorSwitchEffectSpawner_Entrypoint(ElevatorSwitchEffectSpawner* self);

#endif
