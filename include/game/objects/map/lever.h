#ifndef LEVER_H
#define LEVER_H

#include "actor.h"

#define LEVER_STATE_RAISED_UP 0
#define LEVER_STATE_PULL      1

// (Forest of Silence) The first lever, which opens the first grate, which summons a Weretiger
#define LEVER_TYPE_WERETIGER 0
// (Castle Wall Main) White Dragon lever
#define LEVER_TYPE_WHITE_DRAGON 0
// (Forest of Silence) The second lever, which lowers two platforms
#define LEVER_TYPE_LOWER_PLATFORMS 1
// (Castle Wall Main) The lever in the room the player watches Dracula for the first time
#define LEVER_TYPE_DRACULA 1
// The third lever, which opens the door leading to the fourth lever
#define LEVER_TYPE_OPEN_LEVER_4_DOOR 2
// The fourth lever, which opens the grating towards the final King Skeleton
#define LEVER_TYPE_OPEN_BOSS_DOOR 3

typedef struct {
    u8 field_0x00[6];
    s16 field_0x06;
    u8 field_0x08[20];
} struct_56;

typedef struct {
    void* field_0x00; // A function pointer
    struct_56* field_0x04;
    u32 dlist;
    s32 file_ID;
    s32 event_flag_ID;
    u32 event_flag;
    s32 sound_ID;
} struct_21;

// ID 0x016F
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[4];
    Model* model;
    u8 field_0x28[12];
    struct_56* field_0x34;
    void* field_0x38; // A function pointer
    struct_21* field_0x3C;
    s32 field_0x40;
    s32 field_0x44;
    s32 current_lever_pull_time;
    s32 max_lever_pull_time;
    s32 model_pitch;
    u8 field_0x54[24];
    s32 state;
    ActorConfig* settings;
} lever;

void lever_init(lever* self);
void lever_main_entrypoint(lever* self);
void lever_raisedUp(lever* self);
void lever_pull(lever* self);
void lever_doNothing(lever* self);

#endif
