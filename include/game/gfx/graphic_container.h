#ifndef GRAPHIC_CONTAINER_H
#define GRAPHIC_CONTAINER_H

#include <ultra64.h>

typedef struct GraphicContainerHeader {
    void* field_0x00;
    /**
     * One per graphic buffer
     */
    void* data_ptrs[2];
    u8 field_0x0C[4];
} GraphicContainerHeader;

#endif
