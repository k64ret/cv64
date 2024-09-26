#ifndef MUD_LAVA_MAN_ASSETS_LOADER_H
#define MUD_LAVA_MAN_ASSETS_LOADER_H

#include "object.h"

// ID: 0x20A3
typedef struct {
    ObjectHeader header;
    u8 field_0x20[OBJECT_SIZE - 0x20];
} mudAndLavaManAssetsLoader;

void mudAndLavaManAssetsLoader_entrypoint(mudAndLavaManAssetsLoader* self);

#endif
