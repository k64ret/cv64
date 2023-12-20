#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <ultra64.h>

// clang-format off
typedef enum cv64_gamestate_id {
    KONAMI_LOGO     = 1,
    GAMEPLAY        = 2,
    GAME_OVER       = 3,
    STAGE_SELECT    = 4,
    INTRO_CUTSCENE  = 5,
    TITLE_SCREEN    = 6,
    DATA_MENU       = 7,
    OPTIONS_MENU    = 8,
    TITLE_DEMO      = 9,
    GAMENOTE_DELETE = 10,
    CREDITS         = 11
} cv64_gamestate_id_t;
// clang-format on

extern void gamestate_create(s32 gamestate_id);
extern void gamestate_change(s32 gamestate_id);
extern void gamestate_init();

#endif
