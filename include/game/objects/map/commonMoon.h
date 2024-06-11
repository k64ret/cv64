#ifndef COMMON_MOON_H
#define COMMON_MOON_H

#include "actor.h"

// ID 0x0173
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[4];
    cv64_model_inf_t* model;
    u8 field_0x28[12];
    /**
     * This variable has to be right-shifted with 8 to get the actual transparency value (a `u8`).
     */
    s32 transparency;
    u8 field_0x38[56];
    cv64_actor_settings_t* settings;
} commonMoon;

void commonMoon_entrypoint(commonMoon* self);
void commonMoon_init(commonMoon* self);
void commonMoon_main(commonMoon* self);
void commonMoon_main_idleDay(commonMoon* self);
void commonMoon_main_dayToNight(commonMoon* self);
void commonMoon_main_idleNight(commonMoon* self);
void commonMoon_main_nightToDay(commonMoon* self);

typedef enum commonMoon_func_id {
    COMMON_MOON_INIT,
    COMMON_MOON_LOOP
} commonMoon_func_id_t;

typedef enum commonMoon_main_func_id {
    COMMON_MOON_MAIN_IDLEDAY,
    COMMON_MOON_MAIN_DAYTONIGHT,
    COMMON_MOON_MAIN_IDLENIGHT,
    COMMON_MOON_MAIN_NIGHTTODAY
} commonMoon_main_func_id_t;

typedef void (*commonMoon_func_t)(commonMoon*);

extern const u32 COMMON_MOON_BEKKAN_1F_DL;
extern const u32 COMMON_MOON_BEKKAN_2F_DL;

#endif
