#ifndef BLOOD_MAN_ASSETS_LOADER_H
#define BLOOD_MAN_ASSETS_LOADER_H

#include "object.h"

// ID: 0x20A4
typedef struct {
    ObjectHeader header;
    u8 field_0x20[OBJECT_SIZE - 0x20];
} bloodManAssetsLoader;

void bloodManAssetsLoader_entrypoint(bloodManAssetsLoader* self);

#endif
