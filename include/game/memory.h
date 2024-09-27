#ifndef MEMORY_H
#define MEMORY_H

#include "gfx/graphic_container.h"

#define ALIGN8_BITWISE(val)    ((((u32) val) + 7) & ~7)
#define ALIGN8_ARITHMETIC(val) ((((u32) (val + 7)) / 8) * 8)

#define HEAP_MULTIPURPOSE_SIZE 0xD0000
/**
 * @bug Since the menu data heap is always set to start at 0x801CC000, setting
 *      it to a size of 0x40000 can theoretically overwrite `gFramebuffers`,
 *      causing graphical glitches and crashes with the elements that use said
 *      heap (such as the Pause menu).
 *
 *      The correct size should be 0x34000.
 */
#define HEAP_MENU_DATA_SIZE 0x40000

#define HEAP_NUM 8

typedef enum HeapKind {
    /**
     * Most dynamically-allocated data is allocated on this heap
     */
    HEAP_KIND_MULTIPURPOSE,
    HEAP_KIND_1,
    /**
     * Assets used on some menus (usually file `0x60` and `0x61`). Some
     * menu-related structs are also allocated on this heap.
     */
    HEAP_KIND_MENU_DATA,
    HEAP_KIND_3,
    HEAP_KIND_4,
    HEAP_KIND_5,
    HEAP_KIND_6,
    /**
     * Current map's data (assets file, collision data, etc)
     */
    HEAP_KIND_MAP_DATA
} HeapKind;

// clang-format off

typedef enum HeapBlockFlag {
    HEAP_BLOCK_FREE                = 0x0000,
    /**
     * The data allocated in this block is graphic-related
     * content, such as display list or vertex buffers, etc.
     */
    HEAP_BLOCK_GRAPHIC_CONTAINER   = 0x4000,
    HEAP_BLOCK_ACTIVE              = 0x8000
} HeapBlockFlag;

typedef enum HeapFlag {
    HEAP_INACTIVE                = 0x0000,
    HEAP_WRITE_BACK_CACHE_TO_RAM = 0x4000,
    HEAP_ACTIVE                  = 0x8000
} HeapFlag;

// clang-format on

typedef struct HeapBlockHeader {
    s16 flags;
    u8 field_0x02[2];
    /**
     * Size of the block
     */
    u32 size;
    GraphicContainerHeader graphic_container;
} HeapBlockHeader;

typedef struct Heap {
    s16 flags;
    u8 field_0x02[2];
    /**
     * Size of the heap
     */
    u32 size;
    /**
     * Start of the block array
     */
    HeapBlockHeader* heap_start;
} Heap;

extern Heap heaps[HEAP_NUM];
extern void* HEAP_MULTIPURPOSE_START;
extern void* HEAP_MENU_DATA_START;

extern void memory_copy(void* src, void* dest, u32 size);
extern void memory_clear(void* ptr, u32 length);
void heap_init(
    HeapKind kind, HeapBlockHeader* first_block_ptr, s32 heap_size, u32 additional_flags
);
void heap_free(HeapKind kind);
void heap_writebackDCache(void);
void initHeaps(void);
void* heap_alloc(HeapKind kind, u32 data_size);
extern void* heap_allocWithAlignment(HeapKind kind, u32 data_size, u32 alignment);
extern s32 heapBlock_updateBlockMaxSize(void* data, u32 size);
void heapBlock_free(void* ptr);
void* allocStruct(const char* name, u32 size);
void func_8013B4F0_BE6E0(void);
u32 isMenuDataHeapActive(void);
void func_80000D68_1968(HeapKind arg0, u32 arg1);

/**
 * `GraphicContainer` functions
 */
GraphicContainerHeader* GraphicContainer_Alloc(HeapKind heap_kind, u32 size);
GraphicContainerHeader* allocGraphicContainerStruct(const char* name, u32 size);
void GraphicContainer_Free(void* ptr);

#endif
