#ifndef OBJECT_8015C368_H
#define OBJECT_8015C368_H

#include "actor.h"

/**
 * Variable 1:
 * 0 = Move to the left
 * Any other value = Move to the right
 *
 * The game would have loaded different models depending
 * if this object was moving either to the left or to the right.
 */

// ID unknown
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[4];
    cv64_model_inf_t* model;
    u8 field_0x28[OBJECT_SIZE - 0x2C];
    ActorConfig* settings;
} object_8015C368;

void obj8015C368_entrypoint(object_8015C368* self);
void obj8015C368_init(object_8015C368* self);
void obj8015C368_loop(object_8015C368* self);

typedef void (*obj8015C368_func_t)(object_8015C368*);

#endif
