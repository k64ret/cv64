#ifndef GAMESTATEMGR_H
#define GAMESTATEMGR_H

#include "gamestate.h"

// ID: 0x0001
typedef struct {
    s16 ID;
    u16 flags;
    u8 field2_0x4;
    u8 field3_0x5;
    u16 exitingGameState;
    u8 field5_0x8;
    u8 isCurrentGameStateActive;
    u8 field7_0xa;
    u8 field8_0xb;
    u8 field9_0xc;
    u8 field10_0xd;
    u8 field11_0xe;
    u8 field12_0xf;
    void* (*destroy)(struct GameStateMgr*);
    u8 field14_0x14;
    u8 field15_0x15;
    u8 field16_0x16;
    u8 field17_0x17;
    u8 field18_0x18;
    u8 field19_0x19;
    u8 field20_0x1a;
    u8 field21_0x1b;
    void* next;
    u8 field23_0x20;
    u8 field24_0x21;
    u8 field25_0x22;
    u8 field26_0x23;
    s32 current_game_state;
    u8 field28_0x28;
    u8 field29_0x29;
    u8 field30_0x2a;
    u8 field31_0x2b;
    u8 field32_0x2c;
    u8 field33_0x2d;
    u8 field34_0x2e;
    u8 field35_0x2f;
    u8 field36_0x30;
    u8 field37_0x31;
    u8 field38_0x32;
    u8 field39_0x33;
    gameState_info current_game_state_info;
} GameStateMgr;

void GameStateMgr_execute(GameStateMgr* self);
void GameStateMgr_destroy(GameStateMgr* self);
extern void GameStateMgr_createGameStateModules(GameStateMgr* self);
extern void GameStateMgr_executeGameStateModules(GameStateMgr* self,
                                                 u32 execution_flags);
extern GameStateMgr* ptr_GameStateMgr;

#endif
