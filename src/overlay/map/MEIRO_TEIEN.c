/**
 * File: MEIRO_TEIEN.c
 * Description: Contains the code for objects exclusive to MEIRO TEIEN (Maze
 * Garden) Associated objects: 0x01B5
 *
 * osMapTLB'd? = No
 * Entrypoint address   = 0x8018EB10
 * Associated files ptr = 0x8018EB40
 * Associated files:
 *   0x6C50E0 - 0x6C5110 (Overlay)
 */

#include "objects/map_objects/MEIRO_TEIEN/cv64_meiroteien_obj01B5.h"

// Only one map-exclusive object is defined for the Maze Garden map,
// but it only removes itself from memory the moment it spawns.
void cv64_meiroteien_obj01B5_entrypoint(cv64_meiroteien_obj01B5_t* self) {
    self->header.destroy(self);
}
