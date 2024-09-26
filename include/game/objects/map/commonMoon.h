#ifndef COMMON_MOON_H
#define COMMON_MOON_H

#include "actor.h"

// ID 0x0173
typedef struct {
    ObjectHeader header;
    u8 field_0x20[4];
    Model* model;
    u8 field_0x28[12];
    /**
     * This variable has to be right-shifted with 8 to get the actual transparency value (a `u8`).
     */
    s32 transparency;
    u8 field_0x38[56];
    ActorConfig* settings;
} commonMoon;

void commonMoon_entrypoint(commonMoon* self);
void commonMoon_init(commonMoon* self);
void commonMoon_main(commonMoon* self);
void commonMoon_main_invisible(commonMoon* self);
void commonMoon_main_appear(commonMoon* self);
void commonMoon_main_visible(commonMoon* self);
void commonMoon_main_disappear(commonMoon* self);

typedef enum commonMoon_func_id {
    COMMON_MOON_INIT,
    COMMON_MOON_LOOP
} commonMoon_func_id_t;

typedef enum commonMoon_main_func_id {
    COMMON_MOON_MAIN_INVISIBLE,
    COMMON_MOON_MAIN_APPEAR,
    COMMON_MOON_MAIN_VISIBLE,
    COMMON_MOON_MAIN_DISAPPEAR
} commonMoon_main_func_id_t;

typedef void (*commonMoon_func_t)(commonMoon*);

extern const u32 COMMON_MOON_BEKKAN_1F_DL;
extern const u32 COMMON_MOON_BEKKAN_2F_DL;

#endif
