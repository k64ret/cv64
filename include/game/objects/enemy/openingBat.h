#ifndef OPENING_BAT_H
#define OPENING_BAT_H

#include "actor.h"

#define OPENINGBAT_NUMBER_OF_LIMBS 5 + 1

typedef struct {
    u8 field_0x00[8];
    cv64_model_inf_t* model;
    modelLighting* lighting;
    animationMgr* animMgr;
} openingBatDataInner;

typedef struct {
    u8 field_0x00[4];
    openingBatDataInner inner;
    u8 field_0x18[144];
} openingBatData;

// ID: 0x20A6
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[4];
    cv64_model_inf_t* model;
    openingBatData* data;
    u8 field_0x2C[68];
    ActorConfig* settings;
} openingBat;

void openingBat_entrypoint(openingBat* self);
void openingBat_createData(openingBat* self);
void openingBat_init(openingBat* self);
void openingBat_loop(openingBat* self);
void openingBat_destroy(openingBat* self);

typedef void (*openingBat_func_t)(openingBat*);

typedef enum openingBat_func_id {
    OPENINGBAT_CREATEDATA,
    OPENINGBAT_INIT,
    OPENINGBAT_LOOP,
    OPENINGBAT_DESTROY
} openingBat_func_id_t;

extern const u32 OPENINGBAT_DLIST;

#endif
