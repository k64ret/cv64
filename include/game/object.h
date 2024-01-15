#ifndef OBJECT_H
#define OBJECT_H

#include "cv64.h"
#include "object_ID.h"

#define OBJECT_SIZE        0x74
#define OBJECT_HEADER_SIZE 0x20
#define OBJECT_ARRAY_MAX   384
#define OBJECT_NUM_MAX     554

// clang-format off
typedef enum cv64_object_exec_flag {
    OBJ_EXEC_FLAG_DONT_DESTROY = 0x0010,
    OBJ_EXEC_FLAG_PAUSE = 0x4000,
    OBJ_EXEC_FLAG_TOP   = 0x8000
} cv64_object_exec_flag_t;
// clang-format on

typedef union cv64_object_func_inf {
    struct {
        u8 timer;    // Could also be number of accesses to function
        u8 function; // Function ID
    };
    u16 whole;
} cv64_object_func_inf_t; // Size = 0x2

typedef struct cv64_object_hdr_t {
    s16 ID;
    u16 flags;
    s16 timer; // Misc. timer whose purpose depends on the object
    s16 field_0x06;
    cv64_object_func_inf_t current_function[3];
    s16 functionInfo_ID;
    void (*destroy)(void*); // Officially called "OBJ_destruct"
    struct cv64_object_hdr_t* parent;
    struct cv64_object_hdr_t* next;
    struct cv64_object_hdr_t* child;
} cv64_object_hdr_t; // Size = 0x20

// Generic object struct
typedef struct cv64_object {
    cv64_object_hdr_t header;
    u8 field_0x20[OBJECT_SIZE - OBJECT_HEADER_SIZE];
} cv64_object_t; // Size = 0x74

#define OBJECT_FILE_INFO_FLAG_NONE 0x00
#define OBJECT_FILE_INFO_FLAG_LAST 0x40

typedef struct cv64_object_file_info {
    // Can be either a pointer to another struct that holds the information, or
    // simply the file ID The first byte is used as a "flag"
    u32 addr_or_file_ID;
    u32 file_padding;
} cv64_object_file_info_t;

extern cv64_object_hdr_t* object_allocate(s32 ID);
cv64_object_hdr_t* object_create(cv64_object_hdr_t* parent,
                                 cv64_object_id_t ID);
cv64_object_hdr_t* object_createAndSetChild(cv64_object_hdr_t* parent,
                                            cv64_object_id_t ID);
cv64_object_t* object_findFirstObjectByID(cv64_object_id_t ID,
                                          cv64_object_t* current_object);
void object_execute(cv64_object_hdr_t* self);
void object_executeChildObject(cv64_object_hdr_t* self);
extern void object_curLevel_goToFunc(u16 current_functionInfo[],
                                     s16* functionInfo_ID, s32 function);
extern void object_allocEntryInList(cv64_object_hdr_t* object,
                                    s32 allocatedBlockInfo_index, u32 size,
                                    u32 ptrs_array_index);
extern void* object_allocEntryInListAndClear(cv64_object_hdr_t* object,
                                             s32 allocatedBlockInfo_index,
                                             u32 size, u32 ptrs_array_index);
extern void* objectList_findFirstObjectByID(u16 ID);
void object_curLevel_goToNextFunc(u16 current_functionInfo[],
                                  s16* functionInfo_ID);
void object_prevLevel_goToNextFunc(u16 current_functionInfo[],
                                   s16* functionInfo_ID);
void object_nextLevel_goToNextFunc(u16 current_functionInfo[],
                                   s16* functionInfo_ID);
void object_curLevel_goToNextFuncAndClearTimer(
    cv64_object_func_inf_t current_functionInfo[], s16* functionInfo_ID);
void object_curLevel_goToPrevFunc(cv64_object_func_inf_t current_functionInfo[],
                                  s16* functionInfo_ID);
void object_prevLevel_goToPrevFunc(u16 current_functionInfo[],
                                   s16* functionInfo_ID);
void object_nextLevel_goToPrevFunc(u16 current_functionInfo[],
                                   s16* functionInfo_ID);
void object_curLevel_goToPrevFuncAndClearTimer(u16 current_functionInfo[],
                                               s16* functionInfo_ID);
void object_curLevel_goToFunc(u16 current_functionInfo[], s16* functionInfo_ID,
                              s32 function);
void object_curLevel_goToFuncInLevel(u16 current_functionInfo[],
                                     s16* functionInfo_ID, s16 level,
                                     s32 function);
void object_prevLevel_goToFunc(u16 current_functionInfo[], s16* functionInfo_ID,
                               s32 function);
void object_nextLevel_goToFunc(u16 current_functionInfo[], s16* functionInfo_ID,
                               s32 function);
extern void clearAllObjects();
extern void func_8000E860(cv64_object_hdr_t* self);
extern void object_destroyChildrenAndModelInfo(cv64_object_hdr_t* self);
int object_isValid(cv64_object_hdr_t* self);
extern void mapOverlay(cv64_object_hdr_t* self);
extern void unmapOverlay();

extern cv64_object_t objects_array[OBJECT_ARRAY_MAX];
extern u16 objects_number_of_instances_per_object[OBJECT_NUM_MAX];
extern cv64_object_file_info_t* objects_file_info[OBJECT_NUM_MAX];
extern void (*Objects_functions[OBJECT_NUM_MAX])(cv64_object_hdr_t* self);
extern cv64_object_t* object_list_free_space;

// Mostly used inside entrypoint functions
// Commas at the end of statements needed for matching
#define ENTER(self, functions_array)                                           \
    s16 funcID;                                                                \
    funcID = self->header.functionInfo_ID + 1;                                 \
    self->header.functionInfo_ID = funcID,                                     \
    self->header.current_function[funcID].timer++;                             \
    functions_array[self->header.current_function[funcID].function](self);     \
    self->header.functionInfo_ID--;

// cv64_object_func_inf_t* curFunc;
#define GO_TO_FUNC(self, functions_array, curFunc, object_curLevel_goToFunc,   \
                   function_array_ID)                                          \
    (*object_curLevel_goToFunc)(self->header.current_function,                 \
                                &self->header.functionInfo_ID,                 \
                                function_array_ID);                            \
    curFunc = &self->header.current_function[self->header.functionInfo_ID];    \
    curFunc->timer++, functions_array[curFunc->function](self);

// cv64_object_func_inf_t* curFunc;
#define GO_TO_NEXT_FUNC(self, functions_array, curFunc,                        \
                        object_curLevel_goToNextFuncAndClearTimer)             \
    (*object_curLevel_goToNextFuncAndClearTimer)(                              \
        self->header.current_function, &self->header.functionInfo_ID);         \
    curFunc = &self->header.current_function[self->header.functionInfo_ID];    \
    curFunc->timer++, functions_array[curFunc->function](self);

#endif // OBJECT_H
