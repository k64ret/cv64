#ifndef HIERARCHY_H
#define HIERARCHY_H

#include "bit.h"
#include "math.h"

enum HierarchyNodeFlag {
    ALLOW_CHANGING_TEXTURE_AND_PALETTE = BIT(13),
    CREATE_NEXT_NODE                   = BIT(14),
    DONT_CREATE_SIBLING                = BIT(15)
};

/**
 * Accepts values from `HierarchyNodeFlag` OR'ed together
 */
typedef u16 HierarchyNodeFlags;

typedef struct HierarchyNode {
    u32 dlist;
    HierarchyNodeFlags flags;
    Vec3 position;
} HierarchyNode;

typedef struct Hierarchy {
    s32 assets_file_ID;
    HierarchyNode nodes[];
} Hierarchy;

#endif
