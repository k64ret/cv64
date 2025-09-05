/**
 * @file honmaru_5f.c
 *
 * Contains the code for objects exclusive to HONMARU 5F
 * (Castle Center - Top Elevator room)
 *
 * - WoodenBridge: The bridge used to access either Duel Tower or Tower of Science.
 *
 * - Elevator: The elevator that takes the player back to the bottom elevator room.
 */

#include "objects/map/honmaru_5f/wooden_bridge.h"
#include "objects/map/honmaru_5f/elevator.h"
#include "event_flags.h"
#include "sound.h"
#include "system_work.h"

// clang-format off

Vec3f Elevator_BoundingBox[2] = {
    {-14.0f, -49.0f, -14.0f},
    {14.0f, -19.0f, 14.0f}
};

WoodenBridgeFunc WoodenBridge_functions[] = {
    WoodenBridge_Init,
    WoodenBridge_Loop
};

ElevatorFunc Elevator_functions[] = {
    Elevator_Init,
    Elevator_Main
};

ElevatorFunc Elevator_main_functions[] = {
    Elevator_Main_Ascending,
    Elevator_Main_TopIdleInsideElevator,
    Elevator_Main_TopIdleOutsideElevator,
    Elevator_Main_Descending,
    Elevator_Main_BottomIdle
};

// clang-format on

void WoodenBridge_Entrypoint(WoodenBridge* self) {
    ENTER(self, WoodenBridge_functions);
}

void WoodenBridge_Init(WoodenBridge* self) {
    ActorConfig* settings = self->settings;
    Model* model;

    model = (*Model_createAndSetChild)(FIG_TYPE_STANDALONE, map_lights[0]);
    if (model) {
    }
    self->model = model;
    (*Actor_SetPosAndAngle)(self, model);

    model->assets_file = MAP_ASSETS_FILE_ID;
    BITS_SET(
        model->flags, FIG_FLAG_APPLY_FOG_COLOR | FIG_FLAG_APPLY_PRIMITIVE_COLOR | FIG_FLAG_0080
    );

    model->primitive_color.integer = sys.primitive_color.integer;
    model->fog_color.integer       = sys.background_color.integer;

    // Only display the full bridge associated to the character we are currently.
    // Otherwise display the broken bridge.
    if (settings->variable_1 == sys.SaveStruct_gameplay.character) {
        model->dlist = (u32) &HONMARU_5F_WOODEN_BRIDGE_FULL;
    } else {
        model->dlist = (u32) &HONMARU_5F_WOODEN_BRIDGE_BROKEN;
    }

    BITS_SET(self->header.ID, OBJ_FLAG_ENABLE_COLLISION);
    model->map_actor_model = (*getMapActorModelEntryFromArray)(model->dlist, model->assets_file);
    self->map_actor_model  = model->map_actor_model;

    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );
}

void WoodenBridge_Loop(WoodenBridge* self) {
    Model* model = self->model;

    model->primitive_color.integer = sys.primitive_color.integer;
    model->fog_color.integer       = sys.background_color.integer;

    if ((*actor_playerOutsideActorSpawnRadius)(
            self, model->position.x, model->position.y, model->position.z
        )) {
        self->header.destroy(self);
    }
}

void Elevator_Entrypoint(Elevator* self) {
    ENTER(self, Elevator_functions);
}

void Elevator_Init(Elevator* self) {
    ElevatorInner* inner = &self->inner;
    Model* model;
    Model* chain_model;
    u32* chain_model_dl;

    // Cabin model
    self->model = (*Model_createAndSetChild)(FIG_TYPE_STANDALONE, map_lights[0]);
    model       = self->model;
    if (model) {
    }
    (*Actor_SetPosAndAngle)(self, model);
    model->assets_file = MAP_ASSETS_FILE_ID;
    model->dlist       = (u32) &HONMARU_5F_ELEVATOR_DL;
    BITS_SET(model->flags, FIG_FLAG_APPLY_FOG_COLOR | FIG_FLAG_APPLY_PRIMITIVE_COLOR);
    model->primitive_color.integer = sys.primitive_color.integer;
    model->fog_color.integer       = sys.background_color.integer;

    // Hanging chain model
    chain_model = (*Model_createAndSetChild)(FIG_TYPE_STANDALONE, map_lights[0]);
    if (chain_model) {
    }
    self->chain_model = chain_model;
    chain_model_dl    = &HONMARU_5F_ELEVATOR_CHAIN_DL;
    (*Actor_SetPosAndAngle)(self, chain_model);
    chain_model->assets_file = MAP_ASSETS_FILE_ID;
    chain_model->dlist       = chain_model_dl;
    BITS_SET(
        chain_model->flags,
        FIG_FLAG_LOOK_AT_CAMERA_YAW | FIG_FLAG_APPLY_FOG_COLOR | FIG_FLAG_APPLY_PRIMITIVE_COLOR
    );
    chain_model->primitive_color.integer = sys.primitive_color.integer;
    chain_model->fog_color.integer       = sys.background_color.integer;

    (*Model_setMapActorModelNoCollision)(chain_model, chain_model_dl);
    BITS_SET(self->header.ID, OBJ_FLAG_ENABLE_COLLISION | OBJ_FLAG_MOVE_ALONGSIDE_COLLISION);

    model->map_actor_model    = (*getMapActorModelEntryFromArray)(model->dlist, model->assets_file);
    self->map_actor_model     = model->map_actor_model;
    self->move_actor_function = Elevator_MoveActor;

    (*object_curLevel_goToNextFuncAndClearTimer)(
        self->header.current_function, &self->header.function_info_ID
    );

    inner->initial_height         = model->position.y;
    inner->player_inside_elevator = FALSE;

    /*
    * Make the elevator ascend when entering the top elevator map
    * from the bottom elevator map.
    *
    * Otherwise display the elevator already in the top.
    */
    if (sys.SaveStruct_gameplay.spawn == 0) {
        (*play_sound)(SD_ELEVATOR_MOVING);
        inner->height     = 50.0f;
        model->position.y = inner->initial_height - 50.0f;
        inner->speed      = 0.66666669f;
    } else {
        inner->height = 0.0f;
        inner->speed  = 0.0f;
        (*object_nextLevel_goToFunc)(
            self->header.current_function,
            &self->header.function_info_ID,
            ELEVATOR_MAIN_TOP_IDLE_OUTSIDE_ELEVATOR
        );
    }

    chain_model->position.y = model->position.y + 1.0;
    Model_copyPosToVec3f(model, &inner->moving_endpoint);
}

