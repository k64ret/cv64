#ifndef SYSTEM_WORK_H
#define SYSTEM_WORK_H

#include "controller.h"
#include "fade.h"
#include "gfx/color.h"
#include "math.h"
#include "save.h"
#include <ultra64.h>

typedef union {
    s16 field_s16;
    f32 field_f32;
} unk_union_1;

typedef union {
    void* field_voidptr;
    void* enemy; // Actor*
    s16 damage;
} being_grabbed_frozen_related_union;

typedef struct {
    Gfx dlists[5120];
    mf matrices[512];
} sysw_gfx;

typedef struct {
    u32 game_loop_time;
    u32 execution_flags;
    sysw_gfx field2_0x8[2]; /* Double check */
    s16 current_dlist_buffer;
    s16 previous_dlist_buffer;
    s16 frameBuffer_index;
    s16 framebuffer_image_pixel_size;
    cv64_rgba_t background_color;
    s16 should_setup_background_color;
    s16 should_setup_Z_buffer;
    s16 code_execution_max_delay;   /* Max delay before most of the code can be
                                       executed. Used for framerate timing. 0 =
                                       60fps, 1 = 30fps. Update rate. */
    s16 code_execution_delay_timer; /* Current delay before most of the code can
                                       be executed. Used for framerate timing.
                                     */
    s16 should_end_master_display_list;
    s16 fade_flags;
    cv64_rgba_t fade_color;
    u16 fade_current_time; // Likely called "disp_fade_cnt", according to
                           // leftover strings in LoD
    u16 fade_max_time; // Likely called "disp_fade_time", according to leftover
                       // strings in LoD
    u16 fog_distance_near;
    u16 fog_distance_far;
    s32 field16_0x2402c; /* See func_8000C740 */
    mf* field17_0x24030;
    u8 field18_0x24034[68];
    MtxF field19_0x24078;
    unk_union_1 field20_0x240b8;
    u32 field21_0x240bc[64];  // Nisitenma_Ichigo_loaded_files
    u32 field22_0x241bc[64];  // Also Nisitenma_Ichigo_loaded_files?
    u16 code_execution_timer; /* Increments every time the game executes most of
                                 its code and a frame advances. Updates at
                                 30fps. */
    u8 field24_0x242be[6];
    cv64_controller_state_t controllers[4];
    u8 file_load_array_ID;
    u8 field27_0x242fd[3];
    void* Nisitenma_Ichigo_loaded_files_ptr[255];
    u8 field29_0x246fc[4];
    void* file_load_array[8]; // fileLoad*
    u8 field31_0x24720[6154];
    s16 field32_0x25f2a;
    u8 field33_0x25f2c[512];
    cv64_save_state_t SaveStruct_gameplay;
    s16 MENU_IS_CLOSED; /* Could also be "EXECUTE_GAMEPLAY" */
    s16 FREEZE_GAMEPLAY;
    u16 save_difficulty; // 0 = EASY, 1 = NORMAL, 2 = HARD
    s16 FREEZE_CUTSCENE;
    s16 FREEZE_MAP_OBJECTS;
    s16 FREEZE_PLAYER;
    s16 FREEZE_mapSetup;
    s16 FREEZE_ENEMIES;
    s16 FREEZE_EFFECTS;
    s16 field44_0x2621e;
    s16 FREEZE_gameplayMenuMgr;
    s16 contPak_file_no;
    void* ptr_PlayerModule;                           // Player*
    void* actor_player_is_currently_interacting_with; // interactuables*
    u32 pull_lever;
    u8 field50_0x26230[4];
    u16 current_PowerUp_level;
    u8 alternate_costume;
    u8 in_first_person_mode;
    s16 field54_0x26238;
    s16 field55_0x2623a;
    f32 field56_0x2623c;
    f32 field57_0x26240;
    s32 field58_0x26244;
    s16 player_position_log_max;
    s16 player_position_log_current;
    vec3f player_position_log[30];
    being_grabbed_frozen_related_union field62_0x263b4;
    void* enemy_grabbing_player; // Actor*
    u16 angle_of_player_being_grabbed_by_enemy;
    u16 player_grabbed_by_vampire_timer_or_frozen;
    s16 current_boss_actor_ID;
    u8 field67_0x263c2[6];
    void* ptr_cameraMgr;              // cameraMgr*
    void* ptr_playerCameraController; // playerCameraController*
    u8 field70_0x263d0[4];
    MtxF another_viewing_matrix;
    cv64_rgba_t primitive_color;
    s16 map_is_setup;
    u8 field74_0x2641a;
    u8 field75_0x2641b;
    s32 map_assets_file_IDs[3]; // [0] = map, [1] = pickable_items, [2] =
                                // skybox_assets
    s16 map_ID;
    s16 map_entrance_ID;
    cv64_rgba_t map_fade_in_color;
    s16 map_fade_out_time;
    s16 map_fade_in_time;
    s16 NOT_ON_MENU;         /* Always 0 */
    s16 current_opened_menu; // NOT_ON_MENU = 0, PAUSE = 9, RENON_SHOP = 10,
                             // GAME_OVER = 14
    u8 field84_0x26438[4];
    u32 titleDemoCharacter; // 0 = REINHARDT, 1 = CARRIE
    s32 cutscene_ID;
    s32 entrance_cutscene_ID;
    u32 cutscene_flags;
    u32 field89_0x2644c;
} system_work; // Size = 0x26450

extern system_work sys; // 0x80363AB8. Most likely the actual symbol based on
                        // leftover strings from LoD

#endif
