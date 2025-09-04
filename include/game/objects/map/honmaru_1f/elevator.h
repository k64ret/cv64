#ifndef HONMARU_1F_ELEVATOR_H
#define HONMARU_1F_ELEVATOR_H

#include "actor.h"

typedef struct ElevatorInner {
    Vec3f moving_endpoint;
    f32 height;
    f32 speed;
    f32 initial_height;
    s16 player_inside_elevator;
    s16 top_idle_time;
    u8 field_0x1C[20];
} ElevatorInner;

// ID: 0x01C9
typedef struct Elevator {
    ObjectHeader header;
    u8 field_0x20[4];
    Model* model;
    u8 field_0x28[12];
    ElevatorInner inner;
    moveActorFunction move_actor_function;
    MapActorModel* map_actor_model;
    s32 field_0x6C;
    ActorConfig* settings;
} Elevator;

void Elevator1F_Entrypoint(Elevator* self);
void Elevator1F_Init(Elevator* self);
void Elevator1F_Main(Elevator* self);
void Elevator1F_Main_BottomIdleOutsideElevator(Elevator* self);
void Elevator1F_Main_Ascending(Elevator* self);
void Elevator1F_Main_TopIdle(Elevator* self);
void Elevator1F_Main_Descending(Elevator* self);
void Elevator1F_Main_BottomIdleInsideElevator(Elevator* self);
s32 Elevator1F_MoveActor(Elevator* self, Model* actor_model);
s32 Elevator1F_IsPlayerInsideElevator(Model* model, Vec3f bounding_box[]);

typedef void (*ElevatorFunc)(Elevator*);

typedef enum ElevatorFuncId {
    ELEVATOR_INIT,
    ELEVATOR_MAIN
} ElevatorFuncId;

typedef enum ElevatorMainFuncId {
    ELEVATOR_MAIN_BOTTOM_IDLE_OUTSIDE_ELEVATOR,
    ELEVATOR_MAIN_ASCENDING,
    ELEVATOR_MAIN_TOP_IDLE,
    ELEVATOR_MAIN_DESCENDING,
    ELEVATOR_MAIN_BOTTOM_IDLE_INSIDE_ELEVATOR
} ElevatorMainFuncId;

extern const u32 HONMARU_1F_ELEVATOR_DL;

#endif
