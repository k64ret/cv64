#ifndef MAP_ACTOR_MODEL_H
#define MAP_ACTOR_MODEL_H

#include "collision.h"

typedef struct cv64_map_actor_model {
    cv64_collision_triangle_t* collision;
    void* field_0x04;
    void* field_0x08;
    u32 dlist;
    s16 field_0x10;
    u16 total_number_of_collision_triangles;
    s16 file_ID;
    vec3s field_0x16;
} cv64_map_actor_model_t;

extern cv64_map_actor_model_t* getMapActorModelEntryFromArray(u32 segment_address, s32 file_ID);

#endif