void Elevator_Main(Elevator* self) {
    ElevatorInner* inner = &self->inner;
    Model* model         = self->model;
    Model* chain_model   = self->chain_model;
    s32 temp1;

    model->primitive_color.integer       = sys.primitive_color.integer;
    model->fog_color.integer             = sys.background_color.integer;
    chain_model->primitive_color.integer = sys.primitive_color.integer;
    chain_model->fog_color.integer       = sys.background_color.integer;

    (*Model_copyPosToVec3f)(model, &inner->moving_endpoint);
    ENTER(self, Elevator_main_functions);

    model->position.y       = inner->initial_height - inner->height;
    chain_model->position.y = model->position.y + 1.0;
}

void Elevator_Main_Ascending(Elevator* self) {
    s32 temp[2];
    ElevatorInner* inner = &self->inner;
    Model* model         = self->model;

    inner->player_inside_elevator = Elevator_IsPlayerInsideElevator(model, Elevator_BoundingBox);
    if (inner->player_inside_elevator == FALSE) {
        BITS_UNSET(map_misc_event_flags, HONMARU_5F_FLAG_PLAYER_IS_INSIDE_ELEVATOR);
    }

    inner->height -= inner->speed;
    if (inner->height < 0.0) {
        (*play_sound)(SD_ELEVATOR_ACTIVATE);
        (*play_sound)(STOP_SOUND(SD_ELEVATOR_MOVING));
        inner->bottom_idle_time = 60;
        inner->height           = 0.0f;
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    } else {
        if (inner->speed < 0.6666666666666666) {
            inner->speed += 0.01111111111111111;
        }
    }
}

// The player is inside the elevator while it's idling on top of the map
void Elevator_Main_TopIdleInsideElevator(Elevator* self) {
    ElevatorInner* inner = &self->inner;
    Model* model         = self->model;

    if (inner->player_inside_elevator == FALSE) {
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    } else {
        inner->player_inside_elevator =
            Elevator_IsPlayerInsideElevator(model, Elevator_BoundingBox);
        if (inner->player_inside_elevator == FALSE) {
            BITS_UNSET(map_misc_event_flags, HONMARU_5F_FLAG_PLAYER_IS_INSIDE_ELEVATOR);
        }
    }
}

// The player is outside the elevator while it's idling on top of the map
void Elevator_Main_TopIdleOutsideElevator(Elevator* self) {
    ElevatorInner* inner = &self->inner;
    Model* model         = self->model;

    if (inner->player_inside_elevator == TRUE) {
        (*play_sound)(SD_ELEVATOR_ACTIVATE);
        (*play_sound)(SD_ELEVATOR_MOVING);
        inner->speed = 0.0f;
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
        return;
    } else {
        inner->player_inside_elevator =
            Elevator_IsPlayerInsideElevator(model, Elevator_BoundingBox);
        if (inner->player_inside_elevator == TRUE) {
            BITS_SET(map_misc_event_flags, HONMARU_5F_FLAG_PLAYER_IS_INSIDE_ELEVATOR);
        }
    }
}

void Elevator_Main_Descending(Elevator* self) {
    ElevatorInner* inner = &self->inner;
    Model* model         = self->model;

    inner->height += inner->speed;
    if (inner->height > 200.0) {
        (*play_sound)(SD_ELEVATOR_ACTIVATE);
        (*play_sound)(STOP_SOUND(SD_ELEVATOR_MOVING));
        inner->bottom_idle_time = 60;
        inner->height           = 200.0f;
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.function_info_ID
        );
    } else {
        if (inner->speed < 0.6666666666666666) {
            inner->speed += 0.01111111111111111;
        }
    }
}

// The elevator is idling while at the bottom of the map.
void Elevator_Main_BottomIdle(Elevator* self) {
    ElevatorInner* inner = &self->inner;

    inner->bottom_idle_time--;
    if (inner->bottom_idle_time < 0) {
        inner->speed = 0.0f;
        (*object_curLevel_goToFunc)(
            self->header.current_function, &self->header.function_info_ID, ELEVATOR_MAIN_ASCENDING
        );
    }
}

s32 Elevator_MoveActor(Elevator* self, Model* actor_model) {
    ElevatorInner* inner = &self->inner;

    return (*Actor_moveActorUntilEndpoint)(self->model, actor_model, &inner->moving_endpoint);
}

s32 Elevator_IsPlayerInsideElevator(Model* model, Vec3f bounding_box[]) {
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
