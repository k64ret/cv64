#ifndef FIGURE_H
#define FIGURE_H

#include <ultra64.h>

// Types and functions common to figure-type structs (model_info, camera,
// struct_47)

// Types
#define STANDALONE         0x0004 // Assumption
#define MAP_PIECE          0x0008
#define HUD_ELEMENT        0x0010
#define HIERARCHY_NODE     0x0040 // "offset", according to leftover strings
#define STRUCT_47          0x0080
#define CAMERA_ORTHO       0x0100
#define CAMERA_PERSPECTIVE 0x0200
#define CAMERA_CUTSCENE                                                        \
    0x0800 // Also assigned to the Player's mirrored copy in the Villa's mirror
           // room
#define HIERARCHY_FIRST_NODE 0x1000
#define HIERARCHY_ROOT       0x2000 // "super", according to leftover strings
#define HIDE                 0x8000

typedef struct {
    s16 type;
    u16 flags;
    struct figHeader* prev;
    struct figHeader* sibling;
    struct figHeader* next;
    struct figHeader* parent;
} figHeader;

figHeader* fig_allocate(s16 type);

#endif
