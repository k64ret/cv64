#ifndef GAMEPLAY_MENU_MGR_H
#define GAMEPLAY_MENU_MGR_H

#include "cv64.h"
#include "objects/menu/mfds.h"
#include "objects/menu/HUD.h"

typedef enum gameplayMenuMgrFlags {
    IN_PAUSE_MENU   = BIT(0),
    IN_FILE_SELECT  = BIT(1),
    IN_OPTIONS_MENU = BIT(2),
    IN_GAMEPLAY     = BIT(3),
    QUIT_GAME       = BIT(4),
    IN_GAME_OVER    = BIT(5),
    IN_RENON_SHOP   = BIT(6)
} gameplayMenuMgrFlags;

typedef enum gameplayMenuMgrMenuState {
    ENTERING_PAUSE_MENU  = BIT(0),
    ENTERING_FILE_SELECT = BIT(1), // Unused
    ENTERING_OPTION      = BIT(2),
    EXIT_MENU            = BIT(3),
    QUIT_GAME            = BIT(4),
    ENTERING_GAME_OVER   = BIT(5),
    ENTERING_RENON_SHOP  = BIT(6),
    INIT_NEW_GAME        = BIT(9)
} gameplayMenuMgrMenuState;

// ID: 0x0126
typedef struct {
    ObjectHeader header;
    u8 field_0x20[32];
    s32 bought_item_from_renon_shop; // Set to `TRUE` when buting an item in Renon's shop
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

extern void gameplayMenuMgr_entrypoint(gameplayMenuMgr* self);
extern void gameplayMenuMgr_initMainStructs(gameplayMenuMgr* self);
extern void gameplayMenuMgr_initHUDParams(gameplayMenuMgr* self);
extern void gameplayMenuMgr_outsideMenuLoop(gameplayMenuMgr* self);
extern void gameplayMenuMgr_initMenu(gameplayMenuMgr* self);
extern void gameplayMenuMgr_insideMenuLoop(gameplayMenuMgr* self);
extern void gameplayMenuMgr_exitMenu(gameplayMenuMgr* self);
extern void moveSelectionCursor(u32 button);
extern ObjMfds* getGameplayMenuMgrTextboxObject(u16 object_ID, ObjectHeader* start);
extern ObjMfds* getGameplayMenuMgrTextboxObjectFromList();
extern MfdsState* gameplayMenuMgr_closeCommonTextbox();

typedef void (*gameplayMenuMgrFuncs)(gameplayMenuMgr*);

extern gameplayMenuMgr* ptr_gameplayMenuMgr;

#endif
