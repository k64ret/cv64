#include "memory.h"

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/memory_clear.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/memory_copy.s")

void heap_init(cv64_heap_kind_t kind, cv64_heapblock_hdr_t* first_block_ptr,
               s32 heap_size, u32 additional_flags) {
    heaps[kind].flags = additional_flags | HEAP_ACTIVE;
    heaps[kind].size = ALIGN8(heap_size);
    heaps[kind].heap_start = ALIGN8((s32) first_block_ptr);
    first_block_ptr->flags = HEAP_BLOCK_FREE;
    first_block_ptr->size = heaps[kind].size - sizeof(cv64_heapblock_hdr_t);
}

void heap_free(cv64_heap_kind_t kind) { heaps[kind].flags = HEAP_INACTIVE; }

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/heap_writebackDCache.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/initHeaps.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_80000D68_1968.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_80000D74_1974.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/heap_alloc.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/heap_allocWithAlignment.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/heapBlock_updateBlockMaxSize.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_80001008_1C08.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/heapBlock_free.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_80001080_1C80.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_800010A0_1CA0.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_800010C8_1CC8.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_80001110_1D10.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_80001148_1D48.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_800011AC_1DAC.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_800011DC_1DDC.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_80001228_1E28.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_80001260_1E60.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_800012C0_1EC0.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_800012D8_1ED8.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_800012F4_1EF4.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/func_80001338_1F38.s")

void object_curLevel_goToNextFunc(u16 current_functionInfo[],
                                  s16* functionInfo_ID) {
    u16* functionInfo_entry;
    u16* entry_to_clean;

    functionInfo_entry = &current_functionInfo[*functionInfo_ID];
    entry_to_clean = functionInfo_entry + 1;
    (*functionInfo_entry)++; // Set current entry to next function
    while (entry_to_clean < (u16*) functionInfo_ID) {
        *entry_to_clean = 0;
        entry_to_clean++;
    }
}

void object_prevLevel_goToNextFunc(u16 current_functionInfo[],
                                   s16* functionInfo_ID) {
    u16* functionInfo_entry;
    u16* entry_to_clean;

    if (*functionInfo_ID > 0) {
        functionInfo_entry = &current_functionInfo[*functionInfo_ID];
        functionInfo_entry--;
        (*functionInfo_entry)++;
        entry_to_clean = functionInfo_entry + 1;
        while (entry_to_clean < (u16*) functionInfo_ID) {
            *entry_to_clean = 0;
            entry_to_clean++;
        }
    }
}

void object_nextLevel_goToNextFunc(u16 current_functionInfo[],
                                   s16* functionInfo_ID) {
    u16* functionInfo_entry;
    u16* entry_to_clean;

    functionInfo_entry = &current_functionInfo[*functionInfo_ID];
    functionInfo_entry++;
    if (functionInfo_entry < (u16*) functionInfo_ID) {
        entry_to_clean = functionInfo_entry + 1;
        (*functionInfo_entry)++;
        while (entry_to_clean < (u16*) functionInfo_ID) {
            *entry_to_clean = 0;
            entry_to_clean++;
        }
    }
}

void object_curLevel_goToNextFuncAndClearTimer(
    cv64_obj_func_inf_t current_functionInfo[], s16* functionInfo_ID) {
    cv64_obj_func_inf_t* functionInfo_entry;
    cv64_obj_func_inf_t* entry_to_clean;

    functionInfo_entry = &current_functionInfo[*functionInfo_ID];
    functionInfo_entry->whole++;   // Set current function to the next function
    functionInfo_entry->timer = 0; // Set timer to 0
    entry_to_clean = functionInfo_entry + 1;
    while ((cv64_obj_func_inf_t*) entry_to_clean <
           (cv64_obj_func_inf_t*) functionInfo_ID) {
        entry_to_clean->whole = 0;
        entry_to_clean++;
    }
}

