#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "objects/menu/gameplayMenuMgr.h"
#include "objects/camera/modelLighting.h"
#include "menu/pause_item_menu_work.h"
#include "objects/player/player_flags.h"
#include "gfx/light.h"
#include "item.h"

/**
 * The item in question from `item_use_settings_array` is a healing item
 */
#define HEALING 0x10
/**
 * The item in question from `item_use_settings_array` is either a sun or a moon card
 */
#define TIME_CARD 1

/**
 * Turns raw player flag values into a mask that can be used with
 * PauseMenu's `item_effect` field to check the statuses
 */
#define CURABLE_FLAG_TO_PLAYER_FLAG(value) ((value) >> 0x19)
/**
 * Player status to remove when using a healing item from `item_use_settings_array`.
 * If the argument is set to 0, the game won't remove any status.
 *
 * @note Because of the way the checks are setup, only the VAMP, POISON and STO statuses
 *       can be removed from items in the pause menu.
 */
#define PLAYER_STATUS_TO_REMOVE(player_status)                                                     \
    (CURABLE_FLAG_TO_PLAYER_FLAG(player_status) | HEALING)
/**
 * Given the value from PauseMenu's `item_effect` field, this macro checks if any of the
 * curable statuses are set in said field
 */
#define MASK_CURABLE_STATUSES(value)                                                               \
    ((value) & CURABLE_FLAG_TO_PLAYER_FLAG(PLAYER_FLAG_POISON | PLAYER_FLAG_VAMP | PLAYER_FLAG_STO))
/**
 * Turns a mask into a raw player flag value
 */
#define MASKED_CURABLE_STATUS_TO_PLAYER_FLAG(value) ((value) << 0x19)
/**
 * Converts a curable status from PauseMenu's `item_effect` field into a raw player flag
 */
#define CURABLE_STATUS_TO_PLAYER_FLAG(value)                                                       \
    (MASKED_CURABLE_STATUS_TO_PLAYER_FLAG(MASK_CURABLE_STATUSES(value)))

typedef enum PauseMenuMainOptions {
    PAUSE_MENU_ITEM   = 1,
    PAUSE_MENU_OPTION = 2,
    PAUSE_MENU_QUIT   = 3,
    PAUSE_MENU_BACK   = 4
} PauseMenuMainOptions;

typedef enum PauseMenuQuitMiniScrollStates {
    PAUSE_QUIT_STATE_CREATE_SCROLL,
    PAUSE_QUIT_STATE_WAIT_FOR_SCROLL_INIT,
    PAUSE_QUIT_STATE_CREATE_TEXTBOX,
    PAUSE_QUIT_STATE_OPEN_SCROLL,
    PAUSE_QUIT_STATE_IDLE,
    PAUSE_QUIT_STATE_QUIT_GAME,
    PAUSE_QUIT_STATE_CLOSE_QUIT_SUBMENU,
    PAUSE_QUIT_STATE_DESTROY_SCROLL
} PauseMenuQuitMiniScrollStates;

typedef struct ItemUseSettings {
    u8 item;
    /**
     * See PauseMenu's `item_effect` field
     */
    u8 item_effect;
    /**
     * For example, for Healing Kit, this value is 100 (100 health recovered)
     *
     * If `item_effect` is set to `TIME_CARD`, then this variable
     * will act as the target hour the clock will go to when using the item.
     * For example, if it's 6, then the clock will go to 6:00 when using the item.
     */
    u8 target_value;
} ItemUseSettings;

