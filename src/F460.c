#include "cv64.h"
#include "game/objects/engine/GameStateMgr.h"
#include "game/fade.h"
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

// Turn off clang-format to preserve whitespace for matching
// clang-format off

void object_fadeOutNineFramesAndGoToNextFunc(cv64_object_t* self) {            \
    (*fade_setSettings)(FADE_OUT, 9, 0, 0, 0);
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.functionInfo_ID
    );
}

void object_fadeOutFifteenFramesAndGoToNextFunc(cv64_object_t* self) {         \
    (*fade_setSettings)(FADE_OUT, 15, 0, 0, 0);
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.functionInfo_ID
    );
}

void object_fadeOutTwentyOneFramesAndGoToNextFunc(cv64_object_t* self) {       \
    (*fade_setSettings)(FADE_OUT, 21, 0, 0, 0);
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.functionInfo_ID
    );
}

void object_fadeOutThirtyFramesAndGoToNextFunc(cv64_object_t* self) {          \
    (*fade_setSettings)(FADE_OUT, 30, 0, 0, 0);
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.functionInfo_ID
    );
}

void object_fadeOutFortyFiveFramesAndGoToNextFunc(cv64_object_t* self) {       \
    (*fade_setSettings)(FADE_OUT, 45, 0, 0, 0);
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.functionInfo_ID
    );
}

void object_fadeOutSixtyFramesAndGoToNextFunc(cv64_object_t* self) {           \
    (*fade_setSettings)(FADE_OUT, 60, 0, 0, 0);
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.functionInfo_ID
    );
}

// clang-format on

// clang-format off

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
