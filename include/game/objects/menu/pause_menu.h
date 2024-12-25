#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "objects/menu/gameplayMenuMgr.h"
#include "objects/camera/modelLighting.h"
#include "menu/sound_menu_work.h"
#include "gfx/light.h"
#include "item.h"

typedef struct ItemUseSettings {
    u8 item;
    /**
     * This value is AND with 0xE, and then << 0x19 to obtain the actual player flag value
     * See `pauseMenu_checkIfItemCanBeUsed`
     */
    u8 player_flag_to_change;
    /**
     * For example, for Healing Kit, this value is 100 (100 health recovered)
     */
    u8 amount_to_fill;
} ItemUseSettings;

// Real name: `Digital_Clock`
typedef struct DigitalClock {
    /**
     * Text numbers of the digital clock
     * in the CV64 custom text format.
     */
    u16 clock_text[6];
} DigitalClock;

// ID: 0x2134
typedef struct PauseMenu {
    ObjectHeader header;
    u8 field_0x20[4];
    Model* scroll_background_model;
    Light* scrolls_borders_light;
    Light* scrolls_background_light;
    union {
        Model* character_portrait;
        // Real name: `item`
        Model* item_model;
    };
    MfdsState* options_textbox;
    scroll_state* main_menu_options_scroll;
    SoundMenuWork* sound_menu;
    scroll_state* item_model_scroll;
    scroll_state* options_text_scroll;
    scroll_state* description_text_scroll;
    MfdsState* item_description;
    u8 outside_item_selected_menu;
    /**
     * Similar to `outside_item_selected_menu`? Although this field doesn't seem to be read.
     * Set to 1 when entering the menu, and to 0 when viewing an item.
     */
    u8 field_0x51;
    s8 option_selection_inside_selected_item;
    s8 selected_item_ID_in_item_list;
    s8 selected_item_ID;
    s8 delay_before_being_able_to_select_option;
    s8 item_use_settings_array_entry;
    u8 field_0x57;
    MfdsState* selection_arrow_textbox;
    MfdsState* character_name_textbox;
    MfdsState* digital_clock_textbox;
    DigitalClock* digital_clock_text;
    s8 target_health; // After using a health item
    s8 target_hour;   // After using a Moon / Sun card
    s8 item_use_settings_amount_to_fill;
    s8 player_flag_to_change;
    gameplayMenuMgr* gameplay_menu_mgr;
    u8 field_0x70[2];
    u8 selected_item_can_be_used;
    u8 field_0x73;
} PauseMenu;

extern void pauseMenu_entrypoint(PauseMenu*);
extern void pauseMenu_init(PauseMenu*);
extern void pauseMenu_createMainMenu(PauseMenu*);
extern void pauseMenu_calcMainMenu(PauseMenu*);
extern void pauseMenu_checkScrollObjExists(PauseMenu*);
extern void pauseMenu_calcItemList(PauseMenu*);
extern void pauseMenu_calcItemSelectedMenu(PauseMenu*);
extern void pauseMenu_destroy(PauseMenu*);
extern void pauseMenu_calcQuitMenu(PauseMenu*);
extern void pauseMenu_updateDigitalClockDisplay(PauseMenu*);
extern SoundMenuWork*
pauseMenu_createSoundMenuWork(PauseMenu*, s32, modelLighting*, modelLighting*, s32);
extern void func_0F001BF0();
extern void pauseMenu_createItemDescription(PauseMenu*);
extern s32 getItemUseArrayEntry(s32);
extern void pauseMenu_updateClock(PauseMenu*);
extern s32 pauseMenu_checkIfItemCanBeUsed(PauseMenu*);

typedef void (*PauseMenuFuncs)(PauseMenu*);

#endif
