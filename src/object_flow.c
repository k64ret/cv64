/**
 * @file object_flow.c
 *
 * Contains code that tells an object to advance to certain functions in its functions arrays
 * if they fulfill certain conditions.
 *
 * It also contains code that set up and execute game states.
 */

#include "cv64.h"
#include "game/objects/engine/GameStateMgr.h"
#include "game/fade.h"
#include "object.h"

#define LOCAL_GO_TO_NEXT_FUNC(object)                                                              \
    do {                                                                                           \
        (*object_curLevel_goToNextFuncAndClearTimer)(                                              \
            (object)->header.current_function, &(object)->header.function_info_ID                  \
        );                                                                                         \
    } while (0)

#define FADE_OUT_AND_GO_TO_NEXT_FUNC(fade_time, object)                                            \
    do {                                                                                           \
        (*Fade_SetSettings)(FADE_OUT, (s16) (fade_time), 0, 0, 0);                                 \
        LOCAL_GO_TO_NEXT_FUNC(object);                                                             \
    } while (0)

void object_doNothing(cv64_object_t* self) {}

// Turn off clang-format to preserve whitespace for matching
// clang-format off

void object_goToNextFuncNoCondition(cv64_object_t* self) { LOCAL_GO_TO_NEXT_FUNC(self); }

// clang-format on

void object_goToNextFuncIfTimerIsTwo(cv64_object_t* self) {
    if (self->header.current_function[self->header.function_info_ID].timer == 2) {
        LOCAL_GO_TO_NEXT_FUNC(self);
    }
}

void object_goToNextFuncIfTimerIsThree(cv64_object_t* self) {
    if (self->header.current_function[self->header.function_info_ID].timer == 3) {
        LOCAL_GO_TO_NEXT_FUNC(self);
    }
}

// Turn off clang-format to preserve whitespace for matching
// clang-format off

void object_fadeOutNineFramesAndGoToNextFunc(cv64_object_t* self) { FADE_OUT_AND_GO_TO_NEXT_FUNC(9, self); }

void object_fadeOutFifteenFramesAndGoToNextFunc(cv64_object_t* self) { FADE_OUT_AND_GO_TO_NEXT_FUNC(15, self); }

void object_fadeOutTwentyOneFramesAndGoToNextFunc(cv64_object_t* self) { FADE_OUT_AND_GO_TO_NEXT_FUNC(21, self); }

void object_fadeOutThirtyFramesAndGoToNextFunc(cv64_object_t* self) { FADE_OUT_AND_GO_TO_NEXT_FUNC(30, self); }

void object_fadeOutFortyFiveFramesAndGoToNextFunc(cv64_object_t* self) { FADE_OUT_AND_GO_TO_NEXT_FUNC(45, self); }

void object_fadeOutSixtyFramesAndGoToNextFunc(cv64_object_t* self) { FADE_OUT_AND_GO_TO_NEXT_FUNC(60, self); }

void object_goToNextFuncIfNotFading(cv64_object_t* self) { if ((*Fade_IsFading)()) return; LOCAL_GO_TO_NEXT_FUNC(self); }

// clang-format on

void GameStateMgr_setupGameState(GameStateMgr* self) {
    s32* currentSlot;
    s32 temp2;

    for (currentSlot = ARRAY_START(self->current_game_state_slots);
         currentSlot < ARRAY_END(self->current_game_state_slots);
         currentSlot++) {
        temp2 = BITS_MASK(*currentSlot, 0x7FC00000);
        if (*currentSlot != 0) {
            BITS_ASSIGN_MASK(*currentSlot, 0x803FFFFF);
            if (*currentSlot > 0) {
                *currentSlot =
                    BITS_MASK((s32) object_createAndSetChild(self, *currentSlot), 0x7FFFFFFF);
            }
            if (1) {
            }
            BITS_SET(*currentSlot, temp2);
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

        if (slotData == 0)
            break;

        if (slotData < 0) {
            function = BITS_MASK(slotData, 0x803FFFFF);
            function();
        } else {
            object_execute(K0BASE | BITS_MASK(slotData, 0x803FFFFF));
        }
    }
}

void GameStateMgr_executeGameStateCappedFramerate(GameStateMgr* self, u32 execution_flags) {
    s32* currentSlot;
    s32 slotData;
    void (*function)();

    for (currentSlot = ARRAY_START(self->current_game_state_slots);
         currentSlot < ARRAY_END(self->current_game_state_slots);
         currentSlot++) {
        slotData = *currentSlot;

        if (slotData == 0)
            break;

        if (BITS_HAS(slotData, execution_flags)) {
            if (slotData < 0) {
                function = BITS_MASK(slotData, 0x803FFFFF);
                function();
            } else {
                object_execute(K0BASE | BITS_MASK(slotData, 0x803FFFFF));
            }
        }
    }
}
