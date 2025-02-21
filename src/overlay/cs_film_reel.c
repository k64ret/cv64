/**
 * @file cs_film_reel.c
 *
 * This file contains the code that manages and draws an unused film reel texture
 * that can be drawn on the screen during cutscenes.
 */

#include "cv64.h"
#include "gfx/camera.h"
#include "objects/cutscene/cs_film_reel.h"
#include "system_work.h"
#include <ultra64.h>

// clang-format off

CSFilmReelFunc ovl_csfilmreel_funcs[] = {
    CSFilmReel_CheckInitialConditions,
    CSFilmReel_Init,
    CSFilmReel_Loop,
    CSFilmReel_Destroy
};

// clang-format on

static u32 CSFilmReel_draw(CSFilmReelGraphicData*);

void CSFilmReel_Entrypoint(CSFilmReel* self) {
    ENTER(self, ovl_csfilmreel_funcs);
}

void CSFilmReel_CheckInitialConditions(CSFilmReel* self) {
    if (BITS_HAS(sys.cutscene_flags, CUTSCENE_FLAG_FILM_REEL_EFFECT)) {
        /**
         * @bug The film reel effect is supposed to be disabled if the cutscene is displayed
         *      in fullscreen, without borders.
         *
         *      If attempting to load the effect on fullscreen cutscenes, the game should just
         *      destroy the effect. However, on practice, it just waits until the `CUTSCENE_FLAG_DISPLAY_WIDESCREEN_BORDERS`
         *      flag is set (done by some cutscenes manually after they're spawned), due to the early `return`.
         *
         *      When said flag is set, the effect will be enabled, and the texture will get cutoff in the locations where the
         *      upper and lower borders would be.
         */
        if (BITS_NOT_HAS(sys.cutscene_flags, CUTSCENE_FLAG_DISPLAY_WIDESCREEN_BORDERS)) {
            return;
        }

        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );

        return;
    }

    self->header.destroy(self);
}

/**
 * Have to include ASM here until we can solve the "undefined reference" errors
 * related to `CSFILMREEL_TEXTURE`. Otherwise, the function matches.
 */
