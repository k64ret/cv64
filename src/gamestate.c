#include "cv64.h"
#include "memory.h"
#include "object.h"
#include "object_ID.h"
#include "objects/engine/GameStateMgr.h"
#include "unknown_struct.h"
#include "unknown_struct_2.h"

void gamestate_create(s32 game_state) {
    // Set target framerate
    code_execution_max_delay =
        gameState_settings[game_state - 1].code_execution_max_delay;

    // This is inside a loop to make it so that
    // the game softlocks in case GameStateMgr
    // could not be created
    do {
        clearAllObjects();
        ptr_GameStateMgr = object_create(NULL, ENGINE_GAMESTATE_MGR);
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

void GameStateMgr_entrypoint(GameStateMgr* self) {
    if (self->current_game_state < 0) {
        if (self->exitingGameState == FALSE) {
            gamestate_create(-self->current_game_state);
        } else {
            self->exitingGameState--;
        }
        return;
    } else if (self->isCurrentGameStateActive == FALSE) {
        GameStateMgr_createGameStateModules(self);
        gameState_settings[self->current_game_state - 1].init_function(self);
        self->isCurrentGameStateActive++;
    }
    GameStateMgr_executeGameStateModules(self, D_80363AB8.execution_flags);
}

#pragma GLOBAL_ASM("../asm/nonmatchings/gamestate/gamestate_init.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/gamestate/setup_frame.s")

void end_frame(void) {
    fade_calc();
    if (D_80383AB8.should_end_master_display_list) {
        end_master_display_list();
    }
}
