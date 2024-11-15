#ifndef GAMEPLAY_MENU_MGR_H
#define GAMEPLAY_MENU_MGR_H

#include "cv64.h"
#include "objects/menu/mfds.h"
#include "objects/menu/HUD.h"

typedef enum gameplayMenuMgr_flags_t {
    IN_PAUSE_MENU   = BIT(0),
    IN_FILE_SELECT  = BIT(1),
    IN_OPTIONS_MENU = BIT(2),
    IN_GAMEPLAY     = BIT(3),
    QUIT_GAME       = BIT(4),
    IN_GAME_OVER    = BIT(5),
    IN_RENON_SHOP   = BIT(6)
} gameplayMenuMgr_flags_t;

typedef enum pause_menu_state_t {
    ENTERING_PAUSE_MENU  = BIT(0),
    ENTERING_FILE_SELECT = BIT(1), // Unused
    ENTERING_OPTION      = BIT(2),
    EXIT_MENU            = BIT(3),
    QUIT_GAME            = BIT(4),
    ENTERING_GAME_OVER   = BIT(5),
    ENTERING_RENON_SHOP  = BIT(6),
    INIT_NEW_GAME        = BIT(9)
} pause_menu_state_t;

// ID: 0x0126
typedef struct {
    ObjectHeader header;
    u8 field_0x20[32];
    s32 field_0x40;
    u32 hide_common_textbox_window;
    u8 field_0x48[8];
    u32 update_assets_heap_block_max_size; // See 0x80136C9C
    void* assets_file_buffer_start_ptr;
    RGBA background_color;
    MfdsState* common_textbox;
    HUDParams* HUD_params;
    u32 current_opened_menu;
    void* assets_file_buffer_end_ptr;
    u32 flags;
    u32 menu_state;
} gameplayMenuMgr;

void gameplayMenuMgr_entrypoint(gameplayMenuMgr* self);

typedef void (*gameplayMenuMgr_func_t)(gameplayMenuMgr*);

extern gameplayMenuMgr* ptr_gameplayMenuMgr;

#endif
