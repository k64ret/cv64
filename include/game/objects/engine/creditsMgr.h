#ifndef CREDITS_MGR_H
#define CREDITS_MGR_H

#include "object.h"

// ID: 0x201B
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[20];
    u32 field_0x34[16];
} creditsMgr;

void creditsMgr_entrypoint(creditsMgr* self); // 0x0F000000
void creditsMgr_init(creditsMgr* self);       // 0x0F000070
void creditsMgr_loop(creditsMgr* self);       // 0x0F00016C
void creditsMgr_exit(creditsMgr* self);       // 0x0F0001F0

void (*creditsMgr_functions[])(creditsMgr* self) = {
    creditsMgr_init, creditsMgr_loop, creditsMgr_exit};

#endif
