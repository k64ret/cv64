#ifndef PLAYER_CONTROLS_H
#define PLAYER_CONTROLS_H

#include "controller.h"

typedef struct playerControllerData_t {
    cv64_controller_state_t controller;
    cv64_controller_state_t controller_previous_frame;
    s16 joystick_angle;
    s16 player_angle; // Player's facing angle (yaw)
    f32 joystick_x;
    f32 joystick_y;
    f32 player_angle_x;
    f32 player_angle_z;
    f32 joystick_magnitude; // Current "held" value. Ranges from 0 (center) to 1 (holding max towards a direction)
    f32 joystick_normalized_x; // Joystick X: 0 (center), -1 (full left), +1 (full right)
    f32 joystick_normalized_y; // Joystick Y: 0 (center), -1 (full up), +1 (full down)
    f32 player_angle_normalized_x;
    f32 player_angle_normalized_z;
    f32 joystick_normalized_x_delta; // Difference between the "joystic_normalized_x" value between the current and previous frame
    f32 joystick_normalized_y_delta; // Difference between the "joystic_normalized_y" value between the current and previous frame
    f32 player_angle_normalized_x_accumulative; // Sum of "player_angle_normalized_x" overtime
    f32 player_angle_normalized_z_accumulative; // Sum of "player_angle_normalized_z" overtime
} playerControllerData_t;

extern playerControllerData_t playerControllerData;
extern playerControllerData_t D_800D7B00_A8DD0; // Used by `func_800217AC_223AC`

typedef struct JoystickAndPlayerAngleListEntry_t {
    f32 joystick_normalized_x;
    f32 joystick_normalized_y;
    f32 player_angle_normalized_x;
    f32 player_angle_normalized_z;
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
