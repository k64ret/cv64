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
    IN_QUIT_GAME    = BIT(4),
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
    MENU_STATE_100       = BIT(8), // Unused
    INIT_NEW_GAME        = BIT(9)
} gameplayMenuMgrMenuState;

// ID: 0x0126
// Real name: `etc_ctrl`
typedef struct gameplayMenuMgr {
    ObjectHeader header;
    u8 field_0x20[32];
    s32 bought_item_from_renon_shop; // Set to `TRUE` when buying an item in Renon's shop
    u32 hide_common_textbox_window;
    u8 field_0x48[8];
    u32 update_assets_heap_block_max_size;
    void* assets_file_buffer_start_ptr;
    RGBA background_color;
    MfdsState* common_textbox;
    /**
     * `obj_hud` is only written to instead of `HUD_params`
     * if the `HUD` object is not created during the initialization of `gameplayMenuMgr`.
     *
     * See `gameplayMenuMgr_initMainStructs`
     */
    union {
        HUDParams* HUD_params;
        HUD* obj_hud;
    };
    u32 current_opened_menu;
    void* assets_file_buffer_end_ptr;
    u32 flags;
    u32 menu_state;
} gameplayMenuMgr;

void gameplayMenuMgr_entrypoint(gameplayMenuMgr* self);
void gameplayMenuMgr_initMainStructs(gameplayMenuMgr* self);
void gameplayMenuMgr_initHUDParams(gameplayMenuMgr* self);
void gameplayMenuMgr_outsideMenuLoop(gameplayMenuMgr* self);
void gameplayMenuMgr_initMenu(gameplayMenuMgr* self);
void gameplayMenuMgr_insideMenuLoop(gameplayMenuMgr* self);
void gameplayMenuMgr_exitMenu(gameplayMenuMgr* self);
u32 moveSelectionCursor(u32 button);

MfdsState* gameplayCommonTextbox_getIfClosed();
MfdsState* gameplayCommonTextbox_close();
MfdsState* gameplayCommonTextbox_prepare(
    u16* text_ptr, u32 flags, u8 line, u16 width, u8 palette, s16 X_pos, s16 Y_pos, u8 display_time
);
MfdsState* gameplayCommonTextbox_addItemAndPrepareName(s32);
MfdsState* gameplayCommonTextbox_getMapMessage(u16, u8);
MfdsState* gameplayCommonTextbox_getMessageFromPool(u16*, u8, u8);
u32 gameplayCommonTextbox_lensAreOpened();
u32 gameplayCommonTextbox_lensAreClosed();
ObjMfds* gameplayCommonTextbox_getObject(s32, Object*);
ObjMfds* gameplayCommonTextbox_getObjectFromList();

typedef enum gameplayMenuMgrFuncId {
    GAMEPLAYMENUMGR_INIT_MAIN_STRUCTS,
    GAMEPLAYMENUMGR_INIT_HUD_PARAMS,
    GAMEPLAYMENUMGR_OUTSIDE_MENU_LOOP,
    GAMEPLAYMENUMGR_INIT_MENU,
    GAMEPLAYMENUMGR_INSIDE_MENU_LOOP,
    GAMEPLAYMENUMGR_EXIT_MENU,
    GAMEPLAYMENUMGR_DO_NOTHING
} gameplayMenuMgrFuncId;

typedef void (*gameplayMenuMgrFuncs)(gameplayMenuMgr*);

extern gameplayMenuMgr* ptr_gameplayMenuMgr;

#endif
