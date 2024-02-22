#include "gamestate.h"
#include "cv64.h"
#include "fade.h"
#include "memory.h"
#include "object.h"
#include "object_ID.h"
#include "objects/engine/GameStateMgr.h"
#include "system_work.h"

// .bss
GameStateMgr* ptr_GameStateMgr;

void gamestate_create(s32 game_state) {
    // Set target framerate
    sys.code_execution_max_delay =
        gameState_settings[game_state - 1].code_execution_max_delay;

    // This is inside a loop to make it so that
    // the game softlocks in case GameStateMgr
    // could not be created
    do {
        clearAllObjects();
        ptr_GameStateMgr = object_create(NULL, ENGINE_GAMESTATEMGR);
    } while (ptr_GameStateMgr == NULL);

    // Set GameStateMgr params (flags, destroy function, game state ID and game
    // state info)
    ptr_GameStateMgr->flags |= OBJ_EXEC_FLAG_TOP;
    ptr_GameStateMgr->destroy = GameStateMgr_destroy;
    ptr_GameStateMgr->current_game_state = game_state;
    memory_copy(
        &gameState_settings[game_state - 1].info,
        &ptr_GameStateMgr->current_game_state_info,
        sizeof(gameState_info)
    );
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
        GameStateMgr_createGameStateObjects(self);
        gameState_settings[self->current_game_state - 1].init_function(self);
        self->isCurrentGameStateActive++;
    }
    GameStateMgr_executeGameStateObjects(self, sys.execution_flags);
}

#pragma GLOBAL_ASM("../asm/nonmatchings/gamestate/gamestate_init.s")

void setup_frame() {
    gDisplayListHead = &sys.field2_0x8[sys.current_dlist_buffer].dlists;
    gSPSegment(gDisplayListHead++, 0x00, 0x00000000);
    setup_rsp(&gDisplayListHead);
    if (sys.should_setup_Z_buffer != FALSE) {
        setup_z_buffer();
    }
    setup_framebuffer();
    if (sys.should_setup_background_color != FALSE) {
        setup_background_color();
    }
}

void end_frame(void) {
    fade_calc();
    if (sys.should_end_master_display_list) {
        end_master_display_list();
    }
}
