#ifndef CREDITS_MGR_H
#define CREDITS_MGR_H

#include "object.h"

// ID: 0x201B
typedef struct {
    ObjectHeader header;
    u8 field_0x20[20];
    u32 field_0x34[16];
} creditsMgr;

void creditsMgr_entrypoint(creditsMgr* self); // 0x0F000000
void creditsMgr_init(creditsMgr* self);       // 0x0F000070
void creditsMgr_loop(creditsMgr* self);       // 0x0F00016C
void creditsMgr_exit(creditsMgr* self);       // 0x0F0001F0

typedef void (*cv64_ovl_creditsmgr_func_t)(creditsMgr*);

#endif
