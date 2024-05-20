/**
 * @file 1AE50.c
 */

#include "cv64.h"
#include "system_work.h"

s32 func_8001A250_1AE50(s32* arg0, u16* arg1, s16 arg2) {
    s32 var_v0;
    s32 var_v1 = 0;

    if (arg2 < 0) {
        arg2 *= -1;
        var_v0 = 0;
    } else {
        var_v0 = 1;
    }

    if (CONT_BTNS_PRESSED(CONT_0, CONT_UP) || CONT_BTNS_PRESSED(CONT_0, CONT_DOWN)) {
        *arg1 = 0;
    }

    if (CONT_BTNS_HELD(CONT_0, CONT_UP)) {
        if (*arg1 == 0) {
            *arg1 = 3;
            *arg0 = *arg0 - 1;
            if (*arg0 < 0) {
                var_v1 = -1;
                if (var_v0 != 0) {
                    *arg0 = arg2 - 1;
                } else {
                    *arg0 = 0;
                }
            }
        } else {
            *arg1 = *arg1 - 1;
        }
    }

    if (CONT_BTNS_HELD(CONT_0, CONT_DOWN)) {
        if (*arg1 == 0) {
            *arg1 = 3;
            *arg0 = *arg0 + 1;
            if (*arg0 >= arg2) {
                if (var_v0 != 0) {
                    *arg0  = 0;
                    var_v1 = 1;
                } else {
                    *arg0  = arg2 - 1;
                    var_v1 = 1;
                }
            }
        } else {
            *arg1 = *arg1 - 1;
        }
    }

    return var_v1;
}
