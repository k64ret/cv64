#ifndef OBJECT_H
#define OBJECT_H

#include "gfx/figure.h"
#include "gfx/graphic_container.h"
#include "bit.h"
#include "memory.h"
#include "object_ID.h"

#define OBJECT_ARRAY_MAX 384
#define OBJECT_NUM_MAX   554

// clang-format off

typedef enum cv64_object_exec_flag {
    OBJ_EXEC_FLAG_DONT_DESTROY = 0x0010,
    OBJ_EXEC_FLAG_PAUSE        = 0x4000,
    OBJ_EXEC_FLAG_TOP          = 0x8000
} cv64_object_exec_flag_t;

// clang-format on

typedef union cv64_object_func_inf {
    struct {
        /**
         * Could also be number of accesses to function
         */
        u8 timer;
        /**
         * Function ID
         */
        u8 function;
    };
    u16 whole;
} cv64_object_func_inf_t; // Size = 0x2

typedef struct ObjectHeader {
    s16 ID;
    u16 flags;
    /**
     * Misc. timer whose purpose depends on the object
     */
    u16 timer;
    s16 field_0x06;
    cv64_object_func_inf_t current_function[3];
    s16 function_info_ID;
    /**
     * Real name: `OBJ_destruct`
     */
    void (*destroy)(void*);
    struct ObjectHeader* parent;
    struct ObjectHeader* next;
    struct ObjectHeader* child;
} ObjectHeader; // Size = 0x20

// Generic object struct
#define OBJ_NUM_FIGURES    4
#define OBJ_NUM_ALLOC_DATA 16

typedef struct Object {
    ObjectHeader header;
    /**
     * The following two variables are bitfields, where each bit represents
     * a non-NULL pointer (1) in `alloc_data`
     */
    u16 alloc_data_entries;        // Entries allocated with `heap_alloc`
    u16 graphic_container_entries; // Entries allocated with `GraphicContainer_Alloc`
    Figure* figures[OBJ_NUM_FIGURES];
    void* alloc_data[OBJ_NUM_ALLOC_DATA];
} Object; // Size = 0x74

#define OBJECT_SIZE        sizeof(Object)
#define OBJECT_HEADER_SIZE sizeof(ObjectHeader)

#define OBJECT_FILE_INFO_FLAG_NONE 0x00
#define OBJECT_FILE_INFO_FLAG_LAST 0x40

typedef struct cv64_object_file_info {
    /**
     * Can be either a pointer to another struct that holds the information,
     * or simply the NI file ID.
     *
     * The first byte is used as a "flag"
     */
    union {
        u32 addr;
        u32 file_ID;
    };
    u32 file_padding;
} cv64_object_file_info_t;

