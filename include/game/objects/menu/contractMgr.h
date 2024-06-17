#ifndef CONTRACT_MGR_H
#define CONTRACT_MGR_H

#include "objects/cutscene/interactuables.h"
#include "objects/effect/distortion.h"

// ID: 0x213B
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[20];
    interactuables* contract_item;
    void* field_0x38;
    s32 field_0x3C;
    obj_distortion* distortion;
    u8 field_0x44[OBJECT_SIZE - 0x44];
} contractMgr;

#endif
