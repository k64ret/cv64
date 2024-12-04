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

/**
 * This list stores two values per entry:
 *
 * The map ID, and the text ID in the `entranceMapNameDisplay_mapNames`
 * message pool where the name for said map can be found.
 */
s16 entranceMapNameDisplay_mapList[] = {
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

/**
 * The width of the background model per map
 */
s16 entranceMapNameDisplay_mapNamesWidth[] = {
    154, 100,  46,  68,
    226, 120, 104, 156,
    172, 160, 140, 114,
    104
};

/**
 * Buffer where the display lists for the background model
 * are stored at.
 * Only the first seven display lists from this buffer are used.
 */
Gfx entranceMapNameDisplay_bgModelDlists[16] = {0};

/**
 * The vertices associated to the background model.
 *
 * The background model's blue color is assigned in
 * the vertices' color field (the last 4 values on each vertex, see below).
 *
 * @note The X position for each vertex is determined
 *       in function `entranceMapNameDisplay_init`
 */
Vtx entranceMapNameDisplay_bgModelVertices[] = {
    {{{     0,     -36,     0}, 0, {   0,    0}, {127, 127, 191, 255}}},
    {{{     0,     -36,     0}, 0, {   0,    0}, {127, 127, 191, 255}}},
    {{{     0,     -60,     0}, 0, {   0,    0}, {0,     0, 255,   0}}},
    {{{     0,     -60,     0}, 0, {   0,    0}, {0,     0, 255,   0}}},
};

/**
 * First material assigned to the background model
 */
Gfx entranceMapNameDisplay_bgModelMaterial1[] = {
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

/**
 * Second material assigned to the background model
 */
Gfx entranceMapNameDisplay_bgModelMaterial2[] = {
    gsDPPipeSync(),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_SHADING_SMOOTH),
    gsSPEndDisplayList(),
};

entranceMapNameDisplayFuncs entranceMapNameDisplay_functions[] = {
    entranceMapNameDisplay_init,
    entranceMapNameDisplay_show,
    entranceMapNameDisplay_idle,
    entranceMapNameDisplay_hide,
    entranceMapNameDisplay_destroy
};

// clang-format on

void entranceMapNameDisplay_entrypoint(entranceMapNameDisplay* self) {
    ENTER(self, entranceMapNameDisplay_functions);
}

void entranceMapNameDisplay_init(entranceMapNameDisplay* self) {
    Model* bg_model;
    Gfx* bg_model_dlist;
    s16 i;
    s32 display_name;
    s32 text_ID;
    s16 map_name_width;

    /**
     * The map's name will display if either we've entered through the first entrance only,
     * or if we've entered Clock Tower through any of its entrances.
     */
    display_name = FALSE;
    if (sys.SaveStruct_gameplay.map != TOKEITOU_NAI) {
        if (sys.SaveStruct_gameplay.spawn == 0) {
            display_name = TRUE;
        }
    } else {
        display_name = TRUE;
    }

    if (display_name == FALSE) {
        self->header.destroy(self);
        return;
    }

    /**
     * Delay showing the map's name until the currently playing cutscene is over
     */
    if (!(sys.cutscene_flags & CUTSCENE_FLAG_PLAYING)) {
        /**
         * Create the "Restart this stage" save
         *
         * @note Because this function is only called here,
         *       it means that the game can only create the
         *       "Restart this stage" save on those maps that spawn the
         *       `entranceMapNameDisplay` object.
         */
        (*initSave_BeginningOfStageState)();

        /**
         * Obtains the map name's text ID
         *
         * @note
         *
         * - entranceMapNameDisplay_mapList[i]: The map ID
         *   entranceMapNameDisplay_mapList[i + 1]: The map name's text ID
         *
         * - If the map we're in does not appear in the `entranceMapNameDisplay_mapList`,
         *   then it will display the "Forest of Silence" name, as the
         *   `text_ID` value is assigned to 0 by default
         */
        text_ID = 0;
        i       = 0;
        while (entranceMapNameDisplay_mapList[i] >= 0) {
            if (entranceMapNameDisplay_mapList[i] == sys.SaveStruct_gameplay.map) {
                text_ID = entranceMapNameDisplay_mapList[i + 1];
                break;
            }
            i += 2;
        }
        self->text_ID = text_ID;

        /**
         * Setup the positions for the background model vertices,
         * given the map name's width value
         */
        map_name_width = ((entranceMapNameDisplay_mapNamesWidth[text_ID] + 8) / 2) + 4;
        entranceMapNameDisplay_bgModelVertices[1].v.ob[0] =
            entranceMapNameDisplay_bgModelVertices[3].v.ob[0] = map_name_width;
        entranceMapNameDisplay_bgModelVertices[0].v.ob[0] =
            entranceMapNameDisplay_bgModelVertices[2].v.ob[0] = -map_name_width;

        /**
         * Setup the background model's display lists
         */
        bg_model_dlist = &entranceMapNameDisplay_bgModelDlists;
        gDPPipeSync(bg_model_dlist++);
        gSPDisplayList(
            bg_model_dlist++, (*osVirtualToPhysical)(entranceMapNameDisplay_bgModelMaterial1)
        );
        gDPPipeSync(bg_model_dlist++);
        gSPVertex(
            bg_model_dlist++, (*osVirtualToPhysical)(entranceMapNameDisplay_bgModelVertices), 4, 0
        );
        gSP2Triangles(bg_model_dlist++, 2, 1, 0, 0, 3, 2, 1, 0);
        gSPDisplayList(
            bg_model_dlist++, (*osVirtualToPhysical)(entranceMapNameDisplay_bgModelMaterial2)
        );
        gSPEndDisplayList(bg_model_dlist++);

        /**
         * Create and setup the background model
         */
        bg_model = self->bg_model =
            (*Model_createAndSetChild)(FIG_TYPE_HUD_ELEMENT, common_camera_8009B440);
        if (1) {
        }
        bg_model->assets_file = 0;
        bg_model->dlist       = (*osVirtualToPhysical)(&entranceMapNameDisplay_bgModelDlists);
        bg_model->flags |= FIG_FLAG_APPLY_PRIMITIVE_COLOR;
        bg_model->primitive_color.integer = RGBA(255, 255, 255, 0);
        self->should_hide                 = FALSE;
        self->max_active_time             = 90;
        self->bg_model_transparency       = 0;

        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void entranceMapNameDisplay_show(entranceMapNameDisplay* self) {
    s32 temp;
    Model* bg_model = self->bg_model;
    u16* map_name_ptr;
    MfdsState* map_name_textbox;
    s16 map_name_width;

    self->bg_model_transparency += 2184.46666666666667;

    if (self->bg_model_transparency < 0x7FFF) {
        bg_model->primitive_color.a = self->bg_model_transparency / 256;
        return;
    }

    /**
     * Create and setup the map name's textbox
     */
    map_name_ptr     = (*text_getMessageFromPool)(&entranceMapNameDisplay_mapNames, self->text_ID);
    map_name_width   = entranceMapNameDisplay_mapNamesWidth[self->text_ID];
    self->field_0x5C = 0;
    map_name_textbox = (*textbox_create)(
        self, common_camera_HUD, MFDS_FLAG_OPEN_TEXTBOX | MFDS_FLAG_ALLOW_VARIABLE_SPEED
    );
    (*textbox_setPos)(map_name_textbox, (s16) ((320 - map_name_width) / 2), 160, 1);
    (*textbox_setDimensions)(map_name_textbox, 1, map_name_width, 0, 0);
    (*textbox_setMessagePtr)(
        map_name_textbox,
        GET_UNMAPPED_ADDRESS(NI_OVL_ENTRANCE_MAP_NAME_DISPLAY, map_name_ptr),
        NULL,
        0
    );
    (u16) map_name_textbox->position.x += self->text_position_offset.x;
    (u16) map_name_textbox->position.y += self->text_position_offset.y;
    self->map_name_textbox = map_name_textbox;

    self->current_active_time = 0;
    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void entranceMapNameDisplay_idle(entranceMapNameDisplay* self) {
    MfdsState* map_name_textbox = self->map_name_textbox;

    if (self->hide_text == TRUE) {
        map_name_textbox->flags |= MFDS_FLAG_HIDE_TEXTBOX;
    } else {
        map_name_textbox->flags &= ~MFDS_FLAG_HIDE_TEXTBOX;
    }

    if (self->max_active_time != 0) {
        if (self->max_active_time >= self->current_active_time) {
            self->current_active_time++;
        } else {
            self->should_hide = TRUE;
        }
    }

    if ((self->should_hide) || (sys.current_opened_menu != MENU_ID_NOT_ON_MENU)) {
        map_name_textbox = self->map_name_textbox;
        map_name_textbox->flags |= MFDS_FLAG_CLOSE_TEXTBOX;
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
