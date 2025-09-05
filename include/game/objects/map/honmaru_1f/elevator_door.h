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
void ElevatorDoor_Main_DeactivatedClosed(ElevatorDoor* self);
void ElevatorDoor_Main_Opening(ElevatorDoor* self);
void ElevatorDoor_Main_IsPlayerOutOfElevator(ElevatorDoor* self);
void ElevatorDoor_Main_Opened(ElevatorDoor* self);
void ElevatorDoor_Main_Closing(ElevatorDoor* self);
void ElevatorDoor_Main_Closed(ElevatorDoor* self);
void ElevatorDoor_Destroy(ElevatorDoor* self);

typedef void (*ElevatorDoorFunc)(ElevatorDoor*);

typedef enum ElevatorDoorFuncId {
    ELEVATOR_DOOR_INIT,
    ELEVATOR_DOOR_MAIN
} ElevatorDoorFuncId;

typedef enum ElevatorDoorMainFuncId {
    ELEVATOR_DOOR_MAIN_DEACTIVATED_CLOSED,
    ELEVATOR_DOOR_MAIN_OPENING,
    ELEVATOR_DOOR_MAIN_IS_PLAYER_OUT_OF_ELEVATOR,
    ELEVATOR_DOOR_MAIN_OPENED,
    ELEVATOR_DOOR_MAIN_CLOSING,
    ELEVATOR_DOOR_MAIN_CLOSED
} ElevatorDoorMainFuncId;

extern const u32 HONMARU_1F_ELEVATOR_DOOR_DL;

#endif
