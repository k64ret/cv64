/**
 * @file BDFE0.c
 */

#include "cv64.h"
#include "system_work.h"

// Reads a rectangular block of pixels from the active framebuffer into `dest`
void copyFramebufferRect(s32 arg0, s16 left, s16 top, s16 right, s16 bottom, u16* dest) {
    s32 row;
    s32 column;

    for (row = 0; row < SCREEN_HEIGHT; row++) {
        if (row >= top && row <= bottom) {
            for (column = 0; column < SCREEN_WIDTH; column += 4) {
                if ((column >= left) && (column <= right)) {
                    *dest++ = gFramebuffers[sys.frameBuffer_index][row * SCREEN_WIDTH + column];
                }
                if ((column >= (left - 1)) && (column < right)) {
                    *dest++ = gFramebuffers[sys.frameBuffer_index][row * SCREEN_WIDTH + column + 1];
                }
                if ((column >= (left - 2)) && (column + 2 <= right)) {
                    *dest++ = gFramebuffers[sys.frameBuffer_index][row * SCREEN_WIDTH + column + 2];
                }
                if ((column >= (left - 3)) && (column + 3 <= right)) {
                    *dest++ = gFramebuffers[sys.frameBuffer_index][row * SCREEN_WIDTH + column + 3];
                }
            }
        }
    }
}

// https://decomp.me/scratch/viWnX
#ifdef NON_MATCHING
/**
 * Returns:
 *  0:  No movement happened
 *  1:  Moving one option forwards  / down
 *  -1: Moving one option backwards / up
 */
s32 menuButton_selectNextOption(s32* option, s16* selection_delay_timer, s16 num_options) {
    s32 ret = 0;
    s32 roll_over;

    *selection_delay_timer = 0;

    if (num_options < 0) {
        num_options *= -1;
        roll_over = FALSE;
    } else {
        roll_over = TRUE;
    }

    ret = 0;
    if (moveSelectionCursor(CONT_UP)) {
        *option -= 1;

        if (*option < 0) {
            ret = -1;

            if (roll_over) {
                *option = num_options - 1;
            } else {
                *option = 0;
            }
        }
    }

    if (moveSelectionCursor(CONT_DOWN)) {
        *option += 1;

        if (*option >= num_options) {
            ret = 1;

            if (roll_over) {
                *option = 0;
            } else {
                *option = num_options - 1;
            }
        }
    }

    return ret;
}
#else
    #pragma GLOBAL_ASM("../asm/nonmatchings/common/BDFE0/menuButton_selectNextOption.s")
#endif

void Model_moveWithController(u8 cont_number, Model* model) {
    if (CONT_BTNS_HELD(cont_number, Z_TRIG)) {
        if (CONT_BTNS_PRESSED(cont_number, CONT_UP) || CONT_JOY_Y(cont_number) > 25) {
            model->position.z -= 1.0f;
        }
        if (CONT_BTNS_PRESSED(cont_number, CONT_DOWN) || CONT_JOY_Y(cont_number) < -25) {
            model->position.z += 1.0f;
        }
    } else {
        if (CONT_BTNS_PRESSED(cont_number, CONT_UP) || CONT_JOY_Y(cont_number) > 25) {
            model->position.y += 1.0f;
        }
        if (CONT_BTNS_PRESSED(cont_number, CONT_DOWN) || CONT_JOY_Y(cont_number) < -25) {
            model->position.y -= 1.0f;
        }
    }

    if (CONT_BTNS_PRESSED(cont_number, CONT_LEFT) || CONT_JOY_X(cont_number) < -25) {
        model->position.x -= 1.0f;
    }
    if (CONT_BTNS_PRESSED(cont_number, CONT_RIGHT) || CONT_JOY_X(cont_number) > 25) {
        model->position.x += 1.0f;
    }
}

void Model_copyPositionalParams(Model* src, Model* dest) {
    dest->position.x  = src->position.x;
    dest->position.y  = src->position.y;
    dest->position.z  = src->position.z;
    dest->size.x      = src->size.x;
    dest->size.y      = src->size.y;
    dest->size.z      = src->size.z;
    dest->angle.pitch = src->angle.pitch;
    dest->angle.yaw   = src->angle.yaw;
    dest->angle.roll  = src->angle.roll;
}
