#include "memory.h"
#include "object.h"
#include "system_work.h"

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/memory_clear.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/memory_copy.s")

void heap_init(
    cv64_heap_kind_t kind,
    cv64_heapblock_hdr_t* first_block_ptr,
    s32 heap_size,
    u32 additional_flags
) {
    heaps[kind].flags      = additional_flags | HEAP_ACTIVE;
    heaps[kind].size       = ALIGN8(heap_size);
    heaps[kind].heap_start = ALIGN8(first_block_ptr);
    first_block_ptr->flags = HEAP_BLOCK_FREE;
    first_block_ptr->size  = heaps[kind].size - sizeof(cv64_heapblock_hdr_t);
}

void heap_free(cv64_heap_kind_t kind) {
    heaps[kind].flags = HEAP_INACTIVE;
}

void heap_writebackDCache(void) {
    cv64_heap_inf_t* first;
    cv64_heap_inf_t* current_heap;

    first = &heaps[0], current_heap = &heaps[HEAP_NUM - 1];

    do {
        if (BITS_HAS(current_heap->flags, HEAP_WRITE_BACK_CACHE_TO_RAM)) {
            osWritebackDCache(current_heap->heap_start, current_heap->size);
        }
        current_heap--;
    } while ((u32) first <= (u32) current_heap);
}

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/initHeaps.s")

void func_80000D68_1968(s32 arg0, u32 arg1) {}

s32 func_80000D74_1974(s32 arg0) {
    return 0;
}

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/heap_alloc.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/heap_allocWithAlignment.s")

// https://decomp.me/scratch/tHw91
#pragma GLOBAL_ASM("../asm/nonmatchings/memory/heapBlock_updateBlockMaxSize.s")

void* func_80001008_1C08(cv64_heap_kind_t heap_kind, u32 size) {
    u32 data;
    cv64_heapblock_hdr_t* data_header;

    data = (u32) heap_alloc(heap_kind, size * 2);
    if (data == NULL) {
        return NULL;
    }

    data_header               = data - sizeof(cv64_heapblock_hdr_t);
    data_header->data_ptrs[0] = data;
    BITS_SET(data_header->flags, HEAP_BLOCK_4000);
    data_header->data_ptrs[1] = data + size;
    data_header->field_0x08   = data_header->data_ptrs[sys.current_dlist_buffer];

    return &data_header->field_0x08;
}

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/heapBlock_free.s")

// https://decomp.me/scratch/eT3oh
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

void object_curLevel_goToNextFunc(
    cv64_object_func_inf_t current_functionInfo[], s16* function_info_ID
) {
    u16* functionInfo_entry;
    u16* entry_to_clean;

    functionInfo_entry = &current_functionInfo[*function_info_ID];

    for (entry_to_clean = functionInfo_entry + 1, (*functionInfo_entry)++;
         entry_to_clean < (u16*) function_info_ID;
         entry_to_clean++) {
        *entry_to_clean = 0;
    }
}

void object_prevLevel_goToNextFunc(
    cv64_object_func_inf_t current_functionInfo[], s16* function_info_ID
) {
    u16* functionInfo_entry;
    u16* entry_to_clean;

    if (*function_info_ID <= 0)
        return;

    functionInfo_entry = &current_functionInfo[*function_info_ID];
    functionInfo_entry--;
    (*functionInfo_entry)++;

    for (entry_to_clean = functionInfo_entry + 1; entry_to_clean < (u16*) function_info_ID;
         entry_to_clean++) {
        *entry_to_clean = 0;
    }
}

void object_nextLevel_goToNextFunc(
    cv64_object_func_inf_t current_functionInfo[], s16* function_info_ID
) {
    u16* functionInfo_entry;
    u16* entry_to_clean;

    functionInfo_entry = &current_functionInfo[*function_info_ID];
    functionInfo_entry++;

    if (functionInfo_entry >= (u16*) function_info_ID)
        return;

    for (entry_to_clean = functionInfo_entry + 1, (*functionInfo_entry)++;
         entry_to_clean < (u16*) function_info_ID;
         entry_to_clean++) {
        *entry_to_clean = 0;
    }
}

void object_curLevel_goToNextFuncAndClearTimer(
    cv64_object_func_inf_t current_functionInfo[], s16* function_info_ID
) {
    cv64_object_func_inf_t* functionInfo_entry;
    cv64_object_func_inf_t* entry_to_clean;

    functionInfo_entry = &current_functionInfo[*function_info_ID];
    functionInfo_entry->whole++;   // Set current function to the next function
    functionInfo_entry->timer = 0; // Set timer to 0

    for (entry_to_clean = functionInfo_entry + 1;
         (cv64_object_func_inf_t*) entry_to_clean < (cv64_object_func_inf_t*) function_info_ID;
         entry_to_clean++) {
        entry_to_clean->whole = 0;
    }
}

