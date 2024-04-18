#ifndef MARK_H
#define MARK_H

#include "gfx/camera.h"
#include "gfx/model_info.h"
#include "object.h"

typedef enum mark_work_flags {
    DRAW_CIRCLE                        = 0x01,
    DRAW_CROSS                         = 0x02,
    DISPLAY                            = 0x04,
    DESTROY                            = 0x08,
    DONT_DISPLAY                       = 0x10, // See 0x8014FC18
    DESTROY_AFTER_FINISHING_DISPLAYING = 0x20
} mark_work_flags;

typedef struct {
    camera* display_camera;
    u8 flags;
    u8 field_0x05[3];
    vec3f position;
    vec3f size;
    u8 display_anim_speed;
    u8 display_anim_timer;
    u8 field_0x22[2];
} mark_work;

// ID: 0x0133
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[4];
    cv64_model_inf_t* model;
    u8 field_0x28[68];
    u32 already_played_sound;
    mark_work* work;
} mark;

void mark_entrypoint(mark* self);
void mark_isWorkCreated(mark* self);
void mark_init(mark* self);
void mark_loop(mark* self);
void mark_destroy(mark* self);

typedef void (*mark_func_t)(mark*);

#endif // MARK_H
