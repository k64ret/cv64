#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "object.h"

// ID: 0x0007
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[OBJECT_SIZE - 0x20];
} PlayerController;

extern void PlayerController_entrypoint(PlayerController* self);
extern void PlayerController_createPlayerObject(PlayerController* self);

typedef void (*PlayerController_func_t)(PlayerController*);

extern PlayerController* ptr_PlayerController;

#endif
