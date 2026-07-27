#ifndef GAMEPLAY_MENU_MGR_H
#define GAMEPLAY_MENU_MGR_H

#include "cv64.h"
#include "objects/menu/mfds.h"
#include "objects/menu/HUD.h"

typedef enum GameplayMenuManagerFlag {
    IN_PAUSE_MENU   = BIT(0),
    IN_FILE_SELECT  = BIT(1),
    IN_OPTIONS_MENU = BIT(2),
    IN_GAMEPLAY     = BIT(3),
    IN_QUIT_GAME    = BIT(4),
    IN_GAME_OVER    = BIT(5),
    IN_RENON_SHOP   = BIT(6)
} GameplayMenuManagerFlag;

typedef enum GameplayMenuManagerMenuState {
    ENTERING_PAUSE_MENU  = BIT(0),
    ENTERING_FILE_SELECT = BIT(1), // Unused
    ENTERING_OPTION      = BIT(2),
    EXIT_MENU            = BIT(3),
    QUIT_GAME            = BIT(4),
    ENTERING_GAME_OVER   = BIT(5),
    ENTERING_RENON_SHOP  = BIT(6),
    MENU_STATE_100       = BIT(8), // Unused
    INIT_NEW_GAME        = BIT(9)
} GameplayMenuManagerMenuState;

// ID: 0x0126
// Real name: `etc_ctrl`
typedef struct GameplayMenuManager {
    ObjectHeader header;
    u8 field_0x20[32];
    /**
     * Set to `TRUE` when buying an item in Renon's shop
     */
    s32 bought_item_from_renon_shop;
    u32 hide_common_textbox_window;
    u8 field_0x48[8];
    u32 update_assets_heap_block_max_size;
    void* assets_file_buffer_start_ptr;
    RGBA background_color;
    MfdsState* common_textbox;
    /**
     * `obj_hud` is only written to instead of `HUD_params`
     * if the `HUD` object is not created during the initialization of `GameplayMenuManager`.
     *
     * See `GameplayMenuManager_initMainStructs`
     */
    union {
        HUDParams* HUD_params;
        HUD* obj_hud;
    };
    u32 current_opened_menu;
    void* assets_file_buffer_end_ptr;
    u32 flags;
    u32 menu_state;
} GameplayMenuManager;

void GameplayMenuManager_entrypoint(GameplayMenuManager* self);
void GameplayMenuManager_initMainStructs(GameplayMenuManager* self);
void GameplayMenuManager_initHUDParams(GameplayMenuManager* self);
void GameplayMenuManager_outsideMenuLoop(GameplayMenuManager* self);
void GameplayMenuManager_initMenu(GameplayMenuManager* self);
void GameplayMenuManager_insideMenuLoop(GameplayMenuManager* self);
void GameplayMenuManager_exitMenu(GameplayMenuManager* self);

MfdsState* GameplayCommonTextbox_getIfClosed(void);
MfdsState* GameplayCommonTextbox_close(void);
MfdsState* GameplayCommonTextbox_prepare(
    u16* text_ptr, u32 flags, u8 line, u16 width, u8 palette, s16 X_pos, s16 Y_pos, u8 display_time
);
MfdsState* GameplayCommonTextbox_addItemAndPrepareName(s32);
MfdsState* GameplayCommonTextbox_getMapMessage(u16, u8);
MfdsState* GameplayCommonTextbox_getMessageFromPool(u16*, u8, u8);
u32 GameplayCommonTextbox_lensAreOpened(void);
u32 GameplayCommonTextbox_lensAreClosed(void);
ObjMfds* GameplayCommonTextbox_getObject(s32, Object*);
ObjMfds* GameplayCommonTextbox_getObjectFromList(void);

typedef enum GameplayMenuManagerFuncID {
    GAMEPLAYMENUMGR_INIT_MAIN_STRUCTS,
    GAMEPLAYMENUMGR_INIT_HUD_PARAMS,
    GAMEPLAYMENUMGR_OUTSIDE_MENU_LOOP,
    GAMEPLAYMENUMGR_INIT_MENU,
    GAMEPLAYMENUMGR_INSIDE_MENU_LOOP,
    GAMEPLAYMENUMGR_EXIT_MENU,
    GAMEPLAYMENUMGR_DO_NOTHING
} GameplayMenuManagerFuncID;

typedef void (*GameplayMenuManagerFunc)(GameplayMenuManager*);

extern GameplayMenuManager* ptr_gameplayMenuMgr;

#endif
