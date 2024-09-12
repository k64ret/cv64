#ifndef HUD_H
#define HUD_H

#include "objects/menu/mfds.h"
#include "gfx/model_info.h"

typedef enum HUD_parameters_flags {
    HUD_PARAMS_ENTERED_PAUSE_MENU        = 0x01,
    HUD_PARAMS_IN_PAUSE_MENU             = 0x02,
    HUD_PARAMS_SHOW_BOSS_BAR             = 0x04,
    HUD_PARAMS_UPDATE_HUD_GOLD_AND_JEWEL = 0x08,
    HUD_PARAMS_CLOSE_CLOCK               = 0x20, // Unused
    /**
     * Hides HUD during cutscenes or when transitioning between maps.
     */
    HUD_PARAMS_HIDE_HUD    = 0x40,
    HUD_PARAMS_DESTROY_HUD = 0x80
} HUD_parameters_flags;

typedef struct {
    u8 flags;
    u8 field_0x01;
    s16 damage_received;
    f32 health_bar_damage_length;
    u8 field_0x08[2];
    s16 life_lost_before_entering_loading_zone;
    f32 amount_of_life_lost;
    s16 hour_marker_angle;
    s16 minute_marker_angle;
    /**
     * NIGHT = 0x01
     * DAY   = 0x10
     */
    u8 clockDayNightGraphic_timeOfDay;
    u8 boss_actor_ID;
    u8 field_0x16[2];
    s16* boss_current_life;
    s16 boss_bar_health_max;
    s16 boss_bar_health_left;
    s16 boss_bar_damage;
    u8 field_0x22[2];
    f32 boss_bar_damage_length;
    mfds_state* gold_amount_textbox;
    mfds_state* item_amount_textbox;
    u8 field_0x30[4];
    u16* gold_amount_text;
    u16* item_amount_text;
    u8 field_0x3C[4];
} HUD_parameters;

// ID: 0x0129
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[4];
    cv64_model_inf_t* clock_and_health;
    cv64_model_inf_t* boss_bar;
    cv64_model_inf_t* status_and_subweapon;
    cv64_model_inf_t* gold_graphic;
    cv64_model_inf_t* day_graphic_above_clock;
    cv64_model_inf_t* clock_minute_marker;
    cv64_model_inf_t* clock_hour_marker;
    cv64_model_inf_t* health_bar_overlay;
    cv64_model_inf_t* health_bar_fill;
    cv64_model_inf_t* health_bar_fill_damage;
    cv64_model_inf_t* boss_bar_fill;
    cv64_model_inf_t* boss_bar_fill_damage;
    cv64_model_inf_t* status_text;
    cv64_model_inf_t* subweapon;
    cv64_model_inf_t* subweapon_icon;
    f32 day_and_night_switching_alpha;
    /**
     * This value changes when switching from night to day, or viceversa,
     * which is then added to the alpha value
     */
    f32 day_and_night_switching_transition_progress;
    /**
     * -1.0f: Night to Day
     *  1.0f: Day to Night
     *
     * This value is added up to `day_and_night_switching_transition_progress`
     * when transitioning through the time of day
     */
    f32 day_and_night_switching_factor;
    /**
     * This timer is set to 10 when in the pause menu.
     * When exiting, the timer runs down, and when it reaches -1,
     * the game will disable changing the position, scale, etc, of the HUD elements
     */
    u8 time_before_making_elements_static;
    /**
     * Boss bar is filling up when the bar first appears.
     */
    u8 boss_bar_is_filling_up;
    s16 health_depletion_rate_while_poisoned;
    HUD_parameters* params;
} HUD;

extern void HUD_entrypoint(HUD* self);
extern void HUD_initParams(HUD* self);
extern void HUD_initGraphics(HUD* self);
extern void HUD_update(HUD* self);
extern void HUD_destroy(HUD* self);

extern void HUDParams_fillPlayerHealth(
    s16 life, u32 player_flags_to_remove, s32 play_character_health_fulfilled_sound
);

extern s8 play_character_health_fulfilled_sound_after_recovering_health;

typedef void (*HUD_func_t)(HUD*);

#endif
