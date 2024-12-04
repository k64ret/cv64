/**
 * @file entrance_map_name_display.c
 *
 * This file contains the code for the `entranceMapNameDisplay` object,
 * which is in charge of displaying the map's name when entering for the first time.
 */

#include "objects/menu/entrance_map_name_display.h"
#include "cv64.h"
#include "system_work.h"

// clang-format off

u16 entranceMapNameDisplay_mapNames[] = {
#include "objects/menu/entranceMapNameDisplay_mapNames.msg"
};

s16 entranceMapNameDisplay_mapsThatDisplayMessage[] = {
    MORI,         ENTRANCE_MAP_NAME_MORI,
    TOUOKUJI,     ENTRANCE_MAP_NAME_TOUOKUJI,
    NAKANIWA,     ENTRANCE_MAP_NAME_NAKANIWA,
    CHIKA_KODO,   ENTRANCE_MAP_NAME_CHIKA_KODO,
    CHIKA_SUIRO,  ENTRANCE_MAP_NAME_CHIKA_SUIRO,
    HONMARU_B1F,  ENTRANCE_MAP_NAME_HONMARU_B1F,
    KETTOU_TOU,   ENTRANCE_MAP_NAME_KETTOU_TOU,
    KAGAKU_TOU,   ENTRANCE_MAP_NAME_KAGAKU_TOU,
    SHOKEI_TOU,   ENTRANCE_MAP_NAME_SHOKEI_TOU,
    MAHOU_TOU,    ENTRANCE_MAP_NAME_MAHOU_TOU,
    TOU_TURO,     ENTRANCE_MAP_NAME_TOU_TURO,
    TOKEITOU_NAI, ENTRANCE_MAP_NAME_TOKEITOU_NAI,
    TENSHU,       ENTRANCE_MAP_NAME_TENSHU,
    MAP_NONE,     ENTRANCE_MAP_NAME_NONE
};

s16 map_names_width[] = {
    154, 100, 46, 68,
    226, 120, 104, 156,
    172, 160, 140, 114,
    104
};

Gfx D_0F000950_E60C50[7] = {0};

u8 D_0F000988[72] = {0};

Vtx D_0F0009D0_E60CD0[] = {
    {{{     0,     -36,     0}, 0, {   0,    0}, {127, 127, 191, 255}}},
    {{{     0,     -36,     0}, 0, {   0,    0}, {127, 127, 191, 255}}},
    {{{     0,     -60,     0}, 0, {   0,    0}, {0,     0, 255,   0}}},
    {{{     0,     -60,     0}, 0, {   0,    0}, {0,     0, 255,   0}}},
};

Gfx D_0F000A10_E60D10[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_OFF),
    gsDPSetRenderMode(G_RM_PASS, G_RM_CLD_SURF2),
    gsDPSetCombineLERP(SHADE, 0, PRIMITIVE, 0, SHADE, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetColorDither(G_CD_MAGICSQ),
    gsDPSetAlphaDither(G_AD_DISABLE),
    gsSPEndDisplayList(),
};

