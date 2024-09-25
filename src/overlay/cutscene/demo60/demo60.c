#include "objects/cutscene/demo60.h"
#include "memory.h"
#include "system_work.h"

// clang-format off

extern u8 rot_Reindhart_blessing[];
extern u8 trans_Reindhart_blessing[];
extern u8 rot_Carrie_blessing[];
extern u8 trans_Carrie_blessing[];
extern Demo60Func Demo60_functions[];
extern CutsceneCoordinatesSettings D_0E001190[];
extern CutsceneCoordinatesSettings D_0E0011E8[];
extern CutsceneCoordinatesSettings D_0E001284[];

// clang-format on

void Demo60_Entrypoint(Demo60* self) {
    ENTER(self, Demo60_functions);
}

void Demo60_Init(Demo60* self) {
    Demo60Data* data;

    (*Fade_SetSettings)(FADE_OUT, 1, 0, 0, 0);
    self->state = DEMO60_FADE_IN;
    data        = (Demo60Data*) (*object_allocEntryInListAndClear)(
        self, HEAP_KIND_MULTIPURPOSE, sizeof(Demo60Data), 1
    );
    self->skip_cutscene = FALSE;
    data->game_camera   = common_camera_game_view;
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cutscene/demo60/demo60/Demo60_CreateCutsceneCamera.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cutscene/demo60/demo60/Demo60_GetPlayerModelAndSetBorders.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cutscene/demo60/demo60/Demo60_Loop.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cutscene/demo60/demo60/Demo60_Destroy.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cutscene/demo60/demo60/Demo60_PlayPlayerBlessingAnim.s")

// clang-format on
