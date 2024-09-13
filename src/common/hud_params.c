/**
 * @file hud_params.c
 *
 * This file has additional code used by the `HUD` object, all of which
 * handles different operations with the different health bars.
 */

#include "objects/menu/HUD.h"
#include "system_work.h"

void HUDParams_initBossBar(u8 boss_actor_ID, s16* boss_current_life, s16 boss_bar_health) {
    HUD* obj_HUD = (HUD*) objectList_findFirstObjectByID(MENU_HUD);
    HUD_parameters* params;

    if (boss_current_life) {
    }
    if (obj_HUD->params) {
    }

    params = obj_HUD->params;
    params->flags |= HUD_PARAMS_SHOW_BOSS_BAR;
    obj_HUD->boss_bar_is_filling_up = TRUE;
    params->boss_actor_ID           = boss_actor_ID;
    params->boss_bar_damage         = 0;
    params->boss_current_life       = boss_current_life;
    params->boss_bar_health_max     = boss_bar_health;
    params->boss_bar_health_left    = boss_bar_health;
    params->boss_bar_damage_length  = 0.0f;
}

void HUDParams_removeBossCurrentLife() {
    HUD* obj_HUD = (HUD*) objectList_findFirstObjectByID(MENU_HUD);
    HUD_parameters* params;

    if (obj_HUD->params) {
    }

    params                    = obj_HUD->params;
    params->boss_current_life = NULL;
}

void HUDParams_increaseDamage(s16 damage, u32 player_status) {
    HUD* obj_HUD = (HUD*) objectList_findFirstObjectByID(MENU_HUD);
    HUD_parameters* params;

    if (obj_HUD->params) {
    }

    params = obj_HUD->params;
    params->damage_received += damage;
    sys.SaveStruct_gameplay.player_status |= player_status;
}

void HUDParams_resetPlayerLifeAndStatus() {
    HUD* obj_HUD = (HUD*) objectList_findFirstObjectByID(MENU_HUD);
    HUD_parameters* params;

    if (obj_HUD->params) {
    }

    params                                = obj_HUD->params;
    sys.SaveStruct_gameplay.player_status = 0;
    sys.SaveStruct_gameplay.life          = 100;
    params->damage_received               = 0;
    params->health_bar_damage_length      = 0.0f;
}

void HUDParams_fillPlayerHealth(
    s16 life, u32 player_status_to_remove, s32 play_character_health_fulfilled
) {
    HUD* obj_HUD = (HUD*) objectList_findFirstObjectByID(MENU_HUD);
    HUD_parameters* params;

    if (obj_HUD->params) {
    }

    if (play_character_health_fulfilled) {
        play_character_health_fulfilled_sound_after_recovering_health = TRUE;
    }

    params = obj_HUD->params;
    params->life_lost_before_entering_loading_zone += life;
    sys.SaveStruct_gameplay.player_status &= ~player_status_to_remove;
}