#ifdef NON_MATCHING
void CSFilmReel_Init(CSFilmReel* self) {
    CSFilmReelData* data;
    CSFilmReelGraphicContainer* graphic_container;
    Model* left_reel_model;
    Model* right_reel_model;
    CSFilmReelGraphicData* graphic_data;
    Camera* display_camera;
    u32 material_dlist;
    CSFilmReelGraphicRawData* raw_data;
    Gfx* current_dlist;

    // Create data and setup the effect's display camera
    data =
        (*object_allocEntryInListAndClear)(self, HEAP_KIND_MULTIPURPOSE, sizeof(CSFilmReelData), 0);

    display_camera = (*Camera_Create)(FIG_TYPE_CAMERA_ORTHO, 8);
    (*Figure_SetSibling)(display_camera, common_camera_game_view);
    display_camera->position.y = 0.0f;
    display_camera->position.x = 0.0f;
    display_camera->position.z = 101.0f;

    // Create and setup the left reel stripe
    left_reel_model              = (*Model_createAndSetChild)(FIG_TYPE_HUD_ELEMENT, display_camera);
    self->left_reel_model        = left_reel_model;
    left_reel_model->dlist       = &CSFILMREEL_DL;
    left_reel_model->assets_file = NI_ASSETS_FILM_REEL_CUTSCENE_EFFECT;
    left_reel_model->position.z  = 0.0f;
    left_reel_model->position.y  = 0.0f;
    left_reel_model->size.z      = 3.5f;
    left_reel_model->size.y      = 3.5f;
    left_reel_model->size.x      = 3.5f;
    left_reel_model->position.x  = -136.0f;

    // Create and setup the right reel stripe
    right_reel_model        = (*Model_createAndSetChild)(FIG_TYPE_HUD_ELEMENT, display_camera);
    self->right_reel_model  = right_reel_model;
    right_reel_model->dlist = &CSFILMREEL_DL;
    right_reel_model->assets_file = NI_ASSETS_FILM_REEL_CUTSCENE_EFFECT;
    right_reel_model->position.z  = 0.0f;
    right_reel_model->position.y  = 0.0f;
    right_reel_model->size.z      = 3.5f;
    right_reel_model->size.y      = 3.5f;
    right_reel_model->size.x      = 3.5f;
    right_reel_model->position.x  = 136.0f;

    // Allocate graphic data structs
    graphic_data =
        (*object_allocEntryInList)(self, HEAP_KIND_MULTIPURPOSE, sizeof(CSFilmReelGraphicData), 3);
    data->graphic_data = graphic_data;
    graphic_container  = (*object_allocGraphicContainerEntryInList)(
        self, HEAP_KIND_MULTIPURPOSE, sizeof(CSFilmReelGraphicRawData), 4
    );
    graphic_data->graph_container = graphic_container;

    if (1) {
    }

    // Initialize graphic data structs
    raw_data      = graphic_data->graph_container->header.data_ptrs[sys.current_graphic_buffer];
    current_dlist = (Gfx*) ARRAY_START(raw_data->dlists);
    gSPEndDisplayList(current_dlist++);

    raw_data      = graphic_data->graph_container->header.data_ptrs[sys.previous_graphic_buffer];
    current_dlist = (Gfx*) ARRAY_START(raw_data->dlists);
    gSPEndDisplayList(current_dlist++);

    // Set graphic data parameters
    graphic_data->material_dlist =
        GET_UNMAPPED_ADDRESS(NI_ASSETS_FILM_REEL_CUTSCENE_EFFECT, &CSFILMREEL_MATERIAL_DL);
    graphic_data->texture_ptr =
        GET_UNMAPPED_ADDRESS(NI_ASSETS_FILM_REEL_CUTSCENE_EFFECT, &CSFILMREEL_TEXTURE);
    graphic_data->tile               = G_TX_RENDERTILE;
    graphic_data->vertical_pos       = 0.0f;
    graphic_data->alpha_change_speed = 8;
    graphic_data->alpha = graphic_data->dont_increase_alpha = graphic_data->field_0x12 = 0;
    data->scrolling_speed                                                              = 2.0f;

    left_reel_model                  = self->left_reel_model;
    right_reel_model                 = self->right_reel_model;
    material_dlist                   = CSFilmReel_draw(graphic_data);
    left_reel_model->material_dlist  = material_dlist;
    right_reel_model->material_dlist = material_dlist;

    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}
#else
    #pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cs_film_reel/CSFilmReel_Init.s")
#endif

void CSFilmReel_Loop(CSFilmReel* self) {
    CSFilmReelData* data                = self->data;
    CSFilmReelGraphicData* graphic_data = data->graphic_data;
    Model* left_reel_model              = self->left_reel_model;
    Model* right_reel_model             = self->right_reel_model;
    u32 material_dlist;

    // If the effect is active, increase the transparency until the texture is fully opaque
    if (BITS_HAS(sys.cutscene_flags, CUTSCENE_FLAG_FILM_REEL_EFFECT)) {
        if (graphic_data->dont_increase_alpha == FALSE) {
            graphic_data->alpha += graphic_data->alpha_change_speed;
            if (graphic_data->alpha > 255) {
                graphic_data->alpha               = 255;
                graphic_data->dont_increase_alpha = TRUE;
            }
        }
        // Otherwise, decrease the transparency and destroy the effect
    } else {
        if (graphic_data->alpha < graphic_data->alpha_change_speed) {
            graphic_data->alpha = FALSE;
            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.function_info_ID
            );
        } else {
            graphic_data->alpha -= graphic_data->alpha_change_speed;
        }
    }

    // Increase vertical scrolling. The scrolling speed is capped at 32
    graphic_data->vertical_pos += data->scrolling_speed;

    // Downwards scrolling
    if (data->scrolling_speed < 0.0) {
        if (graphic_data->vertical_pos < 0.0) {
            graphic_data->vertical_pos += 32.0f;
        }
        // Upwards scrolling
    } else {
        if (graphic_data->vertical_pos > 32.0f) {
            graphic_data->vertical_pos -= 32.0f;
        }
    }

    // Draw the effect
    material_dlist                   = CSFilmReel_draw(graphic_data);
    left_reel_model->material_dlist  = material_dlist;
    right_reel_model->material_dlist = material_dlist;
}

