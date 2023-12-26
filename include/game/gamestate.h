#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <ultra64.h>

// clang-format off
typedef enum cv64_gamestate_id {
    GAMESTATE_KONAMI_LOGO     = 1,
    GAMESTATE_GAMEPLAY        = 2,
    GAMESTATE_GAME_OVER       = 3,
    GAMESTATE_STAGE_SELECT    = 4,
    GAMESTATE_INTRO_CUTSCENE  = 5,
    GAMESTATE_TITLE_SCREEN    = 6,
    GAMESTATE_DATA_MENU       = 7,
    GAMESTATE_OPTIONS_MENU    = 8,
    GAMESTATE_TITLE_DEMO      = 9,
    GAMESTATE_GAMENOTE_DELETE = 10,
    GAMESTATE_CREDITS         = 11
} cv64_gamestate_id_t;
// clang-format on

void gamestate_create(s32 gamestate_id);
void gamestate_change(s32 gamestate_id);
extern void gamestate_init();
void end_frame(void);
extern void setup_background_color();
extern void setup_framebuffer();
extern void setup_rsp(Gfx**);
extern void setup_z_buffer();

#endif
