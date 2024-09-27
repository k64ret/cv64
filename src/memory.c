/**
 * @file memory.c
 *
 * Contains code that handles memory-related operations, including dynamically allocating data.
 *
 * It also has all the functions that tell an object to advance to certain functions in their respective
 * functions arrays.
 */

#include "memory.h"
#include "object.h"
#include "system_work.h"

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/memory_clear.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/memory_copy.s")

void heap_init(
    HeapKind kind, HeapBlockHeader* first_block_ptr, s32 heap_size, u32 additional_flags
) {
    heaps[kind].flags      = additional_flags | HEAP_ACTIVE;
    heaps[kind].size       = ALIGN8_BITWISE(heap_size);
    heaps[kind].heap_start = ALIGN8_BITWISE(first_block_ptr);
    first_block_ptr->flags = HEAP_BLOCK_FREE;
    first_block_ptr->size  = heaps[kind].size - sizeof(HeapBlockHeader);
}

void heap_free(HeapKind kind) {
    heaps[kind].flags = HEAP_INACTIVE;
}

void heap_writebackDCache(void) {
    Heap* first;
    Heap* current_heap;

    first = ARRAY_START(heaps), current_heap = &heaps[ARRAY_COUNT(heaps) - 1];

    do {
        if (BITS_HAS(current_heap->flags, HEAP_WRITE_BACK_CACHE_TO_RAM)) {
            osWritebackDCache(current_heap->heap_start, current_heap->size);
        }
        current_heap--;
    } while (first <= current_heap);
}

void initHeaps(void) {
    s32 i;

    // clang-format off
    for (i = ARRAY_COUNT(heaps) - 1; i > 0; i--) heaps[i].flags = HEAP_INACTIVE;
    // clang-format on

    heap_init(
        HEAP_KIND_MULTIPURPOSE,
        (HeapBlockHeader*) &HEAP_MULTIPURPOSE_START,
        HEAP_MULTIPURPOSE_SIZE,
        HEAP_WRITE_BACK_CACHE_TO_RAM
    );
}

void func_80000D68_1968(HeapKind arg0, u32 arg1) {}

s32 func_80000D74_1974(s32 arg0) {
    return 0;
}

void* heap_alloc(HeapKind kind, u32 size) {
    Heap* heap = &heaps[kind];
    HeapBlockHeader* curr_blk;
    HeapBlockHeader* second_blk;
    HeapBlockHeader* next_blk;
    HeapBlockHeader* new_blk;
    u32 curr_blk_sz;

    size = ALIGN8_ARITHMETIC(size);

    for (curr_blk  = heap->heap_start,
        second_blk = (HeapBlockHeader*) (heap->size + (u8*) heap->heap_start);
         curr_blk != second_blk;
         curr_blk =
             (HeapBlockHeader*) ((u8*) curr_blk + curr_blk->size + sizeof(HeapBlockHeader))) {
        if (curr_blk->flags == HEAP_BLOCK_FREE) {
            while (TRUE) {
                next_blk = curr_blk;
                if (next_blk->size) {
                }
                curr_blk_sz = next_blk->size;
                if (curr_blk_sz < size) {
                    next_blk =
                        (HeapBlockHeader*) ((u8*) next_blk + curr_blk_sz + sizeof(HeapBlockHeader));
                    if ((next_blk < second_blk) && (next_blk->flags == HEAP_BLOCK_FREE)) {
                        curr_blk->size += next_blk->size + sizeof(HeapBlockHeader);
                        continue;
                    }
                } else {
                    next_blk = NULL;
                }

                if (next_blk == NULL) {
                    next_blk = (HeapBlockHeader*) (curr_blk_sz - size - sizeof(HeapBlockHeader));
                    if ((s32) next_blk > 0) {
                        new_blk          = (HeapBlockHeader*) ((u8*) curr_blk + size);
                        new_blk[1].flags = HEAP_BLOCK_FREE;
                        new_blk[1].size  = (u32) next_blk;
                        curr_blk->size   = size;
                    }
                    curr_blk->flags = HEAP_BLOCK_ACTIVE;
                    return curr_blk + 1;
                }

                break;
            }
        }
    }

    return NULL;
}

#pragma GLOBAL_ASM("../asm/nonmatchings/memory/heap_allocWithAlignment.s")

s32 heapBlock_updateBlockMaxSize(void* data, u32 size) {
    HeapBlockHeader* current_block_header =
        (HeapBlockHeader*) (((s32) data) - sizeof(HeapBlockHeader));
    s32 current_block_size = current_block_header->size;
    s32 remaining_free_space;
    s32* current_block_size_ptr;
    HeapBlockHeader* next_block_header;

    current_block_size_ptr = &current_block_header->size;
    if (1) {
    }
    size = ALIGN8_ARITHMETIC(size);
    if ((*current_block_size_ptr) < size) {
        return -1;
    }
    remaining_free_space = (*current_block_size_ptr - size) - (sizeof(HeapBlockHeader));
    next_block_header    = (HeapBlockHeader*) (((s32) current_block_header) + size);
    if (remaining_free_space > 0) {
        next_block_header[1].flags = HEAP_BLOCK_FREE;
        next_block_header[1].size  = remaining_free_space;
        current_block_header->size = size;
        current_block_size         = size;
    }
    return current_block_size;
}

GraphicContainerHeader* GraphicContainer_Alloc(HeapKind heap_kind, u32 size) {
    u32 data;
    HeapBlockHeader* data_header;

    data = (u32) heap_alloc(heap_kind, size * NUM_GRAPHIC_BUFFERS);
    if (data == NULL) {
        return NULL;
    }

    data_header                                 = data - sizeof(HeapBlockHeader);
    data_header->graphic_container.data_ptrs[0] = data;
    BITS_SET(data_header->flags, HEAP_BLOCK_GRAPHIC_CONTAINER);
    data_header->graphic_container.data_ptrs[1] = data + size;
    data_header->graphic_container.field_0x00 =
        data_header->graphic_container.data_ptrs[sys.current_graphic_buffer];

    return &data_header->graphic_container;
}

void heapBlock_free(void* ptr) {
    HeapBlockHeader* temp = (HeapBlockHeader*) (((s32) ptr) - sizeof(HeapBlockHeader));
    temp->flags           = HEAP_BLOCK_FREE;
}

void GraphicContainer_Free(void* ptr) {
    u8* temp;

    /**
     * @bug `temp` is used before it's initialised.
     *      This works in practice because the stack allocated for `temp`
     *      happens to contain 0, which points to the proper address in its
     *      heap block header.
     */
    temp = temp + ((u8*) ptr - temp) - OFFSET_OF(HeapBlockHeader, graphic_container);
    ((HeapBlockHeader*) temp)->flags = HEAP_BLOCK_FREE;
}

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
