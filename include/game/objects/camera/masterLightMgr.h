#ifndef MASTER_LIGHT_MGR_H
#define MASTER_LIGHT_MGR_H

#include "object.h"
#include "gfx/light.h"

// ID: 0x006D
typedef struct masterLightMgr {
    ObjectHeader header;
    u8 field_0x20[20];
    FigureLight* master_light;
    u8 field_0x28[76];
} masterLightMgr;

#endif
