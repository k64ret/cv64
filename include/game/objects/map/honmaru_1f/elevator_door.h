#ifndef HONMARU_1F_ELEVATOR_DOOR_H
#define HONMARU_1F_ELEVATOR_DOOR_H

#include "actor.h"

typedef struct ElevatorDoorInner {
    atari_base_work* atari_base;
    ObjectDestroyFunc obj_destroy_function;
    f32 slide_length;
    f32 speed;
    s16 field_0x10;
    s16 player_inside_elevator;
    u8 field_0x14[32];
} ElevatorDoorInner;

// ID: 0x01C7
typedef struct ElevatorDoor {
    ObjectHeader header;
    u8 field_0x20[4];
    Model* model;
    u8 field_0x28[12];
    ElevatorDoorInner inner;
    MapActorModel* map_actor_model;
    s32 field_0x6C;
    ActorConfig* settings;
} ElevatorDoor;

void ElevatorDoor_Entrypoint(ElevatorDoor* self);
void ElevatorDoor_Init(ElevatorDoor* self);
void ElevatorDoor_Main(ElevatorDoor* self);
void ElevatorDoor_Main_BottomIdleOutsideElevatorDoor(ElevatorDoor* self);
void ElevatorDoor_Main_Ascending(ElevatorDoor* self);
void ElevatorDoor_Main_TopIdle(ElevatorDoor* self);
void ElevatorDoor_Main_Descending(ElevatorDoor* self);
void ElevatorDoor_Main_BottomIdleInsideElevatorDoor(ElevatorDoor* self);
s32 ElevatorDoor_MoveActor(ElevatorDoor* self, Model* actor_model);
s32 ElevatorDoor_IsPlayerInsideElevatorDoor(Model* model, Vec3f bounding_box[]);

typedef void (*ElevatorDoorFunc)(ElevatorDoor*);

typedef enum ElevatorDoorFuncId {
    ELEVATOR_DOOR_INIT,
    ELEVATOR_DOOR_MAIN
} ElevatorDoorFuncId;

typedef enum ElevatorDoorMainFuncId {
    ELEVATOR_DOOR_MAIN_BOTTOM_IDLE_OUTSIDE_ELEVATOR_DOOR,
    ELEVATOR_DOOR_MAIN_ASCENDING,
    ELEVATOR_DOOR_MAIN_TOP_IDLE,
    ELEVATOR_DOOR_MAIN_DESCENDING,
    ELEVATOR_DOOR_MAIN_BOTTOM_IDLE_INSIDE_ELEVATOR_DOOR,
    ELEVATOR_DOOR_MAIN_CLOSED
} ElevatorDoorMainFuncId;

extern const u32 HONMARU_1F_ELEVATOR_DOOR_DL;

#endif
