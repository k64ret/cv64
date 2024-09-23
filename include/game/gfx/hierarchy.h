#ifndef HIERARCHY_H
#define HIERARCHY_H

#include "math.h"

// Hierarchy node flags
#define ALLOW_CHANGING_TEXTURE_AND_PALETTE 0x2000
#define CREATE_NEXT_NODE                   0x4000
#define DONT_CREATE_SIBLING                0x8000

typedef struct {
    u32 dlist;
    u16 flags;
    Vec3 position;
} hierarchy_node;

typedef struct {
    s32 assets_file_ID;
    hierarchy_node nodes[];
} hierarchy;

#endif
