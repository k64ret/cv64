#ifndef ICE_MAN_ASSETS_LOADER_H
#define ICE_MAN_ASSETS_LOADER_H

#include "object.h"

// ID: 0x20A5
typedef struct {
    ObjectHeader header;
    u8 field_0x20[OBJECT_SIZE - 0x20];
} iceManAssetsLoader;

void iceManAssetsLoader_entrypoint(iceManAssetsLoader* self);

#endif
