#include "gamestate.h"
#include "cv64.h"
#include "fade.h"
#include "memory.h"
#include "object.h"
#include "object_ID.h"
#include "objects/engine/GameStateMgr.h"
#include "gfx/camera.h"
#include "gfx/figure.h"
#include "atari.h"
#include "system_work.h"

// clang-format off

gameState_settings_struct gameState_settings[NUM_GAMESTATES] = {
    // GAMESTATE_KONAMI_LOGO
    {
        0,
        gamestate_init,
        {
            GSS_SLOT(0x20, FUNC_8000C6D0),  GSS_SLOT(0x20, SETUP_FRAME),      GSS_SLOT(0x20, ENGINE_OBJ_002), GSS_SLOT(0x07, ENGINE_KONAMI_KCEK_LOGOS_CREATOR),
            GSS_SLOT(0x20, CAMERA_OBJ_06D), GSS_SLOT(0x20, CAMERA_CAMERAMGR), GSS_SLOT(0x20, FUNC_80012400),  GSS_SLOT(0x20, FUNC_8000C740),
            GSS_SLOT(0x20, FUNC_80005658),  GSS_SLOT(0x20, END_FRAME),        GSS_SLOT(0x20, ENGINE_OBJ_003), GSS_SLOT(0x20, ENGINE_DMAMGR),
            GSS_SLOT(0x00, 0x00000000),     GSS_SLOT(0x00, 0x00000000),       GSS_SLOT(0x00, 0x00000000),     GSS_SLOT(0x00, 0x00000000)
        }
    },
    // GAMESTATE_GAMEPLAY
    {
        1,
        gamestate_init,
        {
            GSS_SLOT(0x20, FUNC_8000C6D0),      GSS_SLOT(0x20, SETUP_FRAME),       GSS_SLOT(0x20, ENGINE_OBJ_002),   GSS_SLOT(0x40, UPDATE_GAMEPLAY_TIME),
            GSS_SLOT(0x07, ENGINE_GAMEPLAYMGR), GSS_SLOT(0x20, CAMERA_OBJ_06D),    GSS_SLOT(0x20, CAMERA_CAMERAMGR), GSS_SLOT(0x20, FUNC_80012400),
            GSS_SLOT(0x20, FUNC_8000C740),      GSS_SLOT(0x07, ATARI_WORK_UPDATE), GSS_SLOT(0x20, FUNC_80005658),    GSS_SLOT(0x20, END_FRAME),
            GSS_SLOT(0x20, ENGINE_OBJ_003),     GSS_SLOT(0x40, ENGINE_DMAMGR),     GSS_SLOT(0x00, 0x00000000),       GSS_SLOT(0x00, 0x00000000)
        }
    },
    // GAMESTATE_GAME_OVER
    {
        1,
        gamestate_init,
        {
            GSS_SLOT(0x20, FUNC_8000C6D0),  GSS_SLOT(0x20, SETUP_FRAME),      GSS_SLOT(0x20, ENGINE_OBJ_002), GSS_SLOT(0x07, ENGINE_GAME_OVER_CREATOR),
            GSS_SLOT(0x20, CAMERA_OBJ_06D), GSS_SLOT(0x20, CAMERA_CAMERAMGR), GSS_SLOT(0x20, FUNC_80012400),  GSS_SLOT(0x20, FUNC_8000C740),
            GSS_SLOT(0x20, FUNC_80005658),  GSS_SLOT(0x20, END_FRAME),        GSS_SLOT(0x20, ENGINE_OBJ_003), GSS_SLOT(0x40, ENGINE_DMAMGR),
            GSS_SLOT(0x00, 0x00000000),     GSS_SLOT(0x00, 0x00000000),       GSS_SLOT(0x00, 0x00000000),     GSS_SLOT(0x00, 0x00000000)
        }
    },
    // GAMESTATE_STAGE_SELECT
    {
        1,
        gamestate_init,
        {
            GSS_SLOT(0x20, FUNC_8000C6D0),  GSS_SLOT(0x20, SETUP_FRAME),      GSS_SLOT(0x20, ENGINE_OBJ_002), GSS_SLOT(0x07, MENU_STAGE_SELECT),
            GSS_SLOT(0x20, CAMERA_OBJ_06D), GSS_SLOT(0x20, CAMERA_CAMERAMGR), GSS_SLOT(0x20, FUNC_80012400),  GSS_SLOT(0x20, FUNC_8000C740),
            GSS_SLOT(0x20, FUNC_80005658),  GSS_SLOT(0x20, END_FRAME),        GSS_SLOT(0x40, ENGINE_OBJ_003), GSS_SLOT(0x40, ENGINE_DMAMGR),
            GSS_SLOT(0x00, 0x00000000),     GSS_SLOT(0x00, 0x00000000),       GSS_SLOT(0x00, 0x00000000),     GSS_SLOT(0x00, 0x00000000)
        }
    },
    // GAMESTATE_INTRO_CUTSCENE
    {
        1,
        gamestate_init,
        {
            GSS_SLOT(0x20, FUNC_8000C6D0),  GSS_SLOT(0x20, SETUP_FRAME),      GSS_SLOT(0x20, ENGINE_OBJ_002), GSS_SLOT(0x07, ENGINE_OPENING_CREATOR),
            GSS_SLOT(0x20, CAMERA_OBJ_06D), GSS_SLOT(0x20, CAMERA_CAMERAMGR), GSS_SLOT(0x20, FUNC_80012400),  GSS_SLOT(0x20, FUNC_8000C740),
            GSS_SLOT(0x20, FUNC_80005658),  GSS_SLOT(0x20, END_FRAME),        GSS_SLOT(0x20, ENGINE_OBJ_003), GSS_SLOT(0x40, ENGINE_DMAMGR),
            GSS_SLOT(0x00, 0x00000000),     GSS_SLOT(0x00, 0x00000000),       GSS_SLOT(0x00, 0x00000000),     GSS_SLOT(0x00, 0x00000000)
        }
    },
    // GAMESTATE_TITLE_SCREEN
    {
        1,
        gamestate_init,
        {
            GSS_SLOT(0x20, FUNC_8000C6D0),  GSS_SLOT(0x20, SETUP_FRAME),      GSS_SLOT(0x20, ENGINE_OBJ_002), GSS_SLOT(0x07, ENGINE_TITLE_SCREEN_CREATOR),
            GSS_SLOT(0x20, CAMERA_OBJ_06D), GSS_SLOT(0x20, CAMERA_CAMERAMGR), GSS_SLOT(0x20, FUNC_80012400),  GSS_SLOT(0x20, FUNC_8000C740),
            GSS_SLOT(0x20, FUNC_80005658),  GSS_SLOT(0x20, END_FRAME),        GSS_SLOT(0x20, ENGINE_OBJ_003), GSS_SLOT(0x40, ENGINE_DMAMGR),
            GSS_SLOT(0x00, 0x00000000),     GSS_SLOT(0x00, 0x00000000),       GSS_SLOT(0x00, 0x00000000),     GSS_SLOT(0x00, 0x00000000)
        }
    },
    // GAMESTATE_DATA_MENU
    {
        1,
        gamestate_init,
        {
            GSS_SLOT(0x20, FUNC_8000C6D0),  GSS_SLOT(0x20, SETUP_FRAME),      GSS_SLOT(0x20, ENGINE_OBJ_002), GSS_SLOT(0x07, ENGINE_FILE_SELECT_CREATOR),
            GSS_SLOT(0x20, CAMERA_OBJ_06D), GSS_SLOT(0x20, CAMERA_CAMERAMGR), GSS_SLOT(0x20, FUNC_80012400),  GSS_SLOT(0x20, FUNC_8000C740),
            GSS_SLOT(0x20, FUNC_80005658),  GSS_SLOT(0x20, END_FRAME),        GSS_SLOT(0x20, ENGINE_OBJ_003), GSS_SLOT(0x40, ENGINE_DMAMGR),
            GSS_SLOT(0x00, 0x00000000),     GSS_SLOT(0x00, 0x00000000),       GSS_SLOT(0x00, 0x00000000),     GSS_SLOT(0x00, 0x00000000)
        }
    },
    // GAMESTATE_OPTIONS_MENU
    {
        1,
        gamestate_init,
        {
            GSS_SLOT(0x20, FUNC_8000C6D0),  GSS_SLOT(0x20, SETUP_FRAME),      GSS_SLOT(0x20, ENGINE_OBJ_002), GSS_SLOT(0x07, ENGINE_OPTIONS_CREATOR),
            GSS_SLOT(0x20, CAMERA_OBJ_06D), GSS_SLOT(0x20, CAMERA_CAMERAMGR), GSS_SLOT(0x20, FUNC_80012400),  GSS_SLOT(0x20, FUNC_8000C740),
            GSS_SLOT(0x20, FUNC_80005658),  GSS_SLOT(0x20, END_FRAME),        GSS_SLOT(0x20, ENGINE_OBJ_003), GSS_SLOT(0x40, ENGINE_DMAMGR),
            GSS_SLOT(0x00, 0x00000000),     GSS_SLOT(0x00, 0x00000000),       GSS_SLOT(0x00, 0x00000000),     GSS_SLOT(0x00, 0x00000000)
        }
    },
    // GAMESTATE_TITLE_DEMO
    {
        1,
        gamestate_init,
        {
            GSS_SLOT(0x20, FUNC_8000C6D0),             GSS_SLOT(0x20, SETUP_FRAME),        GSS_SLOT(0x20, ENGINE_OBJ_002),    GSS_SLOT(0x40, UPDATE_GAMEPLAY_TIME),
            GSS_SLOT(0x07, ENGINE_TITLE_DEMO_CREATOR), GSS_SLOT(0x07, ENGINE_GAMEPLAYMGR), GSS_SLOT(0x20, CAMERA_OBJ_06D),    GSS_SLOT(0x20, CAMERA_CAMERAMGR),
            GSS_SLOT(0x20, FUNC_80012400),             GSS_SLOT(0x20, FUNC_8000C740),      GSS_SLOT(0x07, ATARI_WORK_UPDATE), GSS_SLOT(0x20, FUNC_80005658),
            GSS_SLOT(0x20, END_FRAME),                 GSS_SLOT(0x20, ENGINE_OBJ_003),     GSS_SLOT(0x40, ENGINE_DMAMGR),     GSS_SLOT(0x00, 0x00000000)
        }
    },
    // GAMESTATE_GAMENOTE_DELETE
    {
        1,
        gamestate_init,
        {
            GSS_SLOT(0x20, FUNC_8000C6D0),  GSS_SLOT(0x20, SETUP_FRAME),      GSS_SLOT(0x20, ENGINE_OBJ_002), GSS_SLOT(0x07, ENGINE_GAMENOTE_DELETE_MGR_CREATOR),
            GSS_SLOT(0x20, CAMERA_OBJ_06D), GSS_SLOT(0x20, CAMERA_CAMERAMGR), GSS_SLOT(0x20, FUNC_80012400),  GSS_SLOT(0x20, FUNC_8000C740),
            GSS_SLOT(0x20, FUNC_80005658),  GSS_SLOT(0x20, END_FRAME),        GSS_SLOT(0x20, ENGINE_OBJ_003), GSS_SLOT(0x20, ENGINE_DMAMGR),
            GSS_SLOT(0x00, 0x00000000),     GSS_SLOT(0x00, 0x00000000),       GSS_SLOT(0x00, 0x00000000),     GSS_SLOT(0x00, 0x00000000)
        }
    },
    // GAMESTATE_CREDITS
    {
        1,
        gamestate_init,
        {
            GSS_SLOT(0x20, FUNC_8000C6D0),  GSS_SLOT(0x20, SETUP_FRAME),      GSS_SLOT(0x20, ENGINE_OBJ_002), GSS_SLOT(0x07, ENGINE_CREDITSMGR_CREATOR),
            GSS_SLOT(0x20, CAMERA_OBJ_06D), GSS_SLOT(0x20, CAMERA_CAMERAMGR), GSS_SLOT(0x20, FUNC_80012400),  GSS_SLOT(0x20, FUNC_8000C740),
            GSS_SLOT(0x20, FUNC_80005658),  GSS_SLOT(0x20, END_FRAME),        GSS_SLOT(0x20, ENGINE_OBJ_003), GSS_SLOT(0x40, ENGINE_DMAMGR),
            GSS_SLOT(0x00, 0x00000000),     GSS_SLOT(0x00, 0x00000000),       GSS_SLOT(0x00, 0x00000000),     GSS_SLOT(0x00, 0x00000000)
        }
    },
};

