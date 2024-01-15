#include "object.h"
#include "cv64.h"
#include "objects/engine/GameStateMgr.h"
#include "objects/engine/object_0003.h"

// Checks if the object is allocated inside `objects_array`
// Return type needs to be `int` specifically to match (NOT `s32`)
int object_isValid(cv64_object_hdr_t* self) {
    return ((u32) self >= (u32) ARRAY_START(objects_array)) &&
           ((u32) self < (u32) ARRAY_END(objects_array));
}

#pragma GLOBAL_ASM("../asm/nonmatchings/object/object_free.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/clearAllObjects.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/object_allocate.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/updateObjectListFreeSlot.s")

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
                // last one is reached Then put the new one in there.
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
    if ((u32) current_object < (u32) object_list_free_space) {
        while (TRUE) {
            if (ID == (current_object->header.ID & 0x7FF)) {
                return current_object;
            }
            current_object++;
            if ((u32) object_list_free_space <= (u32) current_object) {
                break;
            }
        }
    }
    return NULL;
}

// clang-format off
#pragma GLOBAL_ASM("../asm/nonmatchings/object/objectList_findFirstObjectByID.s")
// clang-format on

// clang-format off
#pragma GLOBAL_ASM("../asm/nonmatchings/object/object_findObjectBetweenIDRange.s")
// clang-format on

// clang-format off
#pragma GLOBAL_ASM("../asm/nonmatchings/object/objectList_findObjectBetweenRange.s")
// clang-format on

#pragma GLOBAL_ASM("../asm/nonmatchings/object/object_findObjectByIDAndType.s")

// clang-format off
#pragma GLOBAL_ASM("../asm/nonmatchings/object/objectList_findObjectByIDAndType.s")
// clang-format on

#pragma GLOBAL_ASM("../asm/nonmatchings/object/func_80001BE4_27E4.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/func_80001CA0_28A0.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/func_80001DD4_29D4.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/func_80001EB4_2AB4.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/findNextMapObjectInstance.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/findFirstMapObjectInstance.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/func_8000211C_2D1C.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/object_allocEntryInList.s")

// clang-format off
#pragma GLOBAL_ASM("../asm/nonmatchings/object/object_allocEntryInListAndClear.s")
// clang-format on

#pragma GLOBAL_ASM("../asm/nonmatchings/object/func_80002264_2E64.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/func_800022BC_2EBC.s")

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

void object_executeChildObject(cv64_object_hdr_t* self) {
    if (self != NULL) {
        do {
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
            self = self->next;
        } while (self != NULL);
    }
}

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

#pragma GLOBAL_ASM("../asm/nonmatchings/object/func_800026D8_32D8.s")

// clang-format off
#pragma GLOBAL_ASM("../asm/nonmatchings/object/object_destroyChildrenAndModelInfo.s")
// clang-format on

void GameStateMgr_destroy(GameStateMgr* self) {}

#pragma GLOBAL_ASM("../asm/nonmatchings/object/func_800027BC_33BC.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/object/func_8000287C_347C.s")
