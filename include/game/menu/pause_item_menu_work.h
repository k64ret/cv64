#ifndef PAUSE_ITEM_MENU_WORK_H
#define PAUSE_ITEM_MENU_WORK_H

#include "objects/menu/scroll.h"

// Real name: `ITEM_CURSOL`
typedef struct ItemCursol {
    u16 selection_arrow_text[2];
} ItemCursol;

/**
 * @note While the code suggests this struct was named
 * `sound_menu_work`, it was likely an accident as another struct
 * with the same name already exists and is used to handle the
 * sound mode options menu instead.
 *
 * The name here is made up based on its usage in the code.
 */
typedef struct PauseItemMenuWork {
    u8 field_0x00;
    s8 current_page;
    /**
     * Within the current page
     * (i.e. first option is always 0, last option is always 4)
     */
    s8 highlighted_option;
    s8 delay_before_changing_option;
    u8 changing_pages;
    s8 field_0x05;
    /**
     * When switching pages, this is the number of pages to increment / decrement
     */
    u8 number_of_pages_to_advance;
    u8 field_0x07;
    Vec2f item_names_scroll_speed;
    MfdsState* item_names[6];
    MfdsState* item_cursol_textbox;
    ItemCursol* item_cursol;
    u8 field_0x30[4];
    scroll_state* scroll;
    s32 selected_item_in_item_list;
} PauseItemMenuWork;

#endif
