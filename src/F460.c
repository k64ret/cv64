#include "cv64.h"
#include "game/objects/engine/GameStateMgr.h"
#include "object.h"

void func_8000E860(cv64_object_hdr_t* self) {}

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/F460/func_8000E868_F468.s")

// clang-format on

void object_goToNextFuncIfTimerIsTwo(cv64_object_t* self) {
    if (self->header.current_function[self->header.functionInfo_ID].timer ==
        2) {
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.functionInfo_ID
        );
    }
}

void func_8000E8E0_F4E0(cv64_object_t* self) {
    if (self->header.current_function[self->header.functionInfo_ID].timer ==
        3) {
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.functionInfo_ID
        );
    }
}

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/F460/func_8000E928_F528.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/F460/func_8000E97C_F57C.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/F460/func_8000E9D0_F5D0.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/F460/func_8000EA24_F624.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/F460/func_8000EA78_F678.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/F460/func_8000EACC_F6CC.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/F460/gameplayMgr_main_checkExitFadeOutCompleted.s")

// clang-format on

void GameStateMgr_setupGameState(GameStateMgr* self) {
    s32* currentSlot;
    s32 var_s0;
    s32 temp2;

    for (currentSlot = ARRAY_START(self->current_game_state_slots);
         currentSlot < ARRAY_END(self->current_game_state_slots);
         currentSlot++) {
        temp2 = *currentSlot & 0x7FC00000;

        if (*currentSlot != 0) {
            *currentSlot &= 0x803FFFFF;

            if (*currentSlot > 0) {
                *currentSlot =
                    (s32) object_createAndSetChild(self, *currentSlot) &
                    ~0x80000000;
            }
            if (1) {
            }
            *currentSlot |= (temp2);
        } else
            break;
    }
}

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/F460/GameStateMgr_executeGameStateObjects.s")

// clang-format on

void GameStateMgr_executeGameStateObjectsAndFunctions(
    GameStateMgr* self, u32 execution_flags
) {
    s32* currentSlot;
    s32 slotData;
    void (*function)();

    for (currentSlot = ARRAY_START(self->current_game_state_slots);
         currentSlot < ARRAY_END(self->current_game_state_slots);
         currentSlot++) {
        slotData = *currentSlot;
        if (slotData != 0) {
            if (slotData & execution_flags) {
                if (slotData < 0) {
                    function = slotData & 0x803FFFFF;
                    function();
                } else {
                    object_execute(0x80000000 | (slotData & 0x803FFFFF));
                }
            }
        } else {
            break;
        }
    }
}
