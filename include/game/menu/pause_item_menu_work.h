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
    s8 field_0x01;
    s8 field_0x02;
    s8 field_0x03;
    u8 field_0x04;
    s8 field_0x05;
    u8 field_0x06;
    u8 field_0x07;
    f32 field_0x08;
    f32 field_0x0C;
    MfdsState* field_0x10[5];
    MfdsState* field_0x24;
    MfdsState* field_0x28;
    ItemCursol* item_cursol;
    u8 field_0x30[4];
    scroll_state* scroll;
    s32 selected_item_ID_in_item_list;
} PauseItemMenuWork;

#endif
