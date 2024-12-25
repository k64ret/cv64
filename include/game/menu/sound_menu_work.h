#ifndef SOUND_MENU_WORK_H
#define SOUND_MENU_WORK_H

#include "objects/menu/scroll.h"

// Real name: `sound_menu_work`
typedef struct SoundMenuWork {
    u8 field_0x00;
    u8 field_0x01;
    u8 field_0x02;
    u8 field_0x03;
    u8 field_0x04;
    u8 field_0x05;
    u8 field_0x06;
    u8 field_0x07[45];
    scroll_state* field_0x34;
    s32 selected_item_ID_in_item_list;
} SoundMenuWork;

#endif
