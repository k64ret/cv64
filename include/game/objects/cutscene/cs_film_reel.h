#ifndef CS_FILM_REEL_H
#define CS_FILM_REEL_H

#include "object.h"
#include "gfx/model.h"
#include <ultra64.h>

typedef struct CSFilmReelGraphicRawData {
    Gfx dlists[21];
} CSFilmReelGraphicRawData;

typedef struct CSFilmReelGraphicContainer {
    GraphicContainerHeader header;
    CSFilmReelGraphicRawData data;
} CSFilmReelGraphicContainer;

typedef struct CSFilmReelGraphicData {
    CSFilmReelGraphicContainer* graph_container;
    Gfx* field_0x04;
    /**
     * Upper-left corner of texture to load
     */
    f32 height;
    /**
     * Points to the start of the texture's raw data
     */
    void* texture_ptr;
    u8 tile;
    u8 dont_increase_alpha;
    u8 field_0x12;
    u8 field_0x13;
    u16 alpha;
    u16 alpha_change_rate;
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

#endif
