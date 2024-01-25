#ifndef ANIMATION_H
#define ANIMATION_H

#include "gfx/model_info.h"

typedef struct {
    u8 flags;
    u8 field_0x01;
    u8 field_0x02; // Animation speed * 16. Used for calculating the new frame
                   // interpolation speed
    u8 current_animation_keyframe;
    u8 current_interpolation_frame;
    u8 frame_interpolation_speed; // Also used for face overlay texture
    u8 number_of_limbs; // ASSUMPTION. Number of limbs + "frame interpolation
                        // speed" field (0x10 for Carrie)
    u8 field_0x07;      // model_info flags?
    void* current_animation_translation_data_ptr;
    void* current_animation_rotation_data_ptr;
    s32 field_0x10;
} animation_info;

typedef struct {
    animation_info current_anim;
    animation_info previous_anim;
    // & 1 -> Anim index: 0 = Current anim, 1 = Previous anim.
    // Anything other than the less significant 3 bits --> current anim flags?
    // See the end of animationMgr_animateFrame()
    u8 flags;
    u8 current_animation_switching_time;
    u8 animation_switch_time;
    u8 field_0x2B;
    void (*field_0x2C)(cv64_model_inf_t*, s32); // Usually function 0x80022120?
} animationMgr;

#endif
