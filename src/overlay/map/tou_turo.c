#include "cv64.h"
#include "objects/map/tou_turo/door.h"
#include "system_work.h"
#include "gfx/struct_47.h"
#include <ultra64.h>

void cv64_ovl_touturo_door_entrypoint(cv64_ovl_touturo_door_t* self) {
    ENTER(self, cv64_ovl_touturo_door_funcs);
}

void cv64_ovl_touturo_door_init(cv64_ovl_touturo_door_t* self) {
    s32 id;
    cv64_actor_settings_t* settings = self->settings;
    cv64_model_inf_t* model;

    if (settings) {
    }

    model = self->model =
        modelInfo_createRootNode(FIG_TYPE_STANDALONE, D_8018CDE0[0]);

    if (settings) {
    }

    actor_model_set_pos_and_angle((cv64_actor_t*) self, model);
    model->flags |= (0x800 | 0x100);

    model->assets_file_ID = sys.map_assets_file_IDs[0];
    model->dlist = cv64_ovl_touturo_door_dlists[settings->variable_1];

    CV64_COLOR_RGBA_TO_U32(model->primitive_color) =
        CV64_COLOR_RGBA_TO_U32(sys.primitive_color);
    CV64_COLOR_RGBA_TO_U32(model->fog_color) =
        CV64_COLOR_RGBA_TO_U32(sys.background_color);

    self->header.ID |= OBJ_FLAG_STAGE_OBJECT;

    self->map_actor_model =
        getMapActorModelEntryFromArray(model->dlist, model->assets_file_ID);
    model->map_actor_model = self->map_actor_model;

    self->close_time = 30;

    (*object_curLevel_goToNextFuncAndClearTimer)(self->header.current_function,
                                                 &self->header.functionInfo_ID);
}

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/map/tou_turo/cv64_ovl_touturo_door_loop.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/map/tou_turo/cv64_ovl_touturo_door_exit_check_event_flags.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/map/tou_turo/cv64_ovl_touturo_door_entrance_check_event_flags.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/map/tou_turo/cv64_ovl_touturo_door_entrance_close_door.s")

// clang-format on