// clang-format on

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
    BITS_SET(ptr_GameStateMgr->flags, OBJ_EXEC_FLAG_TOP);
    ptr_GameStateMgr->destroy = GameStateMgr_destroy;
    ptr_GameStateMgr->current_game_state = game_state;
    memory_copy(
        &gameState_settings[game_state - 1].slots,
        &ptr_GameStateMgr->current_game_state_slots,
        sizeof(ptr_GameStateMgr->current_game_state_slots)
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
        GameStateMgr_setupGameState(self);
        gameState_settings[self->current_game_state - 1].init_function(self);
        self->isCurrentGameStateActive++;
    }
    GameStateMgr_executeGameStateCappedFramerate(self, sys.execution_flags);
}

void gamestate_init(GameStateMgr* self) {
    // clang-format off
    sys.ptr_cameraMgr =
    sys.ptr_playerCameraController = NULL;

    common_camera_8009B430 =
    common_camera_8009B434 =
    common_camera_game_view =
    common_camera_effects =
    common_camera_8009B440 =
    common_camera_8009B444 =
    common_camera_8009B448 =
    common_camera_8009B44C =
    common_camera_HUD = NULL;
    // clang-format on
    func_8001248C_1308C();
    func_800010A0_1CA0();
    initHeaps();
    clearAllFigs();
    atari_work_table_init();
}

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