void CSFilmReel_Destroy(CSFilmReel* self) {
    self->header.destroy(self);
}

/**
 * Setup the texture parameters when displaying it to the screen
 *
 * - dlist: Display list pointer
 * - texture_ptr: Texture raw data pointer
 * - tile: Tile descriptor index
 * - ult: Upper-left (vertical) coordinate of the texture tile
 */
#define CSFILMREEL_SET_TEXTURE_PARAMS(dlist, texture_ptr, tile, ult)                               \
    gDPSetTextureImage(dlist++, G_IM_FMT_I, G_IM_SIZ_16b, 1, texture_ptr);                         \
    gDPSetTile(                                                                                    \
        dlist++,                                                                                   \
        G_IM_FMT_I,                                                                                \
        G_IM_SIZ_16b,                                                                              \
        0,                                                                                         \
        0x0000,                                                                                    \
        G_TX_LOADTILE,                                                                             \
        0,                                                                                         \
        G_TX_NOMIRROR | G_TX_WRAP,                                                                 \
        5,                                                                                         \
        G_TX_NOLOD,                                                                                \
        G_TX_NOMIRROR | G_TX_WRAP,                                                                 \
        5,                                                                                         \
        G_TX_NOLOD                                                                                 \
    );                                                                                             \
    gDPLoadSync(dlist++);                                                                          \
    gDPLoadBlock(dlist++, G_TX_LOADTILE, 0, 0, 255, 1024);                                         \
    gDPPipeSync(dlist++);                                                                          \
    gDPSetTile(                                                                                    \
        dlist++,                                                                                   \
        G_IM_FMT_I,                                                                                \
        G_IM_SIZ_4b,                                                                               \
        2,                                                                                         \
        0x0000,                                                                                    \
        tile,                                                                                      \
        0,                                                                                         \
        G_TX_NOMIRROR | G_TX_WRAP,                                                                 \
        5,                                                                                         \
        G_TX_NOLOD,                                                                                \
        G_TX_NOMIRROR | G_TX_WRAP,                                                                 \
        5,                                                                                         \
        G_TX_NOLOD                                                                                 \
    );                                                                                             \
    gDPSetTileSize(dlist++, tile, 0, ult, 124, 124);

u32 CSFilmReel_draw(CSFilmReelGraphicData* graphic_data) {
    CSFilmReelGraphicRawData* raw_data =
        (CSFilmReelGraphicRawData*)
            graphic_data->graph_container->header.data_ptrs[sys.current_graphic_buffer];
    Gfx* current_dlist      = (Gfx*) ARRAY_START(raw_data->dlists);
    Gfx* dlist_buffer_start = current_dlist;

    gDPPipeSync(current_dlist++);
    gSPDisplayList(current_dlist++, graphic_data->material_dlist);
    gSPTexture(current_dlist++, 0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON);
    gDPSetCombineMode(current_dlist++, G_CC_MODULATEIA_PRIM, G_CC_PASS2);
    gDPSetPrimColor(current_dlist++, 0, 0, 153, 153, 153, graphic_data->alpha);
    CSFILMREEL_SET_TEXTURE_PARAMS(
        current_dlist,
        graphic_data->texture_ptr,
        graphic_data->tile,
        (s32) ((graphic_data->vertical_pos * 4.0f) + 0.5)
    )
    gSPEndDisplayList(current_dlist++);
    return (*osVirtualToPhysical)(dlist_buffer_start);
}
