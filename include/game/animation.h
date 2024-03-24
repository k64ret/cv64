#ifndef ANIMATION_H
#define ANIMATION_H

#include "gfx/model_info.h"

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
    void (*field_0x2C)(cv64_model_inf_t*, s32);
} animationMgr;

extern void animationInfo_create(animation_info* self, u8 number_of_limbs, u8);
extern void animationInfo_setParams(animation_info* self, void* rotation_data, f32 speed);
extern s32 func_8000B774(animation_info* self, cv64_model_inf_t* model);

#endif