void object_curLevel_goToPrevFunc(
    cv64_object_func_inf_t current_functionInfo[], s16* function_info_ID
) {
    cv64_object_func_inf_t* functionInfo_entry;
    u16* entry_to_clean;

    functionInfo_entry = &current_functionInfo[*function_info_ID];
    functionInfo_entry->whole--;

    for (entry_to_clean = (u16*) functionInfo_entry + 1; entry_to_clean < (u16*) function_info_ID;
         entry_to_clean++) {
        *entry_to_clean = 0;
    }
}

void object_prevLevel_goToPrevFunc(
    cv64_object_func_inf_t current_functionInfo[], s16* function_info_ID
) {
    u16* functionInfo_entry;
    u16* entry_to_clean;

    if (*function_info_ID <= 0)
        return;

    functionInfo_entry = &current_functionInfo[*function_info_ID];
    functionInfo_entry--;
    (*functionInfo_entry)--;

    for (entry_to_clean = functionInfo_entry + 1; entry_to_clean < (u16*) function_info_ID;
         entry_to_clean++) {
        *entry_to_clean = 0;
    }
}

void object_nextLevel_goToPrevFunc(
    cv64_object_func_inf_t current_functionInfo[], s16* function_info_ID
) {
    u16* functionInfo_entry;
    u16* entry_to_clean;

    functionInfo_entry = &current_functionInfo[*function_info_ID];
    functionInfo_entry++;

    if (functionInfo_entry >= (u16*) function_info_ID)
        return;

    for (entry_to_clean = functionInfo_entry + 1, (*functionInfo_entry)--;
         entry_to_clean < (u16*) function_info_ID;
         entry_to_clean++) {
        *entry_to_clean = 0;
    }
}

void object_curLevel_goToPrevFuncAndClearTimer(
    cv64_object_func_inf_t current_functionInfo[], s16* function_info_ID
) {
    u16* functionInfo_entry;
    u16* entry_to_clean;

    functionInfo_entry = &current_functionInfo[*function_info_ID];
    (*functionInfo_entry)--;

    // clang-format off
    (u8) (*functionInfo_entry) = 0;
    // clang-format on

    for (entry_to_clean = functionInfo_entry + 1; entry_to_clean < (u16*) function_info_ID;
         entry_to_clean++) {
        *entry_to_clean = 0;
    }
}

void object_curLevel_goToFunc(
    cv64_object_func_inf_t current_functionInfo[], s16* function_info_ID, s32 function
) {
    u16* functionInfo_entry;
    u16* entry_to_clean;

    functionInfo_entry  = &current_functionInfo[*function_info_ID];
    *functionInfo_entry = function;

    for (entry_to_clean = functionInfo_entry + 1; entry_to_clean < (u16*) function_info_ID;
         entry_to_clean++) {
        *entry_to_clean = 0;
    }
}

void object_curLevel_goToFuncInLevel(
    cv64_object_func_inf_t current_functionInfo[], s16* function_info_ID, s16 level, s32 function
) {
    u16* functionInfo_entry;
    u16* entry_to_clean;

    functionInfo_entry  = &current_functionInfo[level];
    *functionInfo_entry = function;

    for (entry_to_clean = functionInfo_entry + 1; entry_to_clean < (u16*) function_info_ID;
         entry_to_clean++) {
        *entry_to_clean = 0;
    }
}

void object_prevLevel_goToFunc(
    cv64_object_func_inf_t current_functionInfo[], s16* function_info_ID, s32 function
) {
    u16* functionInfo_entry;
    u16* entry_to_clean;

    if (*function_info_ID <= 0)
        return;

    functionInfo_entry = &current_functionInfo[*function_info_ID];
    functionInfo_entry--;
    *functionInfo_entry = function;

    for (entry_to_clean = functionInfo_entry + 1; entry_to_clean < (u16*) function_info_ID;
         entry_to_clean++) {
        *entry_to_clean = 0;
    }
}

void object_nextLevel_goToFunc(
    cv64_object_func_inf_t current_functionInfo[], s16* function_info_ID, s32 function
) {
    u16* functionInfo_entry;
    u16* entry_to_clean;

    functionInfo_entry = &current_functionInfo[*function_info_ID];
    functionInfo_entry++;

    if (functionInfo_entry >= (u16*) function_info_ID)
        return;

    entry_to_clean = functionInfo_entry + 1;
    (*functionInfo_entry)--; // Unneeded

    for (*functionInfo_entry = function; entry_to_clean < (u16*) function_info_ID;
         entry_to_clean++) {
        *entry_to_clean = 0;
    }
}
