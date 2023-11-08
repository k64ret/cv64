#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <ultra64.h>

enum gameState_ID {
    KONAMI_LOGO = 1,
    GAMEPLAY = 2,
    GAME_OVER = 3,
    STAGE_SELECT = 4,
    INTRO_CUTSCENE = 5,
    TITLE_SCREEN = 6,
    DATA_MENU = 7,
    OPTIONS_MENU = 8,
    TITLE_DEMO = 9,
    GAMENOTE_DELETE = 10,
    CREDITS = 11
};

extern void createGameState(s32 game_state);
extern void changeGameState(s32 game_state);
extern void gameState_init();

#endif
