#ifndef LIBRARY_PIECE_H
#define LIBRARY_PIECE_H

#include "actor.h"

#define BLUE_PIECE   0
#define YELLOW_PIECE 1
#define RED_PIECE    2

// ID 0x01D6
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[4];
    cv64_model_inf_t* model;
    u8 field_0x28[12];
    actorPositionalData positionalData;
    u8 field_0x46[2];
    /**
     * The spot in the planetarium where they're put when selecting an option in the puzzle
     */
    s32 planetarium_spot;
    u8 field_0x4C[32];
    /**
     * Same as planetarium_spot,
     * but this value is set as a result of calling
     * function `cutscene_setActorStateIfMatchingVariable1`
     */
    s32 state;
    ActorConfig* settings;
} libraryPiece;

void libraryPiece_entrypoint(libraryPiece* self);
void libraryPiece_init(libraryPiece* self);
void libraryPiece_loop(libraryPiece* self);

typedef void (*libraryPiece_func_t)(libraryPiece*);

#endif
