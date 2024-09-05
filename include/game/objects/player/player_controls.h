#ifndef PLAYER_CONTROLS_H
#define PLAYER_CONTROLS_H

#include "controller.h"

typedef struct cv64_player_cont_data {
    cv64_cont_state_t cont;
    cv64_cont_state_t cont_prev_frame;
    s16 joy_ang;
    /**
     * Player's facing angle (yaw)
     */
    s16 player_ang;
    f32 joy_x;
    f32 joy_y;
    f32 player_ang_x;
    f32 player_ang_z;
    /**
     * Current joystick's "held" value. Ranges from `0` (center) to `1` (holding max towards a direction)
     */
    f32 joy_magn;
    /**
     * Normalized value of the joystick's X-axis: `0` (center), `-1` (full left), `+1` (full right)
     */
    f32 joy_norm_x;
    /**
     * Normalized value of the joystick's Y-axis: `0` (center), `-1` (full up), `+1` (full down)
     */
    f32 joy_norm_y;
    f32 player_ang_norm_x;
    f32 player_ang_norm_z;
    /**
     * Difference between the current and previous frame of `joy_norm_x`
     */
    f32 joy_norm_x_delta;
    /**
     * Difference between the current and previous frame of `joy_norm_y`
     */
    f32 joy_norm_y_delta;
    /**
     * Sum of `player_ang_norm_x` over time
     */
    f32 player_ang_norm_x_sum;
    /**
     * Sum of `player_ang_norm_y` over time
     */
    f32 player_ang_norm_z_sum;
} cv64_player_cont_data_t;

extern cv64_player_cont_data_t playerControllerData;
extern cv64_player_cont_data_t D_800D7B00_A8DD0; // Used by `func_800217AC_223AC`

typedef struct JoystickAndPlayerAngleListEntry_t {
    f32 joy_norm_x;
    f32 joy_norm_y;
    f32 player_ang_norm_x;
    f32 player_ang_norm_z;
} JoystickAndPlayerAngleListEntry_t;

typedef struct JoystickAndPlayerAngleList_t {
    JoystickAndPlayerAngleListEntry_t list[15];
} JoystickAndPlayerAngleList_t;

extern s32 JoystickAndPlayerAngleList_index;
extern JoystickAndPlayerAngleList_t JoystickAndPlayerAngleList;

extern void func_800217AC_223AC();
extern void updatePlayerControls();
extern void JoystickAndPlayerAngleList_pushCurrentDataAtIndex(
    JoystickAndPlayerAngleList_t* self, s32 max_index, s32* index
);

#endif