void object_curLevel_goToPrevFunc(cv64_obj_func_inf_t current_functionInfo[],
                                  s16* functionInfo_ID) {
    cv64_obj_func_inf_t* functionInfo_entry;
    u16* entry_to_clean;

    functionInfo_entry = &current_functionInfo[*functionInfo_ID];
    functionInfo_entry->whole--;
    entry_to_clean = (u16*) functionInfo_entry + 1;
    while (entry_to_clean < (u16*) functionInfo_ID) {
        *entry_to_clean = 0;
        entry_to_clean++;
    }
}

void object_prevLevel_goToPrevFunc(u16 current_functionInfo[],
                                   s16* functionInfo_ID) {
    u16* functionInfo_entry;
    u16* entry_to_clean;

    if (*functionInfo_ID > 0) {
        functionInfo_entry = &current_functionInfo[*functionInfo_ID];
        functionInfo_entry--;
        (*functionInfo_entry)--;
        entry_to_clean = functionInfo_entry + 1;
        while (entry_to_clean < (u16*) functionInfo_ID) {
            *entry_to_clean = 0;
            entry_to_clean++;
        }
    }
}

void object_nextLevel_goToPrevFunc(u16 current_functionInfo[],
                                   s16* functionInfo_ID) {
    u16* functionInfo_entry;
    u16* entry_to_clean;

    functionInfo_entry = &current_functionInfo[*functionInfo_ID];
    functionInfo_entry++;
    if (functionInfo_entry < (u16*) functionInfo_ID) {
        entry_to_clean = functionInfo_entry + 1;
        (*functionInfo_entry)--;
        while (entry_to_clean < (u16*) functionInfo_ID) {
            *entry_to_clean = 0;
            entry_to_clean++;
        }
    }
}

void object_curLevel_goToPrevFuncAndClearTimer(u16 current_functionInfo[],
                                               s16* functionInfo_ID) {
    u16* functionInfo_entry;
    u16* entry_to_clean;

    functionInfo_entry = &current_functionInfo[*functionInfo_ID];
    (*functionInfo_entry)--;
    (u8)(*functionInfo_entry) = 0;
    entry_to_clean = functionInfo_entry + 1;
    while (entry_to_clean < (u16*) functionInfo_ID) {
        *entry_to_clean = 0;
        entry_to_clean++;
    }
}

void object_curLevel_goToFunc(u16 current_functionInfo[], s16* functionInfo_ID,
                              s32 function) {
    u16* functionInfo_entry;
    u16* entry_to_clean;

    functionInfo_entry = &current_functionInfo[*functionInfo_ID];
    *functionInfo_entry = function;
    entry_to_clean = functionInfo_entry + 1;
    while (entry_to_clean < (u16*) functionInfo_ID) {
        *entry_to_clean = 0;
        entry_to_clean++;
    }
}

void object_curLevel_goToFuncInLevel(u16 current_functionInfo[],
                                     s16* functionInfo_ID, s16 level,
                                     s32 function) {
    u16* functionInfo_entry;
    u16* entry_to_clean;

    functionInfo_entry = &current_functionInfo[level];
    *functionInfo_entry = function;
    entry_to_clean = functionInfo_entry + 1;
    while (entry_to_clean < (u16*) functionInfo_ID) {
        *entry_to_clean = 0;
        entry_to_clean++;
    }
}

void object_prevLevel_goToFunc(u16 current_functionInfo[], s16* functionInfo_ID,
                               s32 function) {
    u16* functionInfo_entry;
    u16* entry_to_clean;

    if (*functionInfo_ID > 0) {
        functionInfo_entry = &current_functionInfo[*functionInfo_ID];
        functionInfo_entry--;
        *functionInfo_entry = function;
        entry_to_clean = functionInfo_entry + 1;
        while (entry_to_clean < (u16*) functionInfo_ID) {
            *entry_to_clean = 0;
            entry_to_clean++;
        }
    }
}

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/object_nextLevel_goToFunc.s")
