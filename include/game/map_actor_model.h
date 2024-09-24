#ifndef MAP_ACTOR_MODEL_H
#define MAP_ACTOR_MODEL_H

#include "collision.h"

typedef struct MapActorModel {
    CollisionTri* collision;
    void* field_0x04;
    void* field_0x08;
    u32 dlist;
    s16 field_0x10;
    u16 total_number_of_collision_triangles;
    s16 file_ID;
    Vec3 field_0x16;
} MapActorModel;

extern MapActorModel* getMapActorModelEntryFromArray(u32 segment_address, s32 file_ID);

#endif
