#include "cv64.h"
#include "game/objects/engine/GameStateMgr.h"
#include "object.h"

void object_doNothing(cv64_object_t* self) {}

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/F460/object_goToNextFuncNoCondition.s")

// clang-format on

void object_goToNextFuncIfTimerIsTwo(cv64_object_t* self) {
    if (self->header.current_function[self->header.functionInfo_ID].timer ==
        2) {
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.functionInfo_ID
        );
    }
}

void object_goToNextFuncIfTimerIsThree(cv64_object_t* self) {
    if (self->header.current_function[self->header.functionInfo_ID].timer ==
        3) {
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.functionInfo_ID
        );
    }
}

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/F460/object_fadeOutNineFramesAndGoToNextFunc.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/F460/object_fadeOutFifteenFramesAndGoToNextFunc.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/F460/object_fadeOutTwentyOneFramesAndGoToNextFunc.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/F460/object_fadeOutThirtyFramesAndGoToNextFunc.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/F460/object_fadeOutFortyFiveFramesAndGoToNextFunc.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/F460/object_fadeOutSixtyFramesAndGoToNextFunc.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/F460/object_goToNextFuncIfNotFading.s")

// clang-format on

void GameStateMgr_setupGameState(GameStateMgr* self) {
    s32* currentSlot;
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
                    0x7FFFFFFF;
            }
            if (1) {
            }
            *currentSlot |= temp2;
        } else {
            break;
        }
    }
}

void GameStateMgr_executeGameStateUncappedFramerate(GameStateMgr* self) {
    s32* currentSlot;
    s32 slotData;
    void (*function)();

    for (currentSlot = ARRAY_START(self->current_game_state_slots);
         currentSlot < ARRAY_END(self->current_game_state_slots);
         currentSlot++) {
        slotData = *currentSlot;
        if (slotData == 0) {
            break;
        } else {
            if (slotData < 0) {
                function = slotData & 0x803FFFFF;
                function();
            } else {
                object_execute(K0BASE | (slotData & 0x803FFFFF));
            }
        }
    }
}

void GameStateMgr_executeGameStateCappedFramerate(
    GameStateMgr* self, u32 execution_flags
) {
    s32* currentSlot;
    s32 slotData;
    void (*function)();

    for (currentSlot = ARRAY_START(self->current_game_state_slots);
         currentSlot < ARRAY_END(self->current_game_state_slots);
         currentSlot++) {
        slotData = *currentSlot;
        if (slotData == 0) {
            break;
        } else {
            if (slotData & execution_flags) {
                if (slotData < 0) {
                    function = slotData & 0x803FFFFF;
                    function();
                } else {
                    object_execute(K0BASE | (slotData & 0x803FFFFF));
                }
            }
        }
    }
}
