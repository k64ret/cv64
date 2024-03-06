#include "cv64.h"
#include "object.h"
#include "system_work.h"
#include "cutscene_ID.h"
#include "fade.h"
#include "objects/player/player.h"

extern void camera_setClippingAndScissoring(s16);

typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[40];
    f32 player_animation_speed;
    u8 field_0x4C[28];
    u16 current_time;
    s16 max_time;
    u8 field_0x6C[4];
    s8 skipCutscene;
    s8 set_player_anim_speed;
    u8 field_0x72[2];
} cutscene_object_placeholder;

typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[32];
    cv64_object_t* CSFilmReelDraw; // Module ID 0x202B
    /**
     * NOTE:
     * Follows the cutscene ID listing WITHOUT the empty slots (for example,
     * cutscene 0x3C here is 0x32)
     */
    s32 cutscene_ID;
    cutscene_object_placeholder* cutscene_object;
    u8 field_0x4C[40];
} cutsceneMgr;

typedef void (*cv64_cutscenemgr_func_t)(cutsceneMgr*);

extern cv64_cutscenemgr_func_t cutsceneMgr_functions[];

void cutsceneMgr_entrypoint(cutsceneMgr* self) {
    ENTER(self, cutsceneMgr_functions);
}

void cutsceneMgr_main(cutsceneMgr* self) {
    playerVisualData* visual_data;

    if (sys.cutscene_ID == CUTSCENE_ID_NONE)
        return;

    if (sys.cutscene_ID < 3U) {
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.functionInfo_ID
        );
    } else if (ptr_PlayerData != NULL) {
        visual_data = &ptr_PlayerData->visualData;

        if (((*visual_data).flags & DEAD) ||
            (sys.SaveStruct_gameplay.player_status & DEAD)) {
            sys.entrance_cutscene_ID = CUTSCENE_ID_NONE;
            sys.cutscene_ID = CUTSCENE_ID_NONE;
        } else {
            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.functionInfo_ID
            );
        }
    }
}

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/common/cutscene_manager/cutsceneMgr_createCutscene.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/cutscene_manager/cutsceneMgr_setClippingAndScissoring.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/cutscene_manager/cutsceneMgr_loop.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/common/cutscene_manager/cutsceneMgr_stopCutscene.s")

// clang-format on
