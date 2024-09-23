#ifndef CUTSCENE_TRIGGER_H
#define CUTSCENE_TRIGGER_H

#include "actor.h"
#include "objects/player/player_flags.h"

#define XYZ_AXIS 0
#define XZ_AXIS  1
#define X_AXIS   2
#define Y_AXIS   3
#define Z_AXIS   4

typedef enum cutscene_additional_settings_mode_e {
    //CUTSCENE_SETTINGS_MODE_DEFAULT = 0x00,    // Also mode 1
    //CUTSCENE_SETTINGS_MODE_REQUIRED_PLAYER_FLAGS = 0x02,  // Also mode 4
    /**
     * Also modes 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
     * 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31
     */
    //CUTSCENE_SETTINGS_MODE_DONT_TRIGGER_CUTSCENE = 0x03,
    CUTSCENE_SETTINGS_MODE_SPAWN_ENEMY        = 0x10,
    CUTSCENE_SETTINGS_MODE_SET_EVENT_FLAG     = 0x20,
    CUTSCENE_SETTINGS_MODE_REMOVE_EVENT_FLAG  = 0x40,
    CUTSCENE_SETTINGS_MODE_BAD_ENDING_TRIGGER = 0x80,
} cutscene_additional_settings_mode_e;

typedef struct {
    u8 map;
    u8 event_flag_ID;
    u8 field_0x02[2];
    u32 event_flags;
    /**
     * SaveStruct event flag that must be set in order for the cutscene to play
     */
    u32 required_event_flags;
    union {
        u16 cutscene_ID;
        s16 enemy_actor_ID;
    };
    u16 trigger_dimension_type;
    u16 mode;
    s16 start_hour;
    s16 end_hour;
    Vec3 trigger_lower_limit;
    Vec3 trigger_upper_limit;
    u8 field_0x22[2];
    u32 required_player_flags;
    /**
     * 0x01 for Reinhardt only
     * 0x02 for Carrie only
     * 0x00 for both
     */
    s16 character;
    u8 field_0x2A[2];
} cutscene_additional_settings;

// ID: 0x0029
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[36];
    u32 state;
    u8 field_0x48[8];
    s32 additional_settings_ID;
    u8 field_0x54[28];
    cv64_actor_settings_t* settings;
} cutsceneTrigger;

extern void cutsceneTrigger_entrypoint(cutsceneTrigger* self);
extern void cutsceneTrigger_checkCollision(cutsceneTrigger* self);
extern void cutsceneTrigger_checkModes(cutsceneTrigger* self);
extern void cutsceneTrigger_destroy(cutsceneTrigger* self);
extern void cutsceneTrigger_init(cutsceneTrigger* self);
extern void cutsceneTrigger_resetState(cutsceneTrigger* self);

extern cutscene_additional_settings cutscene_additional_settings_list[29];

typedef void (*cutsceneTrigger_func_t)(cutsceneTrigger*);

#endif
