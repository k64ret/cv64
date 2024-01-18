#include "object.h"
#include "cv64.h"
#include "memory.h"
#include "objects/engine/GameStateMgr.h"
#include "objects/engine/object_0003.h"

// .bss
cv64_object_t* object_list_free_slot;
cv64_object_t* ptr_gameplayParentObject;

/**
 * Checks if the object is allocated inside `objects_array`.
 * Return type explicitly needs to be `int` to match (NOT `s32` typedef)
 */
int object_isValid(cv64_object_hdr_t* self) {
    return ((u32) self >= (u32) ARRAY_START(objects_array)) &&
           ((u32) self < (u32) ARRAY_END(objects_array));
}

/**
 * Removes the object's instance from `objects_array`, and frees
 * the object's pointer list (`alloc_data`).
 */
void object_free(cv64_object_t* self) {
    s32 i;
    s32 alloc_data_slot;
    figure* current_figure;
    figure** current_figure_ptr;

    for (i = 0, alloc_data_slot = 1; i < OBJ_NUM_ALLOC_DATA;
         alloc_data_slot = alloc_data_slot << 1, i++) {
        if (self->field_0x20 & alloc_data_slot) {
            heapBlock_free(self->alloc_data[i]);
        }
        if (self->field_0x22 & alloc_data_slot) {
            func_80001080_1C80(self->alloc_data[i]);
        }
    }
    current_figure_ptr = &self->figures;
    for (i = OBJ_NUM_FIGURES - 1; i >= 0; current_figure_ptr++) {
        current_figure = *current_figure_ptr;
        i--;
        if (current_figure != NULL) {
            // Set the first 4 bytes of the figure to 0,
            // clearing the slot from `figures_array`
            *((u32*) current_figure) = 0;
        }
    }
    objects_number_of_instances_per_object[(self->header.ID & 0x7FF) - 1]--;
    self->header.ID = 0;
}

/**
 * Clears the whole `objects_array`
 */
void clearAllObjects() {
    u32 i;
    cv64_object_t* currentObject;

    // clang-format off
    for (i = 0; i < OBJECT_NUM_MAX; i++) objects_number_of_instances_per_object[i] = 0;
    // clang-format on

    for (currentObject = ARRAY_START(objects_array);
         currentObject < ARRAY_END(objects_array); currentObject++) {
        // Set the first 4 bytes of each object to 0
        *((u32*) currentObject) = 0;
    }
}

/**
 * Allocates an object's basic struct in `objects_array`
 */
cv64_object_hdr_t* object_allocate(cv64_object_id_t ID) {
    cv64_object_t* current_object;
    cv64_object_t* last;

    for (current_object = ARRAY_START(objects_array);
         current_object < ARRAY_END(objects_array); current_object++) {
        // If the object we're currently checking has ID = 0,
        // that means that it's free, so we can create our new object here
        if (current_object->header.ID == 0) {
            // Clear the object space by filling its memory space with 0
            memory_clear(current_object, sizeof(cv64_object_t));
            // Assign the ID for our new object
            current_object->header.ID = ID;
            // Update the "object_list_free_slot" pointer
            if (current_object >= object_list_free_slot) {
                object_list_free_slot = current_object + 1;
            }
            return (cv64_object_hdr_t*) current_object;
        }
    }
    return NULL;
}

/**
 * Updates the `objects_array` free space pointer
 */
void updateObjectListFreeSlot() {
    cv64_object_t* current;
    cv64_object_t* previous;

    for (current = ARRAY_END(objects_array), previous = current - 1;
         previous >= ARRAY_START(objects_array);) {
        if (previous->header.ID == 0) {
            current = previous--;
        } else {
            break;
        }
    }
    object_list_free_slot = current;
}

/**
 * Creates a new object and makes it so that
 * the new object is executed right after `parent`
 */
cv64_object_hdr_t* object_create(cv64_object_hdr_t* parent,
                                 cv64_object_id_t ID) {
    // Allocate the object in the objects array
    cv64_object_hdr_t* new_object = object_allocate(ID);

    if (new_object != NULL) {
        ID &= 0x7FF; // Grab the part of the "ID" field that contains the actual
                     // ID of the object
        if (objects_file_info[ID - 1] != NULL &&
            func_8000EE18(ptr_Object_0003, new_object) == -1) {
            return NULL;
        }
        new_object->functionInfo_ID = -1;
        if (parent != NULL) {
            new_object->parent = parent;
            new_object->next = parent->child;
            parent->child = new_object;
        }
        new_object->destroy = &object_destroyChildrenAndModelInfo;
        objects_number_of_instances_per_object[ID - 1]++;
    }
    return new_object;
}

