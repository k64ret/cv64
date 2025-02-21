/**
 * @file page_work.c
 *
 * Contains the creation function for the `PageWork` struct,
 * which stores data related to the `page` object.
 */

#include "objects/menu/page.h"

PageWork* pageWork_create(
    ObjectHeader* parent,
    FigureLight* page_light,
    u8 flags,
    f32 pos_X,
    f32 pos_Y,
    f32 pos_Z,
    u8 flip_anim_keyframe,
    f32 anim_speed
) {
    PageWork* work;
    Page* page_obj;

    page_obj = (Page*) (*object_create)(parent, MENU_PAGE);
    if (page_obj != NULL) {
        (*allocStructInObjectEntryList)("page_work", page_obj, sizeof(PageWork), 15);
        work = page_obj->work;
        if (work != NULL) {
            work->page_light         = page_light;
            work->flags              = flags;
            work->position.x         = pos_X;
            work->position.y         = pos_Y;
            work->position.z         = pos_Z;
            work->flip_anim_keyframe = flip_anim_keyframe;
            work->anim_speed         = anim_speed;
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }
    return work;
}
