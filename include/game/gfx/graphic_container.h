#ifndef GRAPHIC_CONTAINER_H
#define GRAPHIC_CONTAINER_H

#include "cv64.h"

typedef struct GraphicContainerHeader {
    void* field_0x00;
    void* data_ptrs[NUM_GRAPHIC_BUFFERS];
    /**
     * Related to file decompression?
     * See 0x80010298
     */
    u8 field_0x0C[4];
} GraphicContainerHeader;

#endif