/**
* Text buffer for the digital clock numbers
*
* Real name: `Digital_Clock`
*/
typedef struct DigitalClock {
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
    scroll_state* options_scroll;
    PauseItemMenuWork* item_menu;
    scroll_state* item_model_scroll;
    scroll_state* options_text_scroll;
    scroll_state* item_description_scroll;
    MfdsState* item_description;
    s8 outside_item_selected_menu;
    /**
     * Set to `TRUE` when entering the menu, and to `FALSE` when viewing an item
     * (right after its model is created). This field doesn't seem to be read.
     */
    u8 field_0x51;
    s8 option_selection_inside_selected_item;
    s8 selected_item_in_item_list;
    s8 selected_item;
    s8 delay_before_being_able_to_select_option;
    s8 item_use_settings_array_entry;
    u8 field_0x57;
    MfdsState* selection_arrow_textbox;
    MfdsState* character_name_textbox;
    MfdsState* digital_clock_textbox;
    DigitalClock* digital_clock_text;
    /**
     * The new player health value after using a health item
     *
     * @bug The fact that `target_health` is signed leads to the
     * Healing Item Cancel bug (https://www.youtube.com/watch?v=UgzXJejaf_8).
     *
     * When using a healing item, the new player health value is calculated
     * (see `pauseMenu_calcItemSelectedMenu`). After doing so, another check
     * in that same function runs to stop healing after the player's life is equal
     * or higher than `target_health`, which in turns enabled back the usage of the
     * B button to go back to the item menu.
     *
     * The bug happens when newly calculated `target_health` value becomes larger
     * than 127, at which point it will be considered negative, which will pass the checks
     * mentioned above.
     *
     * This doesn't affect the actual life value that is healed to the player,
     * as the game directly uses the `item_use_settings_target_value` field for that instead.
     */
    s8 target_health;
    /**
     * The new clock hour after using a time card
     */
    s8 target_hour;
    /**
     * Either the target health or target hour (depending on the item)
     * as obtained from `item_use_settings_array`
     */
    s8 item_use_settings_target_value;
    /**
     * This is a bitmask value that represents what are the effects the
     * selected item should do when used. The format in bits is as follows:
     *
     * XXXABBBC
     *
     * - A: If this is set (and not C), the selected item is a healing item, which will cure the status specified by BBB
     * - BBB: These bits represent a combination of three statuses to cure: POISON, VAMP and STO, respectively
     * - C: If this is set (and not A), the selected item is a time card
     * - X: Ignored
     */
    s8 item_effect;
    gameplayMenuMgr* gameplay_menu_mgr;
    u8 field_0x70[2];
    s8 selected_item_can_be_used;
    u8 field_0x73;
} PauseMenu;

void pauseMenu_entrypoint(PauseMenu*);
void pauseMenu_decreaseSoundVolume(PauseMenu*);
void pauseMenu_init(PauseMenu*);
void pauseMenu_createMainMenu(PauseMenu*);
void pauseMenu_calcMainMenu(PauseMenu*);
void pauseMenu_createItemList(PauseMenu*);
void pauseMenu_calcItemList(PauseMenu*);
void pauseMenu_calcItemSelectedMenu(PauseMenu*);
void pauseMenu_destroy(PauseMenu*);
void pauseMenu_calcQuitMenu(PauseMenu*);
void pauseMenu_updateDigitalClockDisplay(PauseMenu*);
PauseItemMenuWork*
pauseMenu_createPauseItemMenuWork(PauseMenu*, u8, modelLighting*, modelLighting*, s32);
void func_0F001BF0();
void pauseMenu_createItemDescription(PauseMenu*);
s32 getItemUseArrayEntry(s32);
void pauseMenu_updateClock(PauseMenu*);
s32 pauseMenu_checkIfItemCanBeUsed(PauseMenu*);

typedef void (*PauseMenuFuncs)(PauseMenu*);

typedef enum PauseMenuFuncId {
    PAUSE_MENU_DECREASE_SOUND_VOLUME,
    PAUSE_MENU_INIT,
    PAUSE_MENU_CREATE_MAIN_MENU,
    PAUSE_MENU_CALC_MAIN_MENU,
    PAUSE_MENU_CHECK_SCROLL_OBJ_EXISTS,
    PAUSE_MENU_CALC_ITEM_LIST,
    PAUSE_MENU_CALC_ITEM_SELECTED,
    PAUSE_MENU_DESTROY,
    PAUSE_MENU_CALC_QUIT_MENU,
    PAUSE_MENU_DO_NOTHING
} PauseMenuFuncId;

extern const u32 PAUSE_SCROLL_BG_MODEL_DL;
extern const u32 PAUSE_CHARACTER_PORTRAIT_MATERIAL_DL;
extern const u32 PAUSE_CHARACTER_PORTRAIT_REINHARDT_DL;
extern const u32 PAUSE_CHARACTER_PORTRAIT_CARRIE_DL;

#endif
