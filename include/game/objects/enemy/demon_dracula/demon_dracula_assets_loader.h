#ifndef DEMON_DRACULA_ASSETS_LOADER_H
#define DEMON_DRACULA_ASSETS_LOADER_H

#include "object.h"

// ID: 0x20B7
typedef struct DemonDraculaAssetsLoader {
    ObjectHeader header;
    u8 field_0x20[OBJECT_SIZE - 0x20];
} DemonDraculaAssetsLoader;

void DemonDraculaAssetsLoader_entrypoint(DemonDraculaAssetsLoader* self);

#endif
