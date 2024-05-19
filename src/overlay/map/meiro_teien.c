/**
 * @file meiro_teien.c
 *
 * Contains the code for objects exclusive to MEIRO TEIEN
 * (Maze Garden)
*/

#include "objects/map/meiro_teien/object_01B5.h"

/** Only one map-exclusive object is defined for the Maze Garden map,
*   but it only removes itself from memory the moment it spawns.
*/
void obj01B5_entrypoint(object_01B5* self) {
    self->header.destroy(self);
}