int object_isValid(ObjectHeader* self);
void object_free(Object* self);
void clearAllObjects();
ObjectHeader* object_allocate(ObjectID ID);
void updateObjectListFreeSlot();
ObjectHeader* object_create(ObjectHeader* parent, ObjectID ID);
ObjectHeader* object_createAndSetChild(ObjectHeader* parent, ObjectID ID);
Object* object_findFirstObjectByID(ObjectID ID, Object* current_object);
Object* objectList_findFirstObjectByID(ObjectID ID);
Object* object_findObjectBetweenIDRange(ObjectID min_ID, ObjectID max_ID, Object* current_object);
Object* objectList_findObjectBetweenRange(ObjectID min_ID, ObjectID max_ID);
Object* object_findObjectByIDAndType(ObjectID ID, Object* current_object);
Object* objectList_findObjectByIDAndType(ObjectID ID);
Object* func_8000211C_2D1C(s32 ID);
void* object_allocEntryInList(Object* self, HeapKind heap_kind, u32 size, s32 alloc_data_index);
void* object_allocEntryInListAndClear(
    Object* self, HeapKind heap_kind, u32 size, s32 alloc_data_index
);
void* object_allocGraphicContainerEntryInList(
    Object* self, u32 size, HeapKind heap_kind, s32 alloc_data_index
);
void object_freeData(Object* self, s32 alloc_data_index);
void object_executeChildObject(ObjectHeader* self);
void object_execute(ObjectHeader* self);
void func_800026D8_32D8(ObjectHeader* self);
void object_destroyChildrenAndModelInfo(ObjectHeader* self);
void object_curLevel_goToFunc(
    cv64_object_func_inf_t current_functionInfo[], s16* function_info_ID, s32 function
);
void object_curLevel_goToNextFunc(
    cv64_object_func_inf_t current_functionInfo[], s16* function_info_ID
);
void object_prevLevel_goToNextFunc(
    cv64_object_func_inf_t current_functionInfo[], s16* function_info_ID
);
void object_nextLevel_goToNextFunc(
    cv64_object_func_inf_t current_functionInfo[], s16* function_info_ID
);
void object_curLevel_goToNextFuncAndClearTimer(
    cv64_object_func_inf_t current_functionInfo[], s16* function_info_ID
);
void object_curLevel_goToPrevFunc(
    cv64_object_func_inf_t current_functionInfo[], s16* function_info_ID
);
void object_prevLevel_goToPrevFunc(
    cv64_object_func_inf_t current_functionInfo[], s16* function_info_ID
);
void object_nextLevel_goToPrevFunc(
    cv64_object_func_inf_t current_functionInfo[], s16* function_info_ID
);
void object_curLevel_goToPrevFuncAndClearTimer(
    cv64_object_func_inf_t current_functionInfo[], s16* function_info_ID
);
void object_curLevel_goToFunc(
    cv64_object_func_inf_t current_functionInfo[], s16* function_info_ID, s32 function
);
void object_curLevel_goToFuncInLevel(
    cv64_object_func_inf_t current_functionInfo[], s16* function_info_ID, s16 level, s32 function
);
void object_prevLevel_goToFunc(
    cv64_object_func_inf_t current_functionInfo[], s16* function_info_ID, s32 function
);
void object_nextLevel_goToFunc(
    cv64_object_func_inf_t current_functionInfo[], s16* function_info_ID, s32 function
);
void object_doNothing(Object* self);
void object_goToNextFuncNoCondition(Object* self);
void object_goToNextFuncIfTimerIsTwo(Object* self);
void object_goToNextFuncIfTimerIsThree(Object* self);
void object_fadeOutNineFramesAndGoToNextFunc(Object* self);
void object_fadeOutFifteenFramesAndGoToNextFunc(Object* self);
void object_fadeOutTwentyOneFramesAndGoToNextFunc(Object* self);
void object_fadeOutThirtyFramesAndGoToNextFunc(Object* self);
void object_fadeOutFortyFiveFramesAndGoToNextFunc(Object* self);
void object_fadeOutSixtyFramesAndGoToNextFunc(Object* self);
void object_goToNextFuncIfNotFading(Object* self);
void func_80002570_3170(ObjectHeader* self);
Object* func_80001BE4_27E4(ObjectID object_ID, Object* arg1);
extern void mapOverlay(ObjectHeader* self);
extern void unmapOverlay();
void* allocStructInObjectEntryList(
    const char* name, Object* object, u32 size, s32 alloc_data_index
);
GraphicContainerHeader* allocGraphicContainerInObjectEntryList(
    const char* name, Object* object, u32 size, s32 alloc_data_index
);

extern Object objects_array[OBJECT_ARRAY_MAX];
extern u16 objects_number_of_instances_per_object[OBJECT_NUM_MAX];
extern cv64_object_file_info_t* objects_file_info[OBJECT_NUM_MAX];

typedef void (*cv64_object_func_t)(ObjectHeader* self);

extern cv64_object_func_t Objects_functions[OBJECT_NUM_MAX];
extern Object* object_list_free_slot;
extern Object* ptr_gameplayParentObject;

// Mostly used inside entrypoint functions
// Commas at the end of statements needed for matching
#define ENTER(self, functions_array)                                                               \
    {                                                                                              \
        s16 funcID;                                                                                \
        funcID                        = self->header.function_info_ID + 1;                         \
        self->header.function_info_ID = funcID, self->header.current_function[funcID].timer++;     \
        functions_array[self->header.current_function[funcID].function](self);                     \
        self->header.function_info_ID--;                                                           \
    }

// Goes to the next function in the array the moment after the function ID is changed
// (so it doesn't wait for the next frame to execute the function)
#define GO_TO_NEXT_FUNC_NOW(self, functions_array)                                                 \
    {                                                                                              \
        cv64_object_func_inf_t* curFunc;                                                           \
        (*object_curLevel_goToNextFuncAndClearTimer)(                                              \
            self->header.current_function, &self->header.function_info_ID                          \
        );                                                                                         \
        curFunc = &self->header.current_function[self->header.function_info_ID];                   \
        curFunc->timer++, functions_array[curFunc->function](self);                                \
    }

// Goes to a given function in the array the moment after the function ID is changed
// (so it doesn't wait for the next frame to execute the function)
#define GO_TO_FUNC_NOW(self, functions_array, function_array_ID)                                   \
    {                                                                                              \
        cv64_object_func_inf_t* curFunc;                                                           \
        (*object_curLevel_goToFunc)(                                                               \
            self->header.current_function, &self->header.function_info_ID, function_array_ID       \
        );                                                                                         \
        curFunc = &self->header.current_function[self->header.function_info_ID];                   \
        curFunc->timer++, functions_array[curFunc->function](self);                                \
    }

#endif // OBJECT_H