/**
 * Creates a new object and makes it so that
 * the new object is executed after all the `parent`'s children
 * are executed beforehand.
 */
cv64_object_hdr_t* object_createAndSetChild(cv64_object_hdr_t* parent,
                                            cv64_object_id_t ID) {
    cv64_object_hdr_t* new_object;
    cv64_object_hdr_t* var_v0;
    cv64_object_hdr_t* var_v1;

    // Allocate the object in the objects array
    new_object = object_allocate(ID);

    if (new_object != NULL) {
        ID &= 0x7FF; // Grab the part of the "ID" field that contains the actual
                     // ID of the object
        if (objects_file_info[ID - 1] != NULL &&
            func_8000EE18(ptr_Object_0003, new_object) == -1) {
            return NULL;
        }
        new_object->functionInfo_ID = -1;
        if (parent != NULL) {
            new_object->parent = parent;
            if (parent->child != NULL) {
                var_v0 = parent->child->next;
                var_v1 = parent->child;
                // Traverse all the parent's child "next" pointers until the
                // last one is reached. Then put the new one in there.
                for (; var_v0 != NULL; var_v0 = var_v0->next) {
                    var_v1 = var_v0;
                }
                var_v1->next = new_object;
            } else {
                parent->child = new_object;
            }
        }
        new_object->destroy = &object_destroyChildrenAndModelInfo;
        objects_number_of_instances_per_object[ID - 1]++;
    }
    return new_object;
}

/**
 * Traverse the `objects_array`, starting from the `current_object`'s slot
 * and return the first instance of the object with the raw ID
 */
cv64_object_t* object_findFirstObjectByID(cv64_object_id_t ID,
                                          cv64_object_t* current_object) {
    // The first slot in the object array is always empty.
    // In that array, objects start at ID 1.
    current_object++;
    // The ID of the object actually consists of a flag variable (upper byte)
    // and the actual ID part (lower byte)
    // Only the ID part of it.
    ID &= 0x7FF;

    // Go through each object sequentially, and when the first object of a given
    // ID is found return a pointer to that object.
    for (; (u32) current_object < (u32) object_list_free_slot;
         current_object++) {
        if (ID == (current_object->header.ID & 0x07FF)) {
            return current_object;
        }
    }
    return NULL;
}

/**
 * Traverse the `objects_array`, starting from the first slot
 * and return the first instance of the object with the raw ID
 *
 * Starts at -1 because `object_findFirstObjectByID` adds it to +1
 * at the beginning of that function.
 */
cv64_object_t* objectList_findFirstObjectByID(s32 ID) {
    return object_findFirstObjectByID(ID, &objects_array[-1]);
}

/**
 * Traverse the `objects_array`, starting from the `current_object`'s slot
 * and return the first instance of the object whose raw ID is higher or equal
 * to `min_ID` or lower or equal to `max_ID`
 */
cv64_object_t* object_findObjectBetweenIDRange(s32 min_ID, s32 max_ID,
                                               cv64_object_t* current_object) {
    s32 current_obj_ID;

    min_ID &= 0x7FF;
    max_ID &= 0x7FF;
    current_object++;
    for (; (u32) current_object < (u32) object_list_free_slot;
         current_object++) {
        current_obj_ID = current_object->header.ID & 0x7FF;
        if ((current_obj_ID >= (min_ID)) && ((max_ID) >= current_obj_ID)) {
            return current_object;
        }
    }
    return NULL;
}

/**
 * Traverse the `objects_array`, starting from the first slot
 * and return the first instance of the object whose raw ID is higher or equal
 * to `min_ID` or lower or equal to `max_ID`
 *
 * Starts at -1 because `object_findFirstObjectByID` adds it to +1
 * at the beginning of that function.
 */
cv64_object_t* objectList_findObjectBetweenRange(s32 min_ID, s32 max_ID) {
    return object_findObjectBetweenIDRange(min_ID, max_ID, &objects_array[-1]);
}

