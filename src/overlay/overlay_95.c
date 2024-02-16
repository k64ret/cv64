/**
 * File: overlay_95.c
 * Description:
 *   This file is related to the Demon Dracula boss, since it's loaded before
 * the battle begins, and the object associated to this overlay also loads the
 * file ID 0x2B, which contains the assets for the Demon Dracula enemy.
 *
 *   It's unknown what its actual purpose is. Either it used to contain some
 * additional code related to Demon Dracula, or its only purpose is to be a
 * placeholder so that the game can load the Demon Dracula's assets file.
 * Associated objects: 0x20B7
 *
 * Mapped by the TLB? = Yes
 */

#include "objects/enemy/demon_dracula/object_20B7.h"

void obj20B7_entrypoint(object_20B7* self) {}
