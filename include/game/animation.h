#ifndef ANIMATION_H
#define ANIMATION_H

#include "gfx/model_info.h"

// Flags for animation data
#define ANIM_FLAG_LOOP          0x20000000
#define ANIM_FLAG_LAST_KEYFRAME 0x40000000

// Flags for `animation_info`
#define ANIM_INFO_FLAG_LOOP  0x01
#define ANIM_INFO_FLAG_PAUSE 0x08
/**
 * Maybe also mirror animation? Set when you're grabbed by the Weretiger
 */
#define ANIM_INFO_FLAG_DONT_SMOOTH_OUT_POSITION_TRANSITION 0x10

typedef struct {
    u8 flags;
    u8 field_0x01;
    /**
     * Animation speed * 16. Used for calculating the new frame interpolation speed
     */
    u8 field_0x02;
    u8 current_animation_keyframe;
    u8 current_interpolation_frame;
    /**
     * Also used for face overlay texture
     */
    u8 frame_interpolation_speed;
    /**
     * ASSUMPTION. Number of limbs + "frame interpolation speed" field (0x10 for Carrie)
     */
    u8 number_of_limbs;
    /**
     * model_info flags?
     */
    u8 field_0x07;
    void* current_animation_translation_data_ptr;
    void* current_animation_rotation_data_ptr;
    s32 field_0x10;
} animation_info;

typedef struct {
    animation_info current_anim;
    animation_info previous_anim;
    /**
     * & 1 -> Anim index: 0 = Current anim, 1 = Previous anim.
     * Anything other than the less significant 3 bits --> current anim flags?
     * See the end of animationMgr_animateFrame()
     */
    u8 flags;
    u8 current_animation_switching_time;
    u8 animation_switch_time;
    u8 field_0x2B;
    /**
     * Usually function 0x80022120?
     */
    void (*field_0x2C)(Model*, s32);
} animationMgr;

typedef struct {
    Vec3 translation;
    u16 flags;
} animation_translation_data;

extern void animationInfo_create(animation_info* self, u8 number_of_limbs, u8);
extern void animationInfo_setParams(animation_info* self, void* rotation_data, f32 speed);
extern s32 animationInfo_animateFrame(animation_info* self, Model* model);
extern void animationMgr_create(
    animationMgr* self, u8 number_of_limbs, u8 anim_switch_time, void* param_4, u8 param_5
);

#endif
