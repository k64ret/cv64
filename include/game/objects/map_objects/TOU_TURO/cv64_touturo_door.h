#ifndef CV64_TOU_TURO_DOOR_H
#define CV64_TOU_TURO_DOOR_H

#include "actor.h"
#include "gfx/model_info.h"
#include "map_actor_model.h"
#include "object.h"

// To-do: Un-hardcode these
#define CV64_TOUTURO_DOOR_EXIT_DLIST     0x0600A300
#define CV64_TOUTURO_DOOR_ENTRANCE_DLIST 0x0600AB00

// ID: 0x1224
typedef struct cv64_touturo_door {
    cv64_obj_hdr_t header;
    u8 padding1[4];
    cv64_model_inf_t* model;
    u8 padding2[12];
    u16 close_time;
    u8 padding3[50];
    cv64_map_actor_model_t* map_actor_model;
    u8 padding4[4];
    cv64_actor_settings_t* settings;
} cv64_touturo_door_t;

// Common to both door types
typedef void (*cv64_touturo_door_func_t)(cv64_touturo_door_t*);
void cv64_touturo_door_entrypoint(cv64_touturo_door_t* self);
extern void cv64_touturo_door_init(cv64_touturo_door_t* self);
extern void cv64_touturo_door_loop(cv64_touturo_door_t* self);

// Type 0: Door that exists to Clock Tower
typedef void (*cv64_touturo_door_exit_func_t)(cv64_touturo_door_t*);
extern void cv64_touturo_door_exit_check_event_flags(cv64_touturo_door_t* self);

// Type 1: Door the player enters the map from
typedef void (*cv64_touturo_door_entrance_func_t)(cv64_touturo_door_t*);
extern void
cv64_touturo_door_entrance_check_event_flags(cv64_touturo_door_t* self);
extern void cv64_touturo_door_entrance_close_door(cv64_touturo_door_t* self);

// .data
cv64_touturo_door_func_t cv64_touturo_door_funcs[] = {cv64_touturo_door_init,
                                                      cv64_touturo_door_loop};

u32 cv64_touturo_door_dlists[] = {CV64_TOUTURO_DOOR_EXIT_DLIST,
                                  CV64_TOUTURO_DOOR_ENTRANCE_DLIST};

cv64_touturo_door_exit_func_t cv64_touturo_door_exit_funcs[] = {
    cv64_touturo_door_exit_check_event_flags, func_801578FC};

cv64_touturo_door_entrance_func_t cv64_touturo_door_entrance_funcs[] = {
    cv64_touturo_door_entrance_check_event_flags,
    cv64_touturo_door_entrance_close_door, func_801578FC};

#endif // CV64_TOU_TURO_DOOR_H
