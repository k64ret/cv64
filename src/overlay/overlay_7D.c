/**
 * File: overlay_7D.c
 * Description:
 * Associated objects: 0x20A3, 0x20A4, 0x20A5
 *
 * Mapped by the TLB? = Yes
 */

#include "objects/enemy/object_20A3.h"
#include "objects/enemy/object_20A4.h"
#include "objects/enemy/object_20A5.h"

void func_0F000150(cv64_object_hdr_t* self);

void (*cv64_ovl_7d_funcs[])(cv64_object_hdr_t* self) = {func_0F000150};

void obj20A3_entrypoint(object_20A3* self) { ENTER(self, cv64_ovl_7d_funcs); }

void obj20A4_entrypoint(object_20A4* self) { ENTER(self, cv64_ovl_7d_funcs); }

void obj20A5_entrypoint(object_20A5* self) { ENTER(self, cv64_ovl_7d_funcs); }

void func_0F000150(cv64_object_hdr_t* self) {}
