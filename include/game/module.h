#ifndef MODULE_H
#define MODULE_H

#include "c64.h"
#include "module_ID.h"

#define MODULE_SIZE        0x74
#define MODULE_HEADER_SIZE 0x20

// clang-format off
typedef enum module_exec_flag {
    PAUSE = C64_BIT(14),
    TOP   = C64_BIT(15)
} module_exec_flag_t;
// clang-format on

typedef struct {
    u8 timer;         // Could also be "number of accesses to function"
    u8 function;      // ID within the functions array
} module_func_info_t; // Size = 0x2

typedef struct {
    s16 ID;
    s16 flags;
    s16 field_0x04;
    s16 field_0x06;
    module_func_info_t current_function[3];
    s16 functionInfo_ID;
    void (*destroy)(void *); // Officially called "OBJ_destruct"
    struct module_header_t *parent;
    struct module_header_t *next;
    struct module_header_t *child;
} module_header_t; // Size = 0x20

extern void *module_create(void *parent, module_t ID);
extern void *module_createAndSetChild(void *parent, module_t ID);
extern void goToNextFunc(u16 current_functionInfo[], s16 *functionInfo_ID);
extern void goToFunc(u16 current_functionInfo[], s16 *functionInfo_ID,
                     s32 function);
extern void module_allocEntryInList(module_header_t *module,
                                    s32 allocatedBlockInfo_index, u32 size,
                                    u32 ptrs_array_index);
extern void *module_allocEntryInListAndClear(module_header_t *module,
                                             s32 allocatedBlockInfo_index,
                                             u32 size, u32 ptrs_array_index);
extern void *moduleList_findFirstModuleByID(u16 ID);
extern void clearAllModules();
extern void func_8000E860(module_header_t *self);

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
// void (*ptr_goToFunc)(u16[], s16*, s32) = goToFunc;
#define GO_TO_FUNC(self, functions_array, curFunc, goToFunc,                   \
                   function_array_ID)                                          \
    goToFunc(self->header.current_function, &self->header.functionInfo_ID,     \
             function_array_ID);                                               \
    curFunc = &self->header.current_function[self->header.functionInfo_ID];    \
    curFunc->timer++, functions_array[curFunc->function](self);

// module_func_info_t* curFunc;
// void (*ptr_goToNextFunc)(u16[], s16*) = goToNextFunc;
#define GO_TO_NEXT_FUNC(self, functions_array, curFunc, goToNextFunc)          \
    goToNextFunc(self->header.current_function,                                \
                 &self->header.functionInfo_ID);                               \
    curFunc = &self->header.current_function[self->header.functionInfo_ID];    \
    curFunc->timer++, functions_array[curFunc->function](self);

#endif // MODULE_H
