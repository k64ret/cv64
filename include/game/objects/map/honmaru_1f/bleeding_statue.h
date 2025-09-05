#ifndef HONMARU_1F_BLEEDING_STATUE_H
#define HONMARU_1F_BLEEDING_STATUE_H

#include "actor.h"

// ID: 0x01C8
typedef struct BleedingStatue {
    ObjectHeader header;
    u8 field_0x20[4];
    Model* model;
    u8 field_0x28[72];
    ActorConfig* settings;
} BleedingStatue;

void BleedingStatue_Entrypoint(BleedingStatue* self);
void BleedingStatue_Init(BleedingStatue* self);
void BleedingStatue_Main(BleedingStatue* self);
void BleedingStatue_Main_Idle(BleedingStatue* self);
void BleedingStatue_Main_InCutscene(BleedingStatue* self);
void BleedingStatue_Main_AfterCutscene(BleedingStatue* self);

typedef void (*BleedingStatueFunc)(BleedingStatue*);

typedef enum BleedingStatueFuncId {
    BLEEDING_STATUE_INIT,
    BLEEDING_STATUE_MAIN
} BleedingStatueFuncId;

typedef enum BleedingStatueMainFuncId {
    BLEEDING_STATUE_MAIN_IDLE,
    BLEEDING_STATUE_MAIN_IN_CUTSCENE,
    BLEEDING_STATUE_MAIN_AFTER_CUTSCENE
} BleedingStatueMainFuncId;

extern const u32 HONMARU_1F_BLEEDING_STATUE_DL;

typedef struct BleedingStatueBloodInner {
    u8 field_0x00[4];
    s32 blend_color_transparency;
    u8 field_0x08[48];
} BleedingStatueBloodInner;

// ID: 0x01CB
typedef struct BleedingStatueBlood {
    ObjectHeader header;
    u8 field_0x20[4];
    Model* model;
    u8 field_0x28[12];
    BleedingStatueBloodInner inner;
    s32 should_spill_blood;
    ActorConfig* settings;
} BleedingStatueBlood;

void BleedingStatueBlood_Entrypoint(BleedingStatueBlood* self);
void BleedingStatueBlood_Init(BleedingStatueBlood* self);
void BleedingStatueBlood_Main(BleedingStatueBlood* self);
void BleedingStatueBlood_Main_NoBlood(BleedingStatueBlood* self);
void BleedingStatueBlood_Main_SpillingBlood(BleedingStatueBlood* self);
void BleedingStatueBlood_Main_IdleBlood(BleedingStatueBlood* self);
void BleedingStatueBlood_Destroy(BleedingStatueBlood* self);

typedef void (*BleedingStatueBloodFunc)(BleedingStatueBlood*);

typedef enum BleedingStatueBloodFuncId {
    BLEEDING_STATUE_BLOOD_INIT,
    BLEEDING_STATUE_BLOOD_MAIN,
    BLEEDING_STATUE_BLOOD_DESTROY
} BleedingStatueBloodFuncId;

typedef enum BleedingStatueBloodMainFuncId {
    BLEEDING_STATUE_BLOOD_MAIN_NO_BLOOD,
    BLEEDING_STATUE_BLOOD_MAIN_SPILLING_BLOOD,
    BLEEDING_STATUE_BLOOD_MAIN_IDLE_BLOOD
} BleedingStatueBloodMainFuncId;

extern const u32 HONMARU_1F_BLEEDING_STATUE_BLOOD_DL;

typedef struct BleedingStatueBloodSpotInner {
    u8 field_0x00[4];
    s32 blend_color_transparency;
    u8 field_0x08[52];
} BleedingStatueBloodSpotInner;

// ID: 0x01CC
typedef struct BleedingStatueBloodSpot {
    ObjectHeader header;
    u8 field_0x20[4];
    Model* model;
    u8 field_0x28[12];
    BleedingStatueBloodSpotInner inner;
    ActorConfig* settings;
} BleedingStatueBloodSpot;

void BleedingStatueBloodSpot_Entrypoint(BleedingStatueBloodSpot* self);
void BleedingStatueBloodSpot_Init(BleedingStatueBloodSpot* self);
void BleedingStatueBloodSpot_Main(BleedingStatueBloodSpot* self);
void BleedingStatueBloodSpot_Main_NoBlood(BleedingStatueBloodSpot* self);
void BleedingStatueBloodSpot_Main_SpillingBlood(BleedingStatueBloodSpot* self);
void BleedingStatueBloodSpot_Main_IdleBlood(BleedingStatueBloodSpot* self);

typedef void (*BleedingStatueBloodSpotFunc)(BleedingStatueBloodSpot*);

typedef enum BleedingStatueBloodSpotFuncId {
    BLEEDING_STATUE_BLOOD_SPOT_INIT,
    BLEEDING_STATUE_BLOOD_SPOT_MAIN
} BleedingStatueBloodSpotFuncId;

typedef enum BleedingStatueBloodSpotMainFuncId {
    BLEEDING_STATUE_BLOOD_SPOT_MAIN_NO_BLOOD,
    BLEEDING_STATUE_BLOOD_SPOT_MAIN_SPILLING_BLOOD,
    BLEEDING_STATUE_BLOOD_SPOT_MAIN_IDLE_BLOOD
} BleedingStatueBloodSpotMainFuncId;

extern const u32 HONMARU_1F_BLEEDING_STATUE_BLOOD_SPOT_DL;

#endif