/**
 * Traverse the `objects_array`, starting from the `current_object`'s slot
 * and return the first instance of the object where the ID passed has bits in
 * common with the object currently being read.
 */
cv64_object_t* object_findObjectByIDAndType(s32 ID,
                                            cv64_object_t* current_object) {
    current_object++;
    for (; (u32) current_object < (u32) object_list_free_slot;
         current_object++) {
        if (current_object->header.ID & ID) {
            return current_object;
        }
    }
    return NULL;
}

/**
 * Traverse the `objects_array`, starting from the first slot
 * and return the first instance of the object where the ID passed has bits in
 * common with the object currently being read.
 *
 * Starts at -1 because `object_findFirstObjectByID` adds it to +1
 * at the beginning of that function.
 */
cv64_object_t* objectList_findObjectByIDAndType(s32 ID) {
    return object_findObjectByIDAndType(ID, &objects_array[-1]);
}

#pragma GLOBAL_ASM("../asm/nonmatchings/object/func_80001BE4_27E4.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/func_80001CA0_28A0.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/func_80001DD4_29D4.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/func_80001EB4_2AB4.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/findNextMapObjectInstance.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/findFirstMapObjectInstance.s")

/**
 * This function either:
 *
 * - Returns the first occurence of an object in `objects_array` given its raw
 * ID.
 * - Returns the first occurence of a non-paused object in `objects_array` given
 * its raw ID, and whose code is mapped by the TLB.
 */
cv64_object_t* func_8000211C_2D1C(s32 ID) {
    cv64_object_t* var_v0;

    if (ID & OBJ_FLAG_MAP_OVERLAY) {
        ID &= 0x7FF;
        var_v0 = objectList_findFirstObjectByID(ID);
        if (var_v0 != NULL) {
            do {
                if (!(var_v0->header.flags & OBJ_EXEC_FLAG_PAUSE)) {
                    return var_v0;
                }
                var_v0 = object_findFirstObjectByID(ID, var_v0);
            } while (var_v0 != NULL);
        }
        return NULL;
    }
    return objectList_findFirstObjectByID(ID);
}

/**
 * Dynamically allocates arbitrary data, and keeps its pointer
 * in one of the object's pointer list (`alloc_data`).
 */
void* object_allocEntryInList(cv64_object_t* self, s32 heap_kind, u32 size,
                              s32 alloc_data_index) {
    self->field_0x20 |= (1 << alloc_data_index);
    self->alloc_data[alloc_data_index] = heap_alloc(heap_kind, size);
    return self->alloc_data[alloc_data_index];
}

/**
 * Dynamically allocates arbitrary data, and keeps its pointer
 * in one of the object's pointer list (`alloc_data`),
 * then clears the allocated data.
 */
void* object_allocEntryInListAndClear(cv64_object_t* self, s32 heap_kind,
                                      u32 size, s32 alloc_data_index) {
    self->field_0x20 |= (1 << alloc_data_index);
    self->alloc_data[alloc_data_index] = heap_alloc(heap_kind, size);
    memory_clear(self->alloc_data[alloc_data_index], size);
    return self->alloc_data[alloc_data_index];
}

void* func_80002264_2E64(cv64_object_t* self, u32 size, s32 heap_kind,
                         s32 alloc_data_index) {
    self->field_0x22 |= (1 << alloc_data_index);
    self->alloc_data[alloc_data_index] = func_80001008_1C08(size, heap_kind);
    return self->alloc_data[alloc_data_index];
}

/**
 * Frees data previously allocated inside
 * one of the object's pointer list (`alloc_data`).
 */
void func_800022BC_2EBC(cv64_object_t* self, s32 alloc_data_index) {
    if (self->field_0x20 & (1 << alloc_data_index)) {
        heapBlock_free(self->alloc_data[alloc_data_index]);
    }
    if (self->field_0x22 & (1 << alloc_data_index)) {
        func_80001080_1C80(self->alloc_data[alloc_data_index]);
    }
}

/**
 * Executes one frame of the object's code
 */
void GameStateMgr_execute(GameStateMgr* self) {
    if (self->ID > 0) {
        if (self->ID & OBJ_FLAG_MAP_OVERLAY) {
            if ((self->flags & OBJ_EXEC_FLAG_PAUSE) == FALSE) {
                mapOverlay(self);
                Objects_functions[(self->ID & 0x7FF) - 1](self);
                unmapOverlay(self);
            }
        } else if (!(self->flags & OBJ_EXEC_FLAG_PAUSE)) {
            Objects_functions[(self->ID & 0x7FF) - 1](self);
        }
    }
}

