#ifndef OBJECT_H
#define OBJECT_H

#include "cv64.h"
#include "object_ID.h"

#define OBJECT_SIZE        0x74
#define OBJECT_HEADER_SIZE 0x20

// clang-format off
typedef enum cv64_obj_exec_flag {
    PAUSE = CV64_BIT(14),
    TOP   = CV64_BIT(15)
} cv64_obj_exec_flag_t;
// clang-format on

typedef struct cv64_obj_func_inf {
    u8 timer;          // Could also be "number of accesses to function"
    u8 function;       // ID within the functions array
} cv64_obj_func_inf_t; // Size = 0x2

typedef struct cv64_obj_hdr {
    s16 ID;
    s16 flags;
    s16 field_0x04;
    s16 field_0x06;
    cv64_obj_func_inf_t current_function[3];
    s16 functionInfo_ID;
    void (*destroy)(void*); // Officially called "OBJ_destruct"
    struct cv64_obj_hdr_t* parent;
    struct cv64_obj_hdr_t* next;
    struct cv64_obj_hdr_t* child;
} cv64_obj_hdr_t; // Size = 0x20

extern void* object_create(void* parent, object_t ID);
extern void* object_createAndSetChild(void* parent, object_t ID);
extern void
object_curLevel_goToNextFuncAndClearTimer(u16 current_functionInfo[],
                                          s16* functionInfo_ID);
extern void object_curLevel_goToFunc(u16 current_functionInfo[],
                                     s16* functionInfo_ID, s32 function);
extern void object_allocEntryInList(cv64_obj_hdr_t* object,
                                    s32 allocatedBlockInfo_index, u32 size,
                                    u32 ptrs_array_index);
extern void* object_allocEntryInListAndClear(cv64_obj_hdr_t* object,
                                             s32 allocatedBlockInfo_index,
                                             u32 size, u32 ptrs_array_index);
extern void* objectList_findFirstObjectByID(u16 ID);
extern void clearAllObjects();
extern void func_8000E860(cv64_obj_hdr_t* self);

// Mostly used inside entrypoint functions
// Commas at the end of statements needed for matching
#define ENTER(self, functions_array)                                           \
    s16 funcID;                                                                \
    funcID = self->header.functionInfo_ID + 1;                                 \
    self->header.functionInfo_ID = funcID,                                     \
    self->header.current_function[funcID].timer++;                             \
    functions_array[self->header.current_function[funcID].function](self);     \
    self->header.functionInfo_ID--;

// module_func_info_t* curFunc;
// void (*ptr_object_curLevel_goToFunc)(u16[], s16*, s32) =
// object_curLevel_goToFunc;
#define GO_TO_FUNC(self, functions_array, curFunc, object_curLevel_goToFunc,   \
                   function_array_ID)                                          \
    object_curLevel_goToFunc(self->header.current_function,                    \
                             &self->header.functionInfo_ID,                    \
                             function_array_ID);                               \
    curFunc = &self->header.current_function[self->header.functionInfo_ID];    \
    curFunc->timer++, functions_array[curFunc->function](self);

// module_func_info_t* curFunc;
// void (*ptr_object_curLevel_goToNextFuncAndClearTimer)(u16[], s16*) =
// object_curLevel_goToNextFuncAndClearTimer;
#define GO_TO_NEXT_FUNC(self, functions_array, curFunc,                        \
                        object_curLevel_goToNextFuncAndClearTimer)             \
    object_curLevel_goToNextFuncAndClearTimer(self->header.current_function,   \
                                              &self->header.functionInfo_ID);  \
    curFunc = &self->header.current_function[self->header.functionInfo_ID];    \
    curFunc->timer++, functions_array[curFunc->function](self);

#endif // OBJECT_H
