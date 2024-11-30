#ifndef INTERACTABLES_HELPERS_H
#define INTERACTABLES_HELPERS_H

#include "interactables.h"
#include "save.h"
#include "actor_config.h"

#define INTERACT_TYPE_NONE       0
#define INTERACT_TYPE_ITEM       1
#define INTERACT_TYPE_PULL_LEVER 2 // See `interactables_getInteractingType`
#define INTERACT_TYPE_TEXT_SPOT  3

typedef struct door_item_open_verify_struct {
    s16 item;
    s16 event_flag_ID;
    u32 event_flag;
} door_item_open_verify_struct;

// Generic special textbox / text spot struct
typedef struct specialTextbox {
    ObjectHeader header;
    u8 field_0x20[20];
    s32 text_ID;
    u8 field_0x38[4];
    u32 interacting_with_interactable;
    u32 textbox_is_active;
    u8 field_0x44[20];
    f32 trigger_size_X;
    f32 trigger_size_Z;
    MfdsState* message_textbox;
    Vec3f position;
    ActorConfig* settings;
} specialTextbox;

specialTextbox* Player_getActorCurrentlyInteractingWith();
specialTextbox* Player_getSpecialTextboxCurrentlyInteractingWith(s16 actor_ID, Model* player_model);
s32 playerCanInteractWithInteractuable(
    f32 actor_pos_X, f32 actor_pos_Y, f32 actor_pos_Z, Interactable* actor
);
s32 interactables_getInteractingType(specialTextbox* actor);
void interactables_enableTextbox(specialTextbox* actor);
void interactables_setInteractingFlag(specialTextbox* actor);
u32 getMapEventFlagID(s16 stage_ID);
void spawnCastleWallGratingMechanismTextboxes(s16 index);
void removeKeyWhenOpeningDoor(s16 event_flag_ID, u32 event_flag);

extern door_item_open_verify_struct door_item_open_verify_list[13];
extern ActorConfig* castleWallGratingMechanism_textSpotsActorConfig[1][3];

#endif
