#ifndef A9560_H
#define A9560_H

#include "objects/cutscene/interactuables.h"
#include "save.h"
#include "actor_settings.h"

#define INTERACT_TYPE_NONE      0
#define INTERACT_TYPE_ITEM      1
#define INTERACT_TYPE_TEXT_SPOT 2
#define INTERACT_TYPE_OTHERS    3 /* Special textboxes, doors, etc */

typedef struct door_item_open_verify_struct {
    s16 item_ID;
    s16 event_flag_IDs;
    u32 event_flag;
} door_item_open_verify_struct;

s32 interactuables_getInteractingType(interactuables* self);
void interactuables_enableTextbox(interactuables* self);
void interactuables_setInteractingFlag(interactuables* self);
u32 getMapEventFlagID(s16 stage_ID);
void spawnCastleWallGratingMechanismTextboxes(s16 index);
void checkDoorCanBeOpenedWithKey(s16 event_flag_IDs, u32 event_flag);

extern door_item_open_verify_struct door_item_open_verify_list[13];
extern cv64_actor_settings_t* castleWallGratingMechanism_textSpotsActorSettings[1][3];

#endif
