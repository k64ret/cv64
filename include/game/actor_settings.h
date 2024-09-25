#ifndef ACTOR_SETTINGS_H
#define ACTOR_SETTINGS_H

#include "math.h"

#define DIFFICULTY_AND_SPAWN_SETTINGS_1(difficulty, spawn_settings_1)                              \
    (((difficulty << 4) & 0xF0) | (spawn_settings_1 & 0x0F))

typedef enum cv64_actor_settings_difficulty {
    SPAWN_ON_ALL_DIFFICULTIES,
    SPAWN_ON_EASY,
    SPAWN_ON_NORMAL,
    SPAWN_ON_HARD
} cv64_actor_settings_difficulty_t;

typedef enum cv64_actor_settings_spawn_settings_1 {
    SPAWN_SETTINGS_1 = 0x01
} cv64_actor_settings_spawn_settings_1_t;

typedef struct ActorConfig {
    Vec3 position;
    s16 actor_ID;
    u16 variable_1;
    u16 variable_2;
    u16 variable_3;
    union {
        struct {
            u8 difficulty__spawn_setting_1; // Difficulty      = 4 upper bits
                                            // Spawn setting 1 = 4 lower bits
            u8 spawn_setting_2;
        };
        u16 difficulty__spawn_settings;
    };
} ActorConfig;

#endif
