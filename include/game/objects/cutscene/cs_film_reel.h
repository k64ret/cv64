#ifndef CS_FILM_REEL_H
#define CS_FILM_REEL_H

#include "object.h"
#include "gfx/model.h"
#include <ultra64.h>

/**
 * Display List buffers
 */
typedef struct CSFilmReelGraphicRawData {
    Gfx dlists[21];
} CSFilmReelGraphicRawData;

typedef struct CSFilmReelGraphicContainer {
    GraphicContainerHeader header;
    CSFilmReelGraphicRawData data;
} CSFilmReelGraphicContainer;

typedef struct CSFilmReelGraphicData {
    CSFilmReelGraphicContainer* graph_container;
    /**
     * The display list that is used for configuring the texture
     * prior to be loaded in
     */
    Gfx* material_dlist;
    /**
     * Current vertical position of the texture during scrolling
     */
    f32 vertical_pos;
    /**
     * Points to the start of the texture's raw data
     */
    void* texture_ptr;
    /**
     * Tile descriptor index
     */
    u8 tile;
    /**
     * If `TRUE`, avoids increasing the transparency
     * (i.e. fading in the texture)
     */
    u8 dont_increase_alpha;
    u8 field_0x12;
    u8 field_0x13;
    /**
     * Texture's transparency
     */
    u16 alpha;
    /**
     * The rate at which the texture changes
     * transparency over time
     */
    u16 alpha_change_speed;
} CSFilmReelGraphicData;

typedef struct CSFilmReelData {
    CSFilmReelGraphicData* graphic_data;
    f32 scrolling_speed;
} CSFilmReelData;

// ID: 0x202B
typedef struct CSFilmReel {
    ObjectHeader header;
    u8 field_0x20[12];
    Model* left_reel_model;
    Model* right_reel_model;
    CSFilmReelData* data;
    u8 field_0x38[8];
    CSFilmReelGraphicData* graphic_data;
    u8 field_0x44[48];
} CSFilmReel;

void CSFilmReel_Entrypoint(CSFilmReel* self);
void CSFilmReel_CheckInitialConditions(CSFilmReel* self);
void CSFilmReel_Init(CSFilmReel* self);
void CSFilmReel_Loop(CSFilmReel* self);
void CSFilmReel_Destroy(CSFilmReel* self);
u32 CSFilmReel_Draw(CSFilmReelGraphicData* graphic_data);

typedef void (*CSFilmReelFunc)(CSFilmReel*);

extern const u32 CSFILMREEL_TEXTURE;
extern const u32 CSFILMREEL_DL;
extern const u32 CSFILMREEL_MATERIAL_DL;

#endif
