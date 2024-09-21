/**
 * @file hud_params.c
 *
 * This file has additional code used by the `HUD` object, all of which
 * handles different operations with the different health bars.
 */

#include "cv64.h"
#include "objects/menu/HUD.h"
#include "system_work.h"

// maybe private
void HUDParams_initBossBar(u8 boss_actor_ID, s16* boss_current_life, s16 boss_bar_health) {
    HUD* obj_HUD = (HUD*) objectList_findFirstObjectByID(MENU_HUD);
    HUDParams* params;

    if (boss_current_life) {
    }
    if (obj_HUD->params) {
    }

    params = obj_HUD->params;
    BITS_SET(params->flags, HUD_PARAMS_SHOW_BOSS_BAR);
    obj_HUD->boss_bar_is_filling_up = TRUE;
    params->boss_actor_ID           = boss_actor_ID;
    params->boss_bar_damage         = 0;
    params->boss_current_life       = boss_current_life;
    params->boss_bar_health_max     = boss_bar_health;
    params->boss_bar_health_left    = boss_bar_health;
    params->boss_bar_damage_length  = 0.0f;
}

// maybe private
void HUDParams_removeBossCurrentLife(void) {
    HUD* obj_HUD = (HUD*) objectList_findFirstObjectByID(MENU_HUD);
    HUDParams* params;

    if (obj_HUD->params) {
    }

    params                    = obj_HUD->params;
    params->boss_current_life = NULL;
}

// public
void HUDParams_IncreaseDamage(s16 damage, u32 player_status) {
    HUD* obj_HUD = (HUD*) objectList_findFirstObjectByID(MENU_HUD);
    HUDParams* params;

    if (obj_HUD->params) {
    }

    params = obj_HUD->params;
    params->damage_received += damage;
    BITS_SET(sys.SaveStruct_gameplay.player_status, player_status);
}

// maybe private
void HUDParams_resetPlayerLifeAndStatus(void) {
    HUD* obj_HUD = (HUD*) objectList_findFirstObjectByID(MENU_HUD);
    HUDParams* params;

    if (obj_HUD->params) {
    }

    params                                = obj_HUD->params;
    sys.SaveStruct_gameplay.player_status = 0;
    sys.SaveStruct_gameplay.life          = 100;
    params->damage_received               = 0;
    params->health_bar_damage_length      = 0.0f;
}

// public
void HUDParams_FillPlayerHealth(
    s16 life, u32 player_status_to_remove, s32 play_character_health_fulfilled
) {
    HUD* obj_HUD = (HUD*) objectList_findFirstObjectByID(MENU_HUD);
    HUDParams* params;

    if (obj_HUD->params) {
    }

    if (play_character_health_fulfilled) {
        play_health_recovery_sound = TRUE;
    }

    params = obj_HUD->params;
    params->life_lost_before_entering_loading_zone += life;
    BITS_UNSET(sys.SaveStruct_gameplay.player_status, player_status_to_remove);
}
