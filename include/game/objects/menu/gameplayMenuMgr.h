#ifndef GAMEPLAY_MENU_MGR_H
#define GAMEPLAY_MENU_MGR_H

#include "objects/menu/mfds.h"
#include "objects/menu/HUD.h"
#include "cv64.h"

typedef enum gameplayMenuMgr_flags_t {
    IN_PAUSE_MENU   = 1,
    IN_FILE_SELECT  = 2,
    IN_OPTIONS_MENU = 4,
    IN_GAMEPLAY     = 8,
    QUIT_GAME       = 0x10,
    IN_GAME_OVER    = 0x20,
    IN_RENON_SHOP   = 0x40
} gameplayMenuMgr_flags_t;

typedef enum pause_menu_state_t {
    ENTERING_PAUSE_MENU  = 1,
    ENTERING_FILE_SELECT = 2, // Unused
    ENTERING_OPTION      = 4,
    EXIT_MENU            = 8,
    QUIT_GAME            = 0x10,
    ENTERING_GAME_OVER   = 0x20,
    ENTERING_RENON_SHOP  = 0x40,
    INIT_NEW_GAME        = 0x200
} pause_menu_state_t;

// ID: 0x0126
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[32];
    s32 field_0x40;
    u32 hide_common_textbox_window;
    u8 field_0x48[8];
    u32 update_assets_heap_block_max_size; // See 0x80136C9C
    void* assets_file_buffer_start_ptr;
    cv64_rgba_t background_color;
    mfds_state* common_textbox;
    HUD_parameters* HUD_params;
    u32 current_opened_menu;
    void* assets_file_buffer_end_ptr;
    u32 flags;
    u32 menu_state;
} gameplayMenuMgr;

void gameplayMenuMgr_entrypoint(gameplayMenuMgr* self);

typedef void (*gameplayMenuMgr_func_t)(gameplayMenuMgr*);

extern gameplayMenuMgr* ptr_gameplayMenuMgr;

#endif
