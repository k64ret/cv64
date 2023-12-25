/**
 * File: meiro_teien.c
 * Description: Contains the code for objects exclusive to MEIRO TEIEN (Maze
 * Garden) Associated objects: 0x01B5
 *
 * osMapTLB'd? = No
 * Entrypoint address   = 0x8018EB10
 * Associated files ptr = 0x8018EB40
 * Associated files:
 *   0x6C50E0 - 0x6C5110 (Overlay)
 */

#include "objects/map_objects/obj_01B5.h"

// Only one map-exclusive object is defined for the Maze Garden map,
// but it only removes itself from memory the moment it spawns.
void obj01B5_entrypoint(obj_01B5* self) { self->header.destroy(self); }
