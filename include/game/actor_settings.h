#ifndef ACTOR_SETTINGS_H
#define ACTOR_SETTINGS_H

#include "math.h"

typedef struct cv64_actor_settings {
    vec3s position;
    s16 actor_ID;
    u16 variable_1;
    u16 variable_2;
    u16 variable_3;
    union {
        u8 difficulty__spawn_setting_1; // Difficulty      = 4 upper bits
                                        // Spawn setting 1 = 4 lower bits
        u8 spawn_setting_2;
        u16 difficulty__spawn_settings;
    };
} cv64_actor_settings_t;

#endif
