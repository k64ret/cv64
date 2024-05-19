#ifndef SYSTEM_WORK_H
#define SYSTEM_WORK_H

#include "controller.h"
#include "fade.h"
#include "gfx/color.h"
#include "actor.h"
#include "math.h"
#include "save.h"
#include "cutscene.h"
#include "cutscene_ID.h"
#include "objects/player/player.h"
#include "objects/camera/cameraMgr.h"
#include "objects/cutscene/interactuables.h"
#include <ultra64.h>

#define MAP_ASSETS_FILE_ID    sys.map_assets_file_IDs[0]
#define ITEM_ASSETS_FILE_ID   sys.map_assets_file_IDs[1]
#define SKYBOX_ASSETS_FILE_ID sys.map_assets_file_IDs[2]

typedef union {
    s16 field_s16;
    f32 field_f32;
} unk_union_1;

typedef union {
    void* field_voidptr;
    cv64_actor_t* enemy;
    s16 damage;
} being_grabbed_frozen_related_union;

typedef struct {
    Gfx dlists[5120];
    Matrix44F matrices[FIG_ARRAY_MAX];
} sysw_gfx;

typedef struct {
    /**
     * Global Timer (uncapped framerate)
     */
    u32 global_timer_uncapped;
    u32 execution_flags;
    sysw_gfx field2_0x8[2];
    s16 current_dlist_buffer;
    s16 previous_dlist_buffer;
    s16 frameBuffer_index;
    s16 framebuffer_image_pixel_size;
    cv64_rgba_t background_color;
    s16 should_setup_background_color;
    s16 should_setup_Z_buffer;
    /**
     * Max delay before most of the code can be executed.
     * Used for framerate timing.
     * 0 = 60fps, 1 = 30fps. Update rate.
     */
    s16 code_execution_max_delay;
    /**
     * Current delay before most of the code can be executed.
     * Used for framerate timing.
     */
    s16 code_execution_delay_timer;
    s16 should_end_master_display_list;
    s16 fade_flags;
    cv64_rgba_t fade_color;
    /**
     * Likely called "disp_fade_cnt", according to leftover strings in LoD
     */
    u16 fade_current_time;
    /**
     * Likely called "disp_fade_time", according to leftover strings in LoD
     */
    u16 fade_max_time;
    u16 fog_distance_near;
    u16 fog_distance_far;
    /**
     * See func_8000C740
     */
    s32 field16_0x2402c;
    Matrix44F* field17_0x24030;
    u8 field18_0x24034[68];
    Matrix44F field19_0x24078;
    unk_union_1 field20_0x240b8;
    u32 NisitenmaIchigo_loadedFiles[64];
    u32 NisitenmaIchigo_currentlyDecompressingFiles[64];
    /**
     * Global Timer (Capped Framerate)
     */
    u16 global_timer_capped;
    u8 field24_0x242be[6];
    cv64_controller_state_t controllers[4];
    u8 file_load_array_ID;
    u8 field27_0x242fd[3];
    void* Nisitenma_Ichigo_loaded_files_ptr[255];
    u8 field29_0x246fc[4];
    /**
     * fileLoad*
     */
    void* file_load_array[8];
    u8 field31_0x24720[6154];
    s16 field32_0x25f2a;
    u8 field33_0x25f2c[512];
    cv64_save_state_t SaveStruct_gameplay;
    /**
     * Could also be "EXECUTE_GAMEPLAY"
     */
    s16 MENU_IS_CLOSED;
    s16 FREEZE_GAMEPLAY;
    /**
     * 0 = EASY, 1 = NORMAL, 2 = HARD
     */
    u16 save_difficulty;
    s16 FREEZE_CUTSCENE;
    s16 FREEZE_MAP_OBJECTS;
    s16 FREEZE_PLAYER;
    s16 FREEZE_mapSetup;
    s16 FREEZE_ENEMIES;
    s16 FREEZE_EFFECTS;
    s16 field44_0x2621e;
    s16 FREEZE_gameplayMenuMgr;
    s16 contPak_file_no;
    Player* ptr_PlayerObject;
    interactuables* actor_player_is_currently_interacting_with;
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
    cv64_actor_t* enemy_grabbing_player;
    u16 angle_of_player_being_grabbed_by_enemy;
    u16 player_grabbed_by_vampire_timer_or_frozen;
    s16 current_boss_actor_ID;
    u8 field67_0x263c2[6];
    cameraMgr* ptr_cameraMgr;
    /**
     * playerCameraController*
     */
    void* ptr_playerCameraController;
    u8 field70_0x263d0[4];
    Matrix44F another_viewing_matrix;
    cv64_rgba_t primitive_color;
    s16 map_is_setup;
    u8 field74_0x2641a;
    u8 field75_0x2641b;
    /**
     * [0] = map [1] = pickable_items [2] = skybox_assets
     */
    s32 map_assets_file_IDs[3];
    s16 map;
    s16 spawn;
    cv64_rgba_t map_fade_in_color;
    s16 map_fade_out_time;
    s16 map_fade_in_time;
    /**
     * Always 0
     */
    s16 NOT_ON_MENU;
    /**
     * NOT_ON_MENU = 0, PAUSE = 9, RENON_SHOP = 10, GAME_OVER = 14
     */
    s16 current_opened_menu;
    u8 field84_0x26438[4];
    /**
     * 0 = REINHARDT, 1 = CARRIE
     */
    u32 titleDemoCharacter;
    u32 cutscene_ID;
    u32 entrance_cutscene_ID;
    u32 cutscene_flags;
    u32 field89_0x2644c;
} system_work; // Size = 0x26450

/**
 * 0x80363AB8
 * Most likely the actual symbol based on leftover strings from LoD
 */
extern system_work sys;

#endif
