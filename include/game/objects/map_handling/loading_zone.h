#ifndef LOADING_ZONE_H
#define LOADING_ZONE_H

#include "object.h"
#include "gfx/color.h"
#include "actor_config.h"

typedef struct {
    Vec3 trigger_position;
    s16 map;
    s16 spawn;
    u16 fade_out_time;
    u16 fade_in_time;
    u8 field_0x0E[2];
    RGBA fade_in_color;
    s16 loading_zone_cutscene_settings_table_ID; // ID + 1
    u8 field_0x16[2];
} map_loading_zone_settings;

typedef struct {
    u16 event_flags_ID;
    u16 entrance_cutscene_ID;
    u32 event_flags;
    u32 cutscene_flags;
} loading_zone_cutscene_settings;

typedef struct {
    Vec3f position;
    s16 field_0x40;
    u8 field_0x42[2];
    void (*obj_destroy_function)(void*);
    s32 camera_mode;
    /**
     * Used after closing the Easy Mode Ending text to warp to the Konami Logo game state
     */
    s16 go_to_konami_logo;
    u8 field_0x4E[34];
    ActorConfig* settings;
} loadingZoneInner;

// ID: 0x016A
typedef struct {
    ObjectHeader header;
    u8 field_0x20[20];
    loadingZoneInner inner;
} loadingZone;

extern void (*loadingZone_functions[])(loadingZone* self);
extern void (*loadingZone_fillHealth_functions[])(loadingZone* self);
extern void (*loadingZone_createEasyModeEnding_functions[])(loadingZone* self);

extern loading_zone_cutscene_settings* loading_zone_cutscene_settings_table[6];
extern map_loading_zone_settings* map_loading_zone_settings_array[30];

extern void loadingZone_entrypoint(loadingZone* self);
extern void loadingZone_init(loadingZone* self);
extern void loadingZone_destroy(loadingZone* self);
extern void loadingZone_checkExceptions(loadingZone* self);
extern void loadingZone_playerIsInsideZone(loadingZone* self);
extern void loadingZone_setCutsceneSettings(loadingZone* self);
extern void loadingZone_freezeEntitiesAndSetCameraParams(loadingZone* self);
extern void loadingZone_fillPlayerHealth(loadingZone* self);
extern void loadingZone_exitMap(loadingZone* self);
extern void loadingZone_warpToMapFromLoadingZone(loadingZone* self);

typedef void (*loadingZone_func_t)(loadingZone*);

#endif
