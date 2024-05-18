#ifndef DEBUG_H
#define DEBUG_H

// General debug functions

#include "cv64.h"

extern s32 processMeter_number_of_divisions;
extern f32 processBar_sizeDivisor;

extern OSTime processMeter_greenBar_beginTime;
extern OSTime processMeter_greenBar_endTime;
extern OSTime processMeter_blueBar_beginTime;
extern OSTime processMeter_blueBar_endTime;
extern f32 processMeter_greenBarSize;
extern f32 processMeter_blueBarSize;

void func_80019BC0_1A7C0();
void func_80019BC8_1A7C8(s32);
void func_80019BD0_1A7D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_80019BE4_1A7E4(s32, s32, s32, s32);
void func_80019BF8_1A7F8();
extern void processMeter_80019C00(OSMesgQueue*);
extern void processMeter_setSizeDivisor(f32 size_divisor);
extern void processMeter_update(s32 state);
extern void processMeter_render(Gfx* dlist);
extern void processMeter_renderDivisions(Gfx* dlist, f32 division_width);
extern void processMeter_renderBar(Gfx* dlist, u32 color, f32 bar_size, s32 row);

#endif
