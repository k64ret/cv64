#include "debug.h"

s32 processMeter_number_of_divisions = 3;
f32 processBar_sizeDivisor           = 45720360.0f;

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

void processMeter_80019C00(OSMesgQueue* mq) {
    u32 start_count;
    u32 end_count;
    u32 total_count;
    f64 framerate;

    // Wait until the message queue has at least one message to process
    if (mq->msgCount <= mq->validCount) {
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    }

    // Wait for the next message in the queue
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    start_count = osGetCount();

    // Wait for another message in the queue to measure end time
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    end_count = osGetCount();

    // Get framerate and the total time elapsed
    framerate   = osTvType == OS_TV_PAL ? 50.0 : 60.0;
    total_count = end_count - start_count;

    // @bug This condition is never executed
    if (FALSE) {
        framerate = 60.0;
        total_count -= 1;
    }

    processMeter_setSizeDivisor(framerate * 1.0 * total_count);
}

void processMeter_setSizeDivisor(f32 size_divisor) {
    processBar_sizeDivisor = size_divisor;
}

#ifdef NON_MATCHING
    #pragma GLOBAL_ASM("../asm/nonmatchings/debug/processMeter_update.s")
#else
void processMeter_update(s32 state) {
    switch (state) {
        case START_GREEN_BAR:
            processMeter_greenBar_beginTime = osGetTime();
            break;
        case END_GREEN_BAR:
            processMeter_greenBar_endTime = osGetTime();
            processMeter_greenBarSize =
                processMeter_greenBar_endTime - processMeter_greenBar_beginTime;
            processMeter_greenBarSize =
                (1000.0 * processMeter_greenBarSize) / (u64) processBar_sizeDivisor;
            break;
        case START_BLUE_BAR:
            processMeter_blueBar_beginTime = osGetTime();
            break;
        case END_BLUE_BAR:
            processMeter_blueBar_endTime = osGetTime();
            processMeter_blueBarSize =
                processMeter_blueBar_endTime - processMeter_blueBar_beginTime;
            processMeter_blueBarSize =
                (1000.0 * processMeter_blueBarSize) / (u64) processBar_sizeDivisor;
            break;
    }
}
#endif

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

void processMeter_renderBar(Gfx** dlist, u32 color, f32 bar_size, s32 row) {
    gDPPipeSync(dlist[0]++);
    if (bar_size < 1.0) {
        gDPSetFillColor(dlist[0]++, color);
        gDPFillRectangle(
            dlist[0]++,
            40,
            row + (SCREEN_HEIGHT - 30),
            (SCREEN_WIDTH - 80) * bar_size + 40,
            row + (SCREEN_HEIGHT - 24)
        );
    } else {
        gDPSetFillColor(dlist[0]++, RGBA(120, 1, 120, 1));
        gDPFillRectangle(
            dlist[0]++,
            40,
            row + (SCREEN_HEIGHT - 30),
            SCREEN_WIDTH - 40,
            row + (SCREEN_HEIGHT - 24)
        );
    }
}
