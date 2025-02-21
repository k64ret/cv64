/**
 * @file debug.c
 *
 * Contains code to render a process meter, used for profiling.
 *
 * The code also features a few empty functions, which may have been used for printing text
 * to the screen, since Legacy of Darkness has text-printing functions on its `debug.c` counterpart,
 * right before the process meter functions.
 *
 * Other N64 Konami games have a very similar looking unused process meter, such as MNSG, so it's possible
 * that this code comes from a common N64 Konami library.
 */

#include "debug.h"
#include "gfx/color.h"
#include "cv64.h"

s32 processMeter_number_of_divisions = 3;
f32 processBar_sizeDivisor           = 45720360.0f;

OSTime processMeter_greenBar_beginTime;
OSTime processMeter_greenBar_endTime;
OSTime processMeter_blueBar_beginTime;
OSTime processMeter_blueBar_endTime;
f32 processMeter_greenBarSize;
f32 processMeter_blueBarSize;

void func_80019BC0_1A7C0() {}

void func_80019BC8_1A7C8(s32 arg0) {}

// Used in `func_80066400`. Maybe a stubbed debug print function
void func_80019BD0_1A7D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {}

// Maybe another stubbed debug print function, based on the number of arguments
void func_80019BE4_1A7E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {}

void func_80019BF8_1A7F8() {}

void processMeter_updateTiming(OSMesgQueue* mq) {
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

    // @note This condition is never executed
    if (FALSE) {
        framerate = 60.0;
        total_count -= 1;
    }

    processMeter_setSizeDivisor(framerate * 1.0 * total_count);
}

void processMeter_setSizeDivisor(f32 size_divisor) {
    processBar_sizeDivisor = size_divisor;
}

/**
 * Updates the size of each process bar.
 *
 * For each bar, this function must be called at least twice:
 * Once with the `START` state, and another one with the `END` state,
 * in order for the size to update correctly.
 *
 * See the `DebugProcessMeterState` enum for all possible values.
 */
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

/**
 * Render both the green and blue process bars.
 */
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

/**
 * Renders each black division bar.
 */
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

/**
 * Renders an individual process bar.
 */
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
        // If the bar is too long, cap its length
        // and give the bar a red color.
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
