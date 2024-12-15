#ifndef CV64_EFFECT_H
#define CV64_EFFECT_H

#include "objects/effect/effect_manager.h"
#include "objects/camera/pointLight.h"
#include "actor.h"

/**
 * IDs in `effect_obj_info_array`
 */
typedef enum EffectObjInfoArrayID {
    EFFECT_ID_FIRE                = 0x00,
    EFFECT_ID_01                  = 0x01,
    EFFECT_ID_FIRE_SPARKLES       = 0x1A,
    EFFECT_ID_PICKABLE_ITEM_FLASH = 0x25
} EffectObjInfoArrayID;

typedef enum EffectVisualFlag {
    EFF_VISUAL_FLAG_DESTROY                                = BIT(3),
    EFF_VISUAL_FLAG_EMIT_LIGHT                             = BIT(4),
    EFF_VISUAL_FLAG_ANIMATE_SCALE                          = BIT(5),
    EFF_VISUAL_FLAG_NO_VARIABLE_TRANSPARENCY               = BIT(7),
    EFF_VISUAL_FLAG_200                                    = BIT(9),
    EFF_VISUAL_FLAG_DONT_FADE_OUT_WHEN_MARKED_FOR_DELETION = BIT(14),
    EFF_VISUAL_FLAG_DONT_ANIMATE =
        BIT(18), // Don't animate through the usual rotation / translation system
    EFF_VISUAL_FLAG_HIDE                                    = BIT(19),
    EFF_VISUAL_FLAG_200000                                  = BIT(21),
    EFF_VISUAL_FLAG_LOOK_AT_CAMERA_YAW                      = BIT(22),
    EFF_VISUAL_FLAG_LOOK_AT_CAMERA_PITCH                    = BIT(23),
    EFF_VISUAL_FLAG_CREATE_MODEL_AND_SET_CHILD_AFTER_PARENT = BIT(26),
    EFF_VISUAL_FLAG_CREATE_MODEL_AND_SET_CHILD              = BIT(27),
    EFF_VISUAL_FLAG_20000000                                = BIT(29)
} EffectVisualFlag;

typedef enum EffectAnimInfoVisualFlag {
    EFF_ANIM_VISUAL_FLAG_VARIABLE_TRANSPARENCY = BIT(1)
} EffectAnimInfoVisualFlag;

typedef enum EffectAnimInfoFlag {
    EFF_ANIM_FLAG_ACTIVE = BIT(13)
} EffectAnimInfoFlag;

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

#define REMOVE_FLAGS 4
#define SET_FLAGS    8

#define EFF_COLOR_TYPE_ENVIRONMENT 4
#define EFF_COLOR_TYPE_PRIMITIVE   8

typedef struct EffectInfo {
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
} EffectInfo;

typedef struct EffectPositionalInfo {
    Vec3f scale;
    f32 scale_multiplier;
    s16 angle;
    u16 flags;
} EffectPositionalInfo;

typedef struct EffectAnimationInfo {
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

typedef struct EffectVisualInfo {
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
    void (*loop_function)(void*);
    u8 field_0x54; // For damage-related effects, this is `atari_damage_type`
    u8 field_0x55;
    u8 field_0x56[2];
} EffectVisualInfo;

// Generic effect struct
typedef struct Effect {
    ObjectHeader header;
    u8 field_0x04[4];
    Model* model;
    u8 field_0x28[60];
    EffectInfo* info;
    EffectPositionalInfo* positional_info;
    EffectVisualInfo* visual_info;
    ActorConfig* settings;
} Effect;

extern Effect* createEffectObject(
    u16 effect_obj_info_array_index, Camera* display_camera, u32 visual_flags, void* parent
);
extern Effect* createEffectObjectUnderEffectMgr(
    u16 effect_obj_info_array_index, Camera* display_camera, u32 visual_flags
);

extern u16 effect_init(Effect* self);
extern void effect_initParams(Effect* self, s32 index, Camera* display_camera, u32 visual_flags);
extern Model* effect_getModel(Effect* self);
extern void effect_updateGraphicParams(Effect* self);
extern void effect_setPosition(Effect* self, f32 x, f32 y, f32 z, u16 arg4);
extern void effect_setAngle(Effect* self, s16 pitch, s16 yaw, s16 roll, u16 arg4);
extern void effect_setScale(Effect* self, f32 x, f32 y, f32 z, u16 arg4);
extern void effect_setMaxFrameSpeed(Effect* self, u16 max_frame_speed);
extern u8 effect_loop(Effect* self);
extern u8 effect_isMarkForDeletion(Effect* self);
extern void effect_markForDeletion(Effect* self);
extern void effect_createPointLight(Effect* self);
extern void effect_editVisualInfoFlags(Effect* self, u32 visual_flags, u32 edit_type);
extern u32 effect_getColor(Effect* self, u32 color_type);
extern void effect_setColor(Effect* self, u32 color, u32 color_type);
extern void effect_setLoopFunction(Effect* self, void (*loop_function)(Effect*));

extern void effectAnimationInfo_create(EffectAnimationInfo* anim_info, u16);
extern void effectAnimationInfo_init(
    EffectAnimationInfo* anim_info, Model* model, u8 max_frame_speed, f32 speed
);
extern void
func_8000E1B4(EffectAnimationInfo* anim_info, Model* model, u8 max_frame_speed, f32 speed);
extern void
effectAnimationInfo_setAnimParams(EffectAnimationInfo* anim_info, u8 max_frame_speed, f32 speed);

#endif // CV64_EFFECT_H
