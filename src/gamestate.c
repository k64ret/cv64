#include "c64.h"
#include "memory.h"
#include "module.h"
#include "module_ID.h"
#include "modules/engine/GameStateMgr.h"
#include <ultra64.h>

void gamestate_create(s32 game_state) {
    // Set target framerate
    code_execution_max_delay =
        gameState_settings[game_state - 1].code_execution_max_delay;

    // This is inside a loop to make it so that
    // the game softlocks in case GameStateMgr
    // could not be created
    do {
        clearAllModules();
        ptr_GameStateMgr = module_create(NULL, ENGINE_GAMESTATE_MGR);
    } while (ptr_GameStateMgr == NULL);

    // Set GameStateMgr params (flags, destroy function, game state ID and game
    // state info)
    ptr_GameStateMgr->flags |= TOP;
    ptr_GameStateMgr->destroy = GameStateMgr_destroy;
    ptr_GameStateMgr->current_game_state = game_state;
    memory_copy(&gameState_settings[game_state - 1].info,
                &ptr_GameStateMgr->current_game_state_info,
                sizeof(gameState_info));
}

void gamestate_change(s32 game_state) {
    ptr_GameStateMgr->current_game_state = -game_state;
    ptr_GameStateMgr->exitingGameState = TRUE;
}

void func_80000534(void) {}

#pragma GLOBAL_ASM("../asm/nonmatchings/gamestate/GameStateMgr_calc.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/gamestate/gamestate_init.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/gamestate/setup_frame.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/gamestate/end_frame.s")
