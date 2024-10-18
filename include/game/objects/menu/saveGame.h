#ifndef SAVEGAME_H
#define SAVEGAME_H

#include "objects/menu/mfds.h"

// ID: 0x2137
typedef struct {
    ObjectHeader header;
    u8 field_0x20[20];
    s32 field_0x34;
    s32 saveFile_errors;
    u8 field_0x3C[4];
    s16 save_crystal_number;
    u8 field_0x42[2];
    s32 field_0x44;
    void* saveGameResults; // saveGameResults*
    MfdsState* textbox;
    u8 field_0x50[36];
} saveGame;

#endif
