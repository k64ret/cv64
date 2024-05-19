#include "cv64.h"
#include "debug.h"

extern s32 processMeter_number_of_divisions;
extern f32 processBar_sizeDivisor;

extern OSTime processMeter_greenBar_beginTime;
extern OSTime processMeter_greenBar_endTime;
extern OSTime processMeter_blueBar_beginTime;
extern OSTime processMeter_blueBar_endTime;
extern f32 processMeter_greenBarSize;
extern f32 processMeter_blueBarSize;

void func_80019BC0_1A7C0(void) {}

void func_80019BC8_1A7C8(s32 arg0) {}

// Used in `func_80066400`. Maybe a stubbed debug print function
void func_80019BD0_1A7D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {}

// Maybe another stubbed debug print function, based on the number of arguments
void func_80019BE4_1A7E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {}

void func_80019BF8_1A7F8(void) {}

#pragma GLOBAL_ASM("../asm/nonmatchings/debug/processMeter_80019C00.s")

void processMeter_setSizeDivisor(f32 size_divisor) {
    processBar_sizeDivisor = size_divisor;
}

#pragma GLOBAL_ASM("../asm/nonmatchings/debug/processMeter_update.s")

#ifdef NON_MATCHING
    #pragma GLOBAL_ASM("../asm/nonmatchings/debug/processMeter_render.s")
#else
void processMeter_render(Gfx** dlist) {
    f32 number_of_divisions = SCREEN_HEIGHT / processMeter_number_of_divisions;
    f32 green_bar_size;
    f32 blue_bar_size;

    gDPPipeSync(dlist[0]++);
    gDPSetCycleType(dlist[0]++, G_CYC_FILL);
    gSPClearGeometryMode(dlist[0]++, G_ZBUFFER);
    gDPSetRenderMode(dlist[0]++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
    green_bar_size = processMeter_greenBarSize / (16.67 * processMeter_number_of_divisions);
    processMeter_renderBar(dlist, RGBA(3, 193, 3, 193), green_bar_size, 0);
    blue_bar_size = processMeter_blueBarSize / (16.67 * processMeter_number_of_divisions);
    processMeter_renderBar(dlist, RGBA(0, 31, 0, 31), blue_bar_size, 4);
    processMeter_renderDivisions(dlist, number_of_divisions);
    gDPPipeSync(dlist[0]++);
}
#endif

void processMeter_renderDivisions(Gfx** dlist, f32 division_width) {
    s32 i;

    gDPPipeSync(dlist[0]++);
    gDPSetFillColor(dlist[0]++, RGBA(0, 1, 0, 1));
    for (i = 0; processMeter_number_of_divisions >= i; i++) {
        gDPFillRectangle(
            dlist[0]++,
            (s32) division_width * i + 40,
            SCREEN_HEIGHT - 30,
            (s32) division_width * i + 40,
            SCREEN_HEIGHT - 20
        );
    }
}

#pragma GLOBAL_ASM("../asm/nonmatchings/debug/processMeter_renderBar.s")
