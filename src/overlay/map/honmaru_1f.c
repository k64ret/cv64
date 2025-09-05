/**
 * @file honmaru_1f.c
 *
 * Contains the code for objects exclusive to HONMARU 1F
 * (Castle Center - Bottom Elevator room)
 *
 * - Elevator: The elevator that takes the player to the top elevator room.
 * - ElevatorDoor: The door leading to the elevator
 * - BleedingStatue: The statue that starts bleeding when first entering the room.
 * - BleedingStatueBlood: The blood tears from the bleeding statue.
 * - BleedingStatueBloodSpot: The blood spot on the floor in front of the bleeding statue.
 * - ElevatorSwitchEffectSpawner: Handles spawning the flash effect seen in the elevator switch.
 */

#include "objects/map/honmaru_1f/elevator.h"
#include "objects/map/honmaru_1f/elevator_door.h"
#include "objects/map/honmaru_1f/bleeding_statue.h"
#include "objects/map/honmaru_1f/elevator_switch_effect_spawner.h"
#include "event_flags.h"
#include "sound.h"
#include "system_work.h"

// clang-format off

Vec3f Elevator1F_BoundingBox[2] = {
    {-15.0f, -0.0f, -15.0f},
    {15.0f, 30.0f, 15.0f}
};

ElevatorFunc Elevator1F_functions[] = {
    Elevator1F_Init,
    Elevator1F_Main
};

ElevatorFunc Elevator1F_main_functions[] = {
    Elevator1F_Main_BottomIdleOutsideElevator,
    Elevator1F_Main_Ascending,
    Elevator1F_Main_TopIdle,
    Elevator1F_Main_Descending,
    Elevator1F_Main_BottomIdleInsideElevator
};

ElevatorDoorFunc ElevatorDoor_functions[] = {
    ElevatorDoor_Init,
    ElevatorDoor_Main
};

ElevatorDoorFunc ElevatorDoor_main_functions[] = {
    ElevatorDoor_Main_DeactivatedClosed,
    ElevatorDoor_Main_Opening,
    ElevatorDoor_Main_IsPlayerOutOfElevator,
    ElevatorDoor_Main_Opened,
    ElevatorDoor_Main_Closing,
    ElevatorDoor_Main_Closed
};

BleedingStatueFunc BleedingStatue_functions[] = {
    BleedingStatue_Init,
    BleedingStatue_Main
};

BleedingStatueFunc BleedingStatue_main_functions[] = {
    BleedingStatue_Main_Idle,
    BleedingStatue_Main_InCutscene,
    BleedingStatue_Main_AfterCutscene
};

// clang-format on

void Elevator1F_Entrypoint(Elevator* self) {
    ENTER(self, Elevator1F_functions);
}

void Elevator1F_Init(Elevator* self) {
    ElevatorInner* inner = &self->inner;
    s32 temp;
    Model* model;

    self->model = (*Model_createAndSetChild)(FIG_TYPE_STANDALONE, map_lights[0]);
    model       = self->model;
    if (model) {
    }
    (*Actor_SetPosAndAngle)(self, model);
    model->assets_file = MAP_ASSETS_FILE_ID;
    model->dlist       = (u32) &HONMARU_1F_ELEVATOR_DL;
    BITS_SET(model->flags, FIG_FLAG_APPLY_FOG_COLOR | FIG_FLAG_APPLY_PRIMITIVE_COLOR);
    model->primitive_color.integer = sys.primitive_color.integer;
    model->fog_color.integer       = sys.background_color.integer;
    BITS_SET(self->header.ID, OBJ_FLAG_ENABLE_COLLISION | OBJ_FLAG_MOVE_ALONGSIDE_COLLISION);

    model->map_actor_model    = (*getMapActorModelEntryFromArray)(model->dlist, model->assets_file);
    self->map_actor_model     = model->map_actor_model;
    self->move_actor_function = Elevator1F_MoveActor;

    self->field_0x6C              = 0;
    inner->player_inside_elevator = FALSE;
    inner->initial_height         = model->position.y;
    Model_copyPosToVec3f(model, &inner->moving_endpoint);

    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );

    /*
    * Make the elevator descend when entering from the top elevator room.
    *
    * Otherwise display the elevator already at the bottom.
    */
    if (sys.SaveStruct_gameplay.spawn == 2) {
        (*play_sound)(SD_ELEVATOR_MOVING);
        inner->height = 20.0f;
        inner->speed  = 0.5f;
        (*object_nextLevel_goToFunc)(
            self->header.current_function, &self->header.function_info_ID, ELEVATOR_MAIN_DESCENDING
        );
    } else {
        BITS_SET(map_misc_event_flags, HONMARU_1F_FLAG_PLAYER_IS_OUTSIDE_ELEVATOR);
        inner->speed  = 0.0f;
        inner->height = 0.0f;
    }

    model->position.y = inner->initial_height + inner->height;
}

