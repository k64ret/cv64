#ifndef FIGURE_H
#define FIGURE_H

#include <ultra64.h>

// Types and functions common to figure-type structs (model_info, camera,
// light)

#define FIG_SIZE      0xA8
#define FIG_ARRAY_MAX 512

// Types
#define FIG_TYPE_STANDALONE         0x0004 // Assumption
#define FIG_TYPE_MAP_PIECE          0x0008
#define FIG_TYPE_HUD_ELEMENT        0x0010
#define FIG_TYPE_HIERARCHY_NODE     0x0040 // "offset", according to leftover strings
#define FIG_TYPE_LIGHT              0x0080
#define FIG_TYPE_CAMERA_ORTHO       0x0100
#define FIG_TYPE_CAMERA_PERSPECTIVE 0x0200
#define FIG_TYPE_0400               0x0400
#define FIG_TYPE_CAMERA_CUTSCENE                                                                   \
    0x0800 // Also assigned to the Player's mirrored copy in the Villa's mirror \
           // room
#define FIG_TYPE_HIERARCHY_FIRST_NODE 0x1000
#define FIG_TYPE_HIERARCHY_ROOT       0x2000 // "super", according to leftover strings
#define FIG_TYPE_HIDE                 0x8000

// Flags
#define FIG_FLAG_0040 0x0040
#define FIG_FLAG_0080 0x0080
#define FIG_FLAG_0100 0x0100
#define FIG_FLAG_0800 0x0800

// Misc. flags that aren't part of the set above
#define FIG_VARIABLE_TEXTURE_AND_PALETTE 0x40000000

typedef struct {
    s16 type;
    u16 flags;
    struct figHeader* prev;
    struct figHeader* sibling;
    struct figHeader* next;
    struct figHeader* parent;
} figHeader; // Size = 0x14

#define FIG_HEADER_SIZE sizeof(figHeader)

// Generic figure struct
typedef struct {
    figHeader header;
    u8 field_0x14[FIG_SIZE - FIG_HEADER_SIZE];
} figure; // Size = 0xA8

extern figHeader* fig_allocate(s16 type);
extern void clearAllFigs();
extern void figure_showModelAndChildren(figHeader*, u16);
extern void figure_hideSelfAndChildren(figHeader*, u16);
extern void* figure_setChild(figHeader* new_child, figHeader* self);

extern figure figures_array[FIG_ARRAY_MAX];

#endif
