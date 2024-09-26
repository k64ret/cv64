#ifndef MARK_H
#define MARK_H

#include "gfx/camera.h"
#include "gfx/model.h"
#include "object.h"

typedef enum mark_work_flags {
    MARK_FLAG_DRAW_CIRCLE                        = 0x01,
    MARK_FLAG_DRAW_CROSS                         = 0x02,
    MARK_FLAG_DISPLAY                            = 0x04,
    MARK_FLAG_DESTROY                            = 0x08,
    MARK_FLAG_DONT_DISPLAY                       = 0x10, // See 0x8014FC18
    MARK_FLAG_DESTROY_AFTER_FINISHING_DISPLAYING = 0x20
} mark_work_flags;

typedef struct {
    Camera* display_camera;
    u8 flags;
    u8 field_0x05[3];
    Vec3f position;
    Vec3f size;
    u8 display_anim_speed;
    u8 display_anim_timer;
    u8 field_0x22[2];
} mark_work;

// ID: 0x0133
typedef struct {
    ObjectHeader header;
    u8 field_0x20[4];
    Model* model;
    u8 field_0x28[68];
    u32 already_played_sound;
    mark_work* work;
} mark;

extern void mark_entrypoint(mark* self);
extern void mark_isWorkCreated(mark* self);
extern void mark_init(mark* self);
extern void mark_loop(mark* self);
extern void mark_destroy(mark* self);
extern mark_work* markWork_create(
    void* parent,
    Camera* display_camera,
    u8 flags,
    f32 pos_X,
    f32 pos_Y,
    f32 pos_Z,
    f32 size_X,
    f32 size_Y,
    f32 size_Z,
    f32 display_anim_speed
);

typedef void (*mark_func_t)(mark*);

#endif // MARK_H