Gfx D_0F000A68_E60D68[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

entranceMapNameDisplayFuncs entranceMapNameDisplay_functions[] = {
    entranceMapNameDisplay_init,
    entranceMapNameDisplay_display,
    entranceMapNameDisplay_loop,
    entranceMapNameDisplay_hide,
    entranceMapNameDisplay_destroy
};

// clang-format on

void entranceMapNameDisplay_entrypoint(entranceMapNameDisplay* self) {
    ENTER(self, entranceMapNameDisplay_functions);
}

void entranceMapNameDisplay_init(entranceMapNameDisplay* self) {
    Model* bg_model;
    Gfx* temp;
    s16 i;
    s32 var_v0;
    s32 text_ID;
    s16 map_name_width;

    var_v0 = 0;
    if (sys.SaveStruct_gameplay.map != TOKEITOU_NAI) {
        if (sys.SaveStruct_gameplay.spawn == 0) {
            var_v0 = 1;
        }
    } else {
        var_v0 = 1;
    }

    if (var_v0 == 0) {
        self->header.destroy(self);
        return;
    }

    if (!(sys.cutscene_flags & CUTSCENE_FLAG_PLAYING)) {
        (*initSave_BeginningOfStageState)();
        text_ID = 0;
        i       = 0;
        while (entranceMapNameDisplay_mapsThatDisplayMessage[i] >= 0) {
            if (entranceMapNameDisplay_mapsThatDisplayMessage[i] == sys.SaveStruct_gameplay.map) {
                text_ID = entranceMapNameDisplay_mapsThatDisplayMessage[i + 1];
                break;
            }
            i += 2;
        }
        self->text_ID = text_ID;

        map_name_width               = ((map_names_width[text_ID] + 8) / 2) + 4;
        D_0F0009D0_E60CD0[1].v.ob[0] = D_0F0009D0_E60CD0[3].v.ob[0] = map_name_width;
        D_0F0009D0_E60CD0[0].v.ob[0] = D_0F0009D0_E60CD0[2].v.ob[0] = -map_name_width;

        temp = &D_0F000950_E60C50;
        gDPPipeSync(temp++);
        gSPDisplayList(temp++, (*osVirtualToPhysical)(D_0F000A10_E60D10));
        gDPPipeSync(temp++);
        gSPVertex(temp++, (*osVirtualToPhysical)(D_0F0009D0_E60CD0), 4, 0);
        gSP2Triangles(temp++, 2, 1, 0, 0, 3, 2, 1, 0);
        gSPDisplayList(temp++, (*osVirtualToPhysical)(D_0F000A68_E60D68));
        gSPEndDisplayList(temp++);

        bg_model = self->bg_model =
            (*Model_createAndSetChild)(FIG_TYPE_HUD_ELEMENT, common_camera_8009B440);
        if (1) {
        }
        bg_model->assets_file = 0;
        bg_model->dlist       = (*osVirtualToPhysical)(&D_0F000950_E60C50);
        bg_model->flags |= FIG_FLAG_APPLY_PRIMITIVE_COLOR;
        bg_model->primitive_color.integer = RGBA(255, 255, 255, 0);
        self->text_not_active             = 0;
        self->max_active_time             = 90;
        self->bg_model_transparency       = 0;

        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void entranceMapNameDisplay_display(entranceMapNameDisplay* self) {
    s32 temp;
    Model* bg_model = self->bg_model;
    u16* map_name_ptr;
    MfdsState* textbox;
    s16 map_name_width;

    self->bg_model_transparency += 2184.46666666666667;
    if (self->bg_model_transparency < 0x7FFF) {
        bg_model->primitive_color.a = self->bg_model_transparency / 256;
        return;
    }
    map_name_ptr     = (*text_getMessageFromPool)(&entranceMapNameDisplay_mapNames, self->text_ID);
    map_name_width   = map_names_width[self->text_ID];
    self->field_0x5C = 0;
    textbox          = (*textbox_create)(
        self, common_camera_HUD, MFDS_FLAG_OPEN_TEXTBOX | MFDS_FLAG_ALLOW_VARIABLE_SPEED
    );
    (*textbox_setPos)(textbox, (s16) ((320 - map_name_width) / 2), 160, 1);
    (*textbox_setDimensions)(textbox, 1, map_name_width, 0, 0);
    (*textbox_setMessagePtr)(
        textbox, GET_UNMAPPED_ADDRESS(NI_OVL_ENTRANCE_MAP_NAME_DISPLAY, map_name_ptr), NULL, 0
    );
    (u16) textbox->position.x += self->text_position_offset.x;
    (u16) textbox->position.y += self->text_position_offset.y;
    self->textbox             = textbox;
    self->current_active_time = 0;
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void entranceMapNameDisplay_loop(entranceMapNameDisplay* self) {
    MfdsState* textbox = self->textbox;

    if (self->disable_text == TRUE) {
        textbox->flags |= MFDS_FLAG_HIDE_TEXTBOX;
    } else {
        textbox->flags &= ~MFDS_FLAG_HIDE_TEXTBOX;
    }

    if (self->max_active_time != 0) {
        if (self->max_active_time >= self->current_active_time) {
            self->current_active_time++;
        } else {
            self->text_not_active = TRUE;
        }
    }

    if ((self->text_not_active) || (sys.current_opened_menu != MENU_ID_NOT_ON_MENU)) {
        textbox = self->textbox;
        textbox->flags |= MFDS_FLAG_CLOSE_TEXTBOX;
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void entranceMapNameDisplay_hide(entranceMapNameDisplay* self) {
    Model* bg_model = self->bg_model;

    self->bg_model_transparency -= 2184.46666666666667;
    if (self->bg_model_transparency < 0) {
        self->bg_model_transparency = 0;
        bg_model->type |= ~FIG_TYPE_SHOW;
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
    bg_model->primitive_color.a = self->bg_model_transparency / 256;
}

void entranceMapNameDisplay_destroy(entranceMapNameDisplay* self) {
    self->header.destroy(self);
}
