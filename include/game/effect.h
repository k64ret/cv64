#ifndef CV64_EFFECT_H
#define CV64_EFFECT_H

#include "gfx/model.h"
#include "gfx/camera.h"
#include "objects/camera/pointLight.h"
#include "actor.h"

/**
 * IDs in `effect_obj_info_array`
 */
typedef enum EffectObjInfoArrayID {
    EFFECT_ID_0                   = 0x00,
    EFFECT_ID_1                   = 0x01,
    EFFECT_ID_PICKABLE_ITEM_FLASH = 0x25
} EffectObjInfoArrayID;

typedef enum EffectAnimInfoVisualFlag {
    EFF_ANIM_VISUAL_FLAG_VARIABLE_TRANSPARENCY = BIT(1)
} EffectAnimInfoVisualFlag;

typedef enum EffectAnimInfoFlag {
    EFF_ANIM_FLAG_ACTIVE = BIT(13)
} EffectAnimInfoVisualFlag;

/**
* These defines are used for the last arguments
* of some of the `effect` setters.
*
* They indicate how the position, angle, scale, etc,
* should be manipulated when it gets stored in `EffectVisualInfo`
*/
#define POSITION_MULTIPLIED_BY_VISUAL_INFO 2
#define POSITION_PLUS_VISUAL_INFO          4
#define POSITION_EQUAL_TO_VISUAL_INFO      8

#define ANGLE_PLUS_VISUAL_INFO     4
#define ANGLE_EQUAL_TO_VISUAL_INFO 8

#define SIZE_MULTIPLIED_BY_VISUAL_INFO 2
#define SIZE_PLUS_VISUAL_INFO          4
#define SIZE_EQUAL_TO_VISUAL_INFO      8

typedef struct {
    u32 flags;
    u16 color_intensity_transition_current_time;
    u16 current_spawned_time;
    u8 environment_color_alpha;
    u8 field_0x09;
    u16 color_intensity_transition_speed;
    pointLight* light;
    Model* attached_bone;
    u8 field_0x14[4];
    void (*object_destroy_function)(void*);
} effect_info;

typedef struct {
    Vec3f scale;
    f32 scale_multiplier;
    s16 angle;
    u16 flags;
} EffectPositionalInfo;

typedef struct {
    u8 visual_flags;
    u8 field_0x01;
    u8 field_0x02;
    u8 field_0x03;
    u8 current_frame_speed;
    u8 max_frame_speed;
    u8 field_0x06;
    u8 field_0x07;
    s16 field_0x08;
    u16 flags_and_number_of_frames; // Upper byte: Flags, lower byte = number of frames
    u8 field_0x0C[4];
} EffectAnimationInfo;

// Generic effect struct
typedef struct cv64_effect {
    ObjectHeader header;
    u8 field_0x04[4];
    Model* model;
    u8 field_0x28[60];
    effect_info* info;
    EffectPositionalInfo* positional_info;
    EffectVisualInfo* visual_info;
    ActorConfig* settings;
} Effect;

typedef struct {
    u32 flags;
    Model* model;
    Camera* display_camera;
    EffectAnimationInfo anim_info;
    u16 max_frame_speed;
    u16 field_0x1E; // Another color_intensity_transition_max_time?
    u16 field_0x20; // Another color_intensity_transition_max_time?
    u16 color_intensity_transition_max_time;
    s16 field_0x24;
    u16 max_spawned_time;
    Vec3f position;
    Vec3f scale;
    Angle angle;
    u8 field_0x46[2];
    RGBA primitive_color;
    RGBA environment_color;
    void (*loop_function)(Effect*);
    u8 field_0x54; // For damage-related effects, this is `atari_damage_type`
    u8 field_0x55;
    u8 field_0x56[2];
} EffectVisualInfo;

extern Effect* createEffectObjectUnderEffectMgr(
    u16 effect_obj_info_array_index, Camera* display_camera, u32 visual_flags
);

extern void effect_setPosition(Effect* self, f32 x, f32 y, f32 z, u16 arg4);
extern void effect_setAngle(Effect* self, s16 pitch, s16 yaw, s16 roll, u16 arg4);
extern void effect_setScale(Effect* self, f32 x, f32 y, f32 z, u16 arg4);
extern void effect_setMaxFrameSpeed(Effect* self, u16 max_frame_speed);
extern u8 effect_isMarkForDeletion(Effect* self);
extern void effect_markForDeletion(Effect* self);

#endif // CV64_EFFECT_H
