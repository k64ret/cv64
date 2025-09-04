#ifndef HONMARU_5F_ELEVATOR_H
#define HONMARU_5F_ELEVATOR_H

#include "actor.h"

// ID: 0x01DA
typedef struct ElevatorInner {
    Vec3f moving_endpoint;
    f32 initial_height;
    f32 height;
    f32 speed;
    s16 player_inside_elevator;
    s16 bottom_idle_time;
    u8 field_0x50[20];
} ElevatorInner;

typedef struct Elevator {
    ObjectHeader header;
    u8 field_0x20[4];
    Model* model;
    Model* chain_model;
    u8 field_0x2C[8];
    ElevatorInner inner;
    moveActorFunction move_actor_function;
    MapActorModel* map_actor_model;
    u8 field_0x6C[4];
    ActorConfig* settings;
} Elevator;

void Elevator_Entrypoint(Elevator* self);
void Elevator_Init(Elevator* self);
void Elevator_Main(Elevator* self);
void Elevator_Main_Ascending(Elevator* self);
void Elevator_Main_TopIdleInsideElevator(Elevator* self);
void Elevator_Main_TopIdleOutsideElevator(Elevator* self);
void Elevator_Main_Descending(Elevator* self);
void Elevator_Main_BottomIdle(Elevator* self);
s32 Elevator_MoveActor(Elevator* self, Model* actor_model);
s32 Elevator_IsPlayerInsideElevator(Model* model, Vec3f bounding_box[]);

typedef void (*ElevatorFunc)(Elevator*);

typedef enum ElevatorFuncId {
    ELEVATOR_INIT,
    ELEVATOR_MAIN
} ElevatorFuncId;

typedef enum ElevatorMainFuncId {
    ELEVATOR_MAIN_ASCENDING,
    ELEVATOR_MAIN_TOP_IDLE_INSIDE_ELEVATOR,
    ELEVATOR_MAIN_TOP_IDLE_OUTSIDE_ELEVATOR,
    ELEVATOR_MAIN_DESCENDING,
    ELEVATOR_MAIN_BOTTOM_IDLE
} ElevatorMainFuncId;

extern const u32 HONMARU_5F_ELEVATOR_DL;
extern const u32 HONMARU_5F_ELEVATOR_CHAIN_DL;

#endif
