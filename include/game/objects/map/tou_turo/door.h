#ifndef CV64_TOU_TURO_DOOR_H
#define CV64_TOU_TURO_DOOR_H

#include "actor.h"
#include "gfx/model.h"
#include "map_actor_model.h"
#include "object.h"

// Variable 1 = Door type
#define TOU_TURO_DOOR_TYPE     settings->variable_1
#define TOU_TURO_EXIT_DOOR     0
#define TOU_TURO_ENTRANCE_DOOR 1

extern const u32 TOUTURO_DOOR_EXIT_DL;
extern const u32 TOUTURO_DOOR_ENTRANCE_DL;

// ID: 0x1224
// Real name: `P27TOBIRA`
typedef struct cv64_ovl_touturo_door {
    ObjectHeader header;
    u8 padding1[4];
    Model* model;
    u8 padding2[12];
    u16 close_time;
    u8 padding3[50];
    MapActorModel* map_actor_model;
    u8 padding4[4];
    ActorConfig* settings;
} cv64_ovl_touturo_door_t;

// Common to both door types
typedef void (*cv64_ovl_touturo_door_func_t)(cv64_ovl_touturo_door_t*);
void cv64_ovl_touturo_door_entrypoint(cv64_ovl_touturo_door_t* self);
extern void cv64_ovl_touturo_door_init(cv64_ovl_touturo_door_t* self);
extern void cv64_ovl_touturo_door_loop(cv64_ovl_touturo_door_t* self);

// Type 0: Door that exists to Clock Tower
typedef void (*cv64_ovl_touturo_door_exit_func_t)(cv64_ovl_touturo_door_t*);
extern void cv64_ovl_touturo_door_exit_check_event_flags(cv64_ovl_touturo_door_t* self);

// Type 1: Door the player enters the map from
typedef void (*cv64_ovl_touturo_door_entrance_func_t)(cv64_ovl_touturo_door_t*);
extern void cv64_ovl_touturo_door_entrance_check_event_flags(cv64_ovl_touturo_door_t* self);
extern void cv64_ovl_touturo_door_entrance_close_door(cv64_ovl_touturo_door_t* self);

typedef enum cv64_ovl_touturo_door_entrance_func_id {
    TOU_TURO_DOOR_ENTRANCE_CHECK_EVENT_FLAGS,
    TOU_TURO_DOOR_ENTRANCE_CLOSE_DOOR,
    TOU_TURO_STAGE_PROP_LOOP
} cv64_ovl_touturo_door_entrance_func_id_t;

#endif // CV64_TOU_TURO_DOOR_H
