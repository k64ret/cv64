/**
 * @file necro_work.c
 *
 * This file contains the code that creates `NecroWork`,
 * which is used in conjuction with the `Necronomicon` object.
 */

#include "objects/menu/necronomicon.h"

NecroWork* necroWork_create(ObjectHeader* parent, FigureLight* light, u8 flags, s32 arg3) {
    NecroWork* work;
    Necronomicon* necro_obj;

    necro_obj = (Necronomicon*) (*object_create)(parent, MENU_NECRONOMICON);
    if (necro_obj != NULL) {
        (*allocStructInObjectEntryList)("necro_work", necro_obj, sizeof(NecroWork), 15);
        work = necro_obj->work;
        if (work != NULL) {
            work->flags                             = flags;
            work->necro_light                       = light;
            work->position.x                        = 0.0f;
            work->position.y                        = 0.0f;
            work->position.z                        = 0.0f;
            work->last_page_flipped                 = FALSE;
            work->time_before_flipping_another_page = 0;
            work->pages_to_flip_before_closing      = 0;
            work->necro_destroy_delay_time          = 0;
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }
    return work;
}