void Elevator1F_Main(Elevator* self) {
    ElevatorInner* inner = &self->inner;
    Model* model         = self->model;

    model->primitive_color.integer = sys.primitive_color.integer;
    model->fog_color.integer       = sys.background_color.integer;
    (*Model_copyPosToVec3f)(model, &inner->moving_endpoint);

    if ((*actor_playerOutsideActorSpawnRadius)(
            (Actor*) self, model->position.x, model->position.y, model->position.z
        )) {
        self->header.destroy(self);
        return;
    }

    inner->player_inside_elevator =
        Elevator1F_IsPlayerInsideElevator(model, Elevator1F_BoundingBox);
    if (inner->player_inside_elevator == TRUE) {
        BITS_SET(map_misc_event_flags, HONMARU_1F_FLAG_PLAYER_IS_INSIDE_ELEVATOR);
    } else {
        BITS_UNSET(map_misc_event_flags, HONMARU_1F_FLAG_PLAYER_IS_INSIDE_ELEVATOR);
    }

    ENTER(self, Elevator1F_main_functions);
    model->position.y = inner->initial_height + inner->height;
}

void Elevator1F_Main_BottomIdleOutsideElevator(Elevator* self) {
    ElevatorInner* inner = &self->inner;
    s32 temp;

    if (!BITS_HAS(map_misc_event_flags, 2)) {
        return;
    }

    if (inner->player_inside_elevator == TRUE) {
        (*play_sound)(SD_ELEVATOR_ACTIVATE);
        (*play_sound)(SD_ELEVATOR_MOVING);
        BITS_UNSET(map_misc_event_flags, HONMARU_1F_FLAG_ELEVATOR_IS_AT_THE_BOTTOM);
        inner->speed = 0.0f;
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void Elevator1F_Main_Ascending(Elevator* self) {
    ElevatorInner* inner = &self->inner;
    s32 temp;

    if (inner->speed < 0.5) {
        inner->speed += 0.008333333333333333;
    }

    inner->height += inner->speed;
    if (inner->height > 50.0) {
        (*play_sound)(SD_ELEVATOR_ACTIVATE);
        (*play_sound)(STOP_SOUND(SD_ELEVATOR_MOVING));
        inner->top_idle_time = 60;
        inner->speed         = 0.0f;
        inner->height        = 50.0f;
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void Elevator1F_Main_TopIdle(Elevator* self) {
    ElevatorInner* inner = &self->inner;

    inner->top_idle_time--;
    if (self->inner.top_idle_time < 0) {
        (*play_sound)(SD_ELEVATOR_ACTIVATE);
        (*play_sound)(SD_ELEVATOR_MOVING);
        inner->speed = 0.0f;
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void Elevator1F_Main_Descending(Elevator* self) {
    ElevatorInner* inner = &self->inner;

    if (inner->speed < 0.5) {
        inner->speed += 0.008333333333333333;
    }

    inner->height -= inner->speed;
    if (inner->height < 0.0) {
        (*play_sound)(SD_ELEVATOR_ACTIVATE);
        (*play_sound)(STOP_SOUND(SD_ELEVATOR_MOVING));
        BITS_SET(map_misc_event_flags, HONMARU_1F_FLAG_ELEVATOR_IS_AT_THE_BOTTOM);
        inner->speed  = 0.0f;
        inner->height = 0.0f;
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void Elevator1F_Main_BottomIdleInsideElevator(Elevator* self) {
    ElevatorInner* inner = &self->inner;

    if (inner->player_inside_elevator == FALSE) {
        BITS_SET(map_misc_event_flags, HONMARU_1F_FLAG_PLAYER_IS_OUTSIDE_ELEVATOR);
        (*object_curLevel_goToFunc)(
            self->header.current_function,
            &self->header.function_info_ID,
            ELEVATOR_MAIN_BOTTOM_IDLE_OUTSIDE_ELEVATOR
        );
    }
}

s32 Elevator1F_MoveActor(Elevator* self, Model* actor_model) {
    ElevatorInner* inner = &self->inner;

    return (*Actor_moveActorUntilEndpoint)(self->model, actor_model, &inner->moving_endpoint);
}

s32 Elevator1F_IsPlayerInsideElevator(Model* model, Vec3f bounding_box[]) {
    Model* player_model = ptr_PlayerData->visualData.model;

    if (player_model->position.x < (bounding_box[0].x + model->position.x)) {
        return FALSE;
    }
    if ((bounding_box[1].x + model->position.x) < player_model->position.x) {
        return FALSE;
    }

    if (player_model->position.y < (bounding_box[0].y + model->position.y)) {
        return FALSE;
    }
    if ((bounding_box[1].y + model->position.y) < player_model->position.y) {
        return FALSE;
    }

    if (player_model->position.z < (bounding_box[0].z + model->position.z)) {
        return FALSE;
    }
    if ((bounding_box[1].z + model->position.z) < player_model->position.z) {
        return FALSE;
    }
    return TRUE;
}

void ElevatorDoor_Entrypoint(ElevatorDoor* self) {
    ENTER(self, ElevatorDoor_functions);
}

// https://decomp.me/scratch/HQsfY
#ifdef NON_MATCHING
void ElevatorDoor_Init(ElevatorDoor* self) {
    ElevatorDoorInner* inner = &self->inner;
    Model* model;
    atari_base_work* atari_base;
    atari_data_work* collider;
    s32 i;
    s32 temp;

    self->model = (*Model_createAndSetChild)(FIG_TYPE_STANDALONE, map_lights[0]);
    model       = self->model;
    if (model) {
    }
    (*Actor_SetPosAndAngle)(self, model);
    model->assets_file = MAP_ASSETS_FILE_ID;
    model->dlist       = (u32) &HONMARU_1F_ELEVATOR_DOOR_DL;
    BITS_SET(model->flags, FIG_FLAG_APPLY_FOG_COLOR | FIG_FLAG_APPLY_PRIMITIVE_COLOR);
    model->primitive_color.integer = sys.primitive_color.integer;
    model->fog_color.integer       = sys.background_color.integer;
    BITS_SET(self->header.ID, OBJ_FLAG_ENABLE_COLLISION);

    model->map_actor_model = (*getMapActorModelEntryFromArray)(model->dlist, model->assets_file);
    self->map_actor_model  = model->map_actor_model;

    inner->atari_base = (*atariBaseWork_create)(model);
    atari_base        = inner->atari_base;

    if (atari_base != NULL) {
        BITS_UNSET(atari_base->field_0x0A, (0x0400 | 0x0200));
        BITS_SET(atari_base->field_0x0A, 0x0400);
        BITS_UNSET(atari_base->field_0x0A, (0x0002 | 0x0001));
        BITS_SET(atari_base->field_0x0A, (0x0002 | 0x0001));

        for (i = 0; i < 3; i++) {
            collider = (*atariDataWork_create)(model, 1);
            (*atariBaseWork_attachCollider)(atari_base, collider, 8);
            collider->direction.pitch = 0;
            collider->direction.yaw   = 0;
            collider->direction.roll  = 0;
            collider->center_point.x  = 0.0f;
            collider->center_point.y  = 0.0f;
            collider->center_point.z  = (((f32) i) * -25.0) + -25.0;
            collider->size.x          = 25.0f;
            collider->size.y          = 270.0f;
        }

        BITS_UNSET(inner->atari_base->flags, ATARI_WORK_ENABLE_PUSH_BACK_FORCE);
        inner->obj_destroy_function = self->header.destroy;
        self->header.destroy        = ElevatorDoor_Destroy;
    }

    self->field_0x6C = 0;

    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );

    if (sys.SaveStruct_gameplay.spawn == 2) {
        (*object_nextLevel_goToFunc)(
            self->header.current_function, &self->header.function_info_ID, ELEVATOR_DOOR_MAIN_CLOSED
        );
    }
}
#else
    #pragma GLOBAL_ASM("../asm/nonmatchings/overlay/map/honmaru_1f/ElevatorDoor_Init.s")
#endif

void ElevatorDoor_Main(ElevatorDoor* self) {
    ElevatorDoorInner* inner = &self->inner;
    Model* model             = self->model;

    if ((*actor_playerOutsideActorSpawnRadius)(
            (Actor*) self, model->position.x, model->position.y, model->position.z
        )) {
        self->header.destroy(self);
        return;
    }

    model->primitive_color.integer = sys.primitive_color.integer;
    model->fog_color.integer       = sys.background_color.integer;

    ENTER(self, ElevatorDoor_main_functions);

    if (BITS_HAS(map_misc_event_flags, HONMARU_1F_FLAG_PLAYER_IS_INSIDE_ELEVATOR)) {
        inner->player_inside_elevator = TRUE;
    } else {
        inner->player_inside_elevator = FALSE;
    }
}

void ElevatorDoor_Main_DeactivatedClosed(ElevatorDoor* self) {
    ElevatorDoorInner* inner = &self->inner;
    Model* model             = self->model;

    if (CHECK_EVENT_FLAGS(
            EVENT_FLAG_ID_CASTLE_CENTER_1F_2F, EVENT_FLAG_CASTLE_CENTER_1F_2F_ELEVATOR_ACTIVATED
        )) {
        BITS_UNSET(map_misc_event_flags, HONMARU_1F_FLAG_ELEVATOR_DOOR_IS_CLOSED);
        BITS_UNSET(self->header.ID, OBJ_FLAG_ENABLE_COLLISION);
        BITS_SET(inner->atari_base->flags, ATARI_WORK_ENABLE_PUSH_BACK_FORCE);
        inner->player_inside_elevator = FALSE;
        inner->slide_length           = 27.0f;
        inner->speed                  = 0.0f;

        (*play_sound_in_position)(SD_HONMARU_1F_DOOR_CLOSE, &model->position);
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void ElevatorDoor_Main_Opening(ElevatorDoor* self) {
    Model* model             = self->model;
    ElevatorDoorInner* inner = &self->inner;

    if (inner->speed < 0.9) {
        inner->speed += 0.03;
    }

    inner->slide_length -= inner->speed;
    if (inner->slide_length < 1.0) {
        BITS_UNSET(inner->atari_base->flags, ATARI_WORK_ENABLE_PUSH_BACK_FORCE);
        inner->field_0x10   = 60;
        inner->slide_length = 1.0f;
        inner->speed        = 0.0f;
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }

    model->size.z = (inner->slide_length / 27.0) / 10.0;
}

void ElevatorDoor_Main_IsPlayerOutOfElevator(ElevatorDoor* self) {
    if (BITS_HAS(map_misc_event_flags, HONMARU_1F_FLAG_PLAYER_IS_OUTSIDE_ELEVATOR)) {
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void ElevatorDoor_Main_Opened(ElevatorDoor* self) {
    ElevatorDoorInner* inner = &self->inner;
    Model* model             = self->model;

    if (inner->player_inside_elevator == TRUE) {
        (*play_sound_in_position)(SD_HONMARU_1F_DOOR_CLOSE, &model->position);
        BITS_SET(inner->atari_base->flags, ATARI_WORK_ENABLE_PUSH_BACK_FORCE);
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    }
}

void ElevatorDoor_Main_Closing(ElevatorDoor* self) {
    Model* model             = self->model;
    ElevatorDoorInner* inner = &self->inner;

    if (inner->speed < 0.9) {
        inner->speed += 0.03;
    }

    inner->slide_length += inner->speed;
    if (inner->slide_length > 27.0) {
        BITS_SET(self->header.ID, OBJ_FLAG_ENABLE_COLLISION);
        BITS_UNSET(inner->atari_base->flags, ATARI_WORK_ENABLE_PUSH_BACK_FORCE);
        inner->slide_length = 27.0f;
        inner->speed        = 0.0f;

        if (BITS_HAS(map_misc_event_flags, HONMARU_1F_FLAG_PLAYER_IS_INSIDE_ELEVATOR)) {
            BITS_SET(map_misc_event_flags, HONMARU_1F_FLAG_ELEVATOR_DOOR_IS_CLOSED);

            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.function_info_ID
            );
        } else {
            (*play_sound_in_position)(SD_HONMARU_1F_DOOR_CLOSE, &model->position);
            BITS_UNSET(map_misc_event_flags, HONMARU_1F_FLAG_ELEVATOR_DOOR_IS_CLOSED);
            BITS_UNSET(self->header.ID, OBJ_FLAG_ENABLE_COLLISION);
            BITS_SET(inner->atari_base->flags, ATARI_WORK_ENABLE_PUSH_BACK_FORCE);
            inner->slide_length = 27.0f;
            inner->speed        = 0.0f;

            (*object_curLevel_goToFunc)(
                self->header.current_function,
                &self->header.function_info_ID,
                ELEVATOR_DOOR_MAIN_OPENING
            );
        }
    }

    model->size.z = (inner->slide_length / 27.0) / 10.0;
}

void ElevatorDoor_Main_Closed(ElevatorDoor* self) {
    Model* model             = self->model;
    ElevatorDoorInner* inner = &self->inner;

    if (BITS_HAS(map_misc_event_flags, HONMARU_1F_FLAG_ELEVATOR_IS_AT_THE_BOTTOM)) {
        BITS_UNSET(map_misc_event_flags, HONMARU_1F_FLAG_ELEVATOR_DOOR_IS_CLOSED);
        BITS_UNSET(self->header.ID, OBJ_FLAG_ENABLE_COLLISION);
        BITS_SET(inner->atari_base->flags, ATARI_WORK_ENABLE_PUSH_BACK_FORCE);
        inner->slide_length = 27.0f;
        inner->speed        = 0.0f;
        (*play_sound_in_position)(SD_HONMARU_1F_DOOR_CLOSE, &model->position);

        (*object_curLevel_goToFunc)(
            self->header.current_function,
            &self->header.function_info_ID,
            ELEVATOR_DOOR_MAIN_OPENING
        );
    }
}

void ElevatorDoor_Destroy(ElevatorDoor* self) {
    ElevatorDoorInner* inner = &self->inner;

    (*atariWork_markForDeletion)(inner->atari_base);
    inner->obj_destroy_function(self);
}
