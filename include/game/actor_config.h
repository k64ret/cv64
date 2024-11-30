#ifndef ACTOR_CONFIG_H
#define ACTOR_CONFIG_H

#include "math.h"

#define DIFFICULTY_AND_SPAWN_SETTINGS_1(difficulty, spawn_settings_1)                              \
    (((difficulty << 4) & 0xF0) | (spawn_settings_1 & 0x0F))

typedef enum ActorConfigDifficulty {
    SPAWN_ON_ALL_DIFFICULTIES,
    SPAWN_ON_EASY,
    SPAWN_ON_NORMAL,
    SPAWN_ON_HARD
} ActorConfigDifficulty;

typedef enum ActorConfigSpawnSetting1 {
    SPAWN_SETTINGS_1 = 0x01
} ActorConfigSpawnSetting1;

typedef struct ActorConfig {
    Vec3 position;
    s16 actor_ID;
    u16 variable_1;
    u16 variable_2;
    u16 variable_3;
    union {
        struct {
            /**
             * Difficulty      = 4 upper bits
             * Spawn setting 1 = 4 lower bits
             */
            u8 difficulty__spawn_setting_1;
            u8 spawn_setting_2;
        };
        u16 difficulty__spawn_settings;
    };
} ActorConfig;

#endif