/**
 * Executes one frame of the object's and all of its children's code
 */
void object_executeChildObject(cv64_object_hdr_t* self) {
    for (; self != NULL; self = self->next) {
        // If a object is waiting to be deleted (i.e. if its ID = 8xxx or
        // Axxx (2xxx | 8xxx)) then don't execute it, nor its children
        if (self->ID > 0) {
            // If a object has an ID = 2xxx, then its code is meant to be
            // mapped somewhere by the TLB (usually 0x0F000000 or
            // 0x0E000000) before it's accessed
            if (self->ID & OBJ_FLAG_MAP_OVERLAY) {
                if ((self->flags & OBJ_EXEC_FLAG_PAUSE) == FALSE) {
                    mapOverlay(self);
                    Objects_functions[(self->ID & 0x7FF) - 1](self);
                    unmapOverlay(self);
                }
            } else if ((self->flags & OBJ_EXEC_FLAG_PAUSE) == FALSE) {
                Objects_functions[(self->ID & 0x7FF) - 1](self);
            }
            // Execute its child object
            if (self->child != NULL) {
                object_executeChildObject(self->child);
            }
        }
        // When there are no child objects left to execute,
        // go to the next object and execute it
        // until there are no more "next" objects left to execute
    }
}

/**
 * Executes one frame of the object's and its `child`'s code
 */
void object_execute(cv64_object_hdr_t* self) {
    // If a object is waiting to be deleted (i.e. if its ID = 8xxx or Axxx (2xxx
    // | 8xxx)) then don't execute it, nor its children
    if (self->ID > 0) {
        // If a object has an ID = 2xxx, then its code is meant to be mapped
        // somewhere by the TLB (usually 0x0F000000 or 0x0E000000) before it's
        // accessed
        if (self->ID & OBJ_FLAG_MAP_OVERLAY) {
            if ((self->flags & OBJ_EXEC_FLAG_PAUSE) == FALSE) {
                mapOverlay(self);
                Objects_functions[(self->ID & 0x7FF) - 1](self);
                unmapOverlay(self);
            }
        } else if ((self->flags & OBJ_EXEC_FLAG_PAUSE) == FALSE) {
            Objects_functions[(self->ID & 0x7FF) - 1](self);
        }
        if (self->child != NULL) {
            object_executeChildObject(self->child);
        }
    }
}

#pragma GLOBAL_ASM("../asm/nonmatchings/object/func_80002570_3170.s")

/**
 * Destroys the object and all of its children
 */
void func_800026D8_32D8(cv64_object_hdr_t* self) {
    cv64_object_hdr_t* temp_s0;
    cv64_object_hdr_t* temp_s1;

    temp_s0 = self->child;
    if (temp_s0 != NULL) {
        temp_s0->destroy(self->child);
        temp_s0 = temp_s0->next;
        if (temp_s0 != NULL) {
            do {
                temp_s1 = temp_s0->next;
                temp_s0->destroy(temp_s0);
                temp_s0 = temp_s1;
            } while (temp_s1 != NULL);
        }
    }
}

/**
 * Destroys the object and all of its children, as well
 * as some additional data, such as their associated models, if any.
 */
void object_destroyChildrenAndModelInfo(cv64_object_hdr_t* self) {
    cv64_object_hdr_t* temp_s0;
    cv64_object_hdr_t* temp_s1;

    temp_s0 = self->child;
    if (temp_s0 != NULL) {
        temp_s0->destroy(self->child);
        temp_s0 = temp_s0->next;
        if (temp_s0 != NULL) {
            do {
                temp_s1 = temp_s0->next;
                temp_s0->destroy(temp_s0);
                temp_s0 = temp_s1;
            } while (temp_s1 != NULL);
        }
    }
    func_80002570_3170(self);
}

/**
 * Object's generic destroy function. Only used by `GameStateMgr`.
 */
void GameStateMgr_destroy(GameStateMgr* self) {}

#pragma GLOBAL_ASM("../asm/nonmatchings/object/func_800027BC_33BC.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/func_8000287C_347C.s")
