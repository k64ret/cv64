/**
 * File: icemanAssetsLoader.c
 * Description:
 *   The only purpose of the three objects below is to load
 *   the assets file for each of the Iceman variants (via their `objects_file_info` entry)
 *   To do that, the objects themselves don't have to run any code,
 *   therefore it is empty.
 * Associated objects: 0x20A3, 0x20A4, 0x20A5
 *
 * Mapped by the TLB? = Yes
 */

#include "objects/enemy/mudAndLavaManAssetsLoader.h"
#include "objects/enemy/bloodManAssetsLoader.h"
#include "objects/enemy/iceManAssetsLoader.h"

void func_0F000150(cv64_object_hdr_t* self);

void (*cv64_ovl_icemanAssetsLoader_funcs[])(cv64_object_hdr_t* self) = {func_0F000150};

void mudAndLavaManAssetsLoader_entrypoint(mudAndLavaManAssetsLoader* self) {
    ENTER(self, cv64_ovl_icemanAssetsLoader_funcs);
}

void bloodManAssetsLoader_entrypoint(bloodManAssetsLoader* self) {
    ENTER(self, cv64_ovl_icemanAssetsLoader_funcs);
}

void iceManAssetsLoader_entrypoint(iceManAssetsLoader* self) {
    ENTER(self, cv64_ovl_icemanAssetsLoader_funcs);
}

void func_0F000150(cv64_object_hdr_t* self) {}
