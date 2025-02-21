#ifndef SYSTEM_WORK_H
#define SYSTEM_WORK_H

#include "controller.h"
#include "fade.h"
#include "gfx/figure.h"
#include "gfx/color.h"
#include "gfx/misc.h"
#include "actor.h"
#include "math.h"
#include "nisitenma_ichigo.h"
#include "save.h"
#include "cutscene.h"
#include "cutscene_ID.h"
#include "objects/player/player.h"
#include "objects/camera/cameraMgr.h"
#include "objects/cutscene/interactables.h"
#include <ultra64.h>

#define NUM_CHARACTERS 2
/**
 * Originally there were going to be two additional
 * playable characteres: Cornell and Coller.
 *
 * `characterSelect_create` still sets the number of characters to 4,
 * but the `difficulty_and_character_select` overlay has hardcoded checks
 * to prevent more than 2 character slots to be selected.
 */
#define NUM_CHARACTERS_EARLY 4

#define MAP_ASSETS_FILE_ID    sys.map_assets_file_IDs[0]
#define ITEM_ASSETS_FILE_ID   sys.map_assets_file_IDs[1]
#define SKYBOX_ASSETS_FILE_ID sys.map_assets_file_IDs[2]

typedef struct {
    Gfx dlists[5120];
    Mat4f matrices[FIG_ARRAY_MAX];
} sysw_gfx;

typedef struct {
    /**
     * Global Timer (uncapped framerate)
     */
    u32 global_timer_uncapped;
    u32 execution_flags;
    sysw_gfx graphic_buffers[NUM_GRAPHIC_BUFFERS];
    s16 current_graphic_buffer;
    s16 previous_graphic_buffer;
    s16 frameBuffer_index;
    s16 framebuffer_image_pixel_size;
    RGBA background_color;
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
    FadeFlags fade_flags;
    RGBA fade_color;
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
     * See Figure_Update
     */
    s32 field16_0x2402c;
    Mat4f* field17_0x24030;
    u8 field18_0x24034[68];
    Mat4f field19_0x24078;
    union {
        s16 field20_0x240b8_s16;
        f32 field20_0x240b8_f32;
    };
    u32 NisitenmaIchigo_loadedFiles[64];
    u32 NisitenmaIchigo_currentlyDecompressingFiles[64];
    /**
     * Global Timer (Capped Framerate)
     */
    u16 global_timer_capped;
    s16 field24_0x242be;
    u8 field_0x242c0[4];
    Controller controllers[4];
    u8 file_load_array_ID;
    u8 field27_0x242fd[3];
    void* Nisitenma_Ichigo_loaded_files_ptr[255];
    u8 field29_0x246fc[4];
    /**
     * fileLoad*
     */
    void* file_load_array[8];
    /**
     * Perhaps a decompression chunk buffer? Used in `romCopyAndDecompress`
     */
    u8 field31_0x24720[0x1800];
    u8 field_0x25f20[10];
    s16 field32_0x25f2a;
    u8 field33_0x25f2c[512];
    SaveData SaveStruct_gameplay;
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
    Interactable* actor_player_is_currently_interacting_with;
    u32 pull_lever;
    u8 field50_0x26230[4];
    s16 current_PowerUp_level;
    u8 alternate_costume;
    u8 in_first_person_mode;
    s16 nitro_explosion_hit_launch_angle;
    s16 field55_0x2623a;
    f32 nitro_explosion_hit_launch_speed;
    f32 nitro_explosion_hit_launch_Y_velocity;
    s32 player_frozenGrab_timer;
    s16 player_position_log_max;
    s16 player_position_log_current;
    Vec3f player_position_log[30];
    union {
        /**
         * Enemy that is grabbing or froze the player
         */
        Actor* enemy;
        /**
         * Damage dealt to the player while grabbed
         */
        s16 damage;
        /**
         * Misc. animation flags for when grabbed and launched by some enemies (such as the Weretiger)
         */
        u32 grabbed_and_launched_flags;
    } grabbed_misc_vars;
    Actor* enemy_grabbing_player;
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
    Mat4f field_0x263d4;
    RGBA primitive_color;
    s16 map_is_setup;
    u8 field74_0x2641a;
    u8 field75_0x2641b;
    /**
     * [0] = map [1] = pickable_items [2] = skybox_assets
     */
    NIFileID map_assets_file_IDs[3];
    s16 map;
    s16 spawn;
    RGBA map_fade_in_color;
    s16 map_fade_out_time;
    s16 map_fade_in_time;
    /**
     * Always 0
     */
    s16 NOT_ON_MENU;
    /**
     * See the `MenuID` enum for possible values
     */
    s16 current_opened_menu;
    u8 field84_0x26438[4];
    PlayerCharacterID title_demo_character;
    u32 cutscene_ID;
    u32 entrance_cutscene_ID;
    u32 cutscene_flags;
    /**
     * If OR'd with 1, cutscene triggers won't spawn
     *
     * See `cutsceneTrigger_init`
     */
    u32 field89_0x2644c;
} system_work; // Size = 0x26450

/**
 * 0x80363AB8
 * Most likely the actual symbol based on leftover strings from LoD
 */
extern system_work sys;

// Controller macros
#define GET_CONTROLLER(controller_id) sys.controllers[(controller_id)]
#define CONT_BTNS_HELD(controller_id, buttons)                                                     \
    BITS_HAS(GET_CONTROLLER(controller_id).btns_held, (buttons))
#define CONT_BTNS_PRESSED(controller_id, buttons)                                                  \
    BITS_HAS(GET_CONTROLLER(controller_id).btns_pressed, (buttons))
#define CONT_ALL_BTNS_HELD(buttons)                                                                \
    BITS_HAS(                                                                                      \
        ((GET_CONTROLLER(0).btns_held) | (GET_CONTROLLER(1).btns_held) |                           \
         (GET_CONTROLLER(2).btns_held) | (GET_CONTROLLER(3).btns_held)),                           \
        (buttons)                                                                                  \
    )
#define CONT_ALL_BTNS_PRESSED(buttons)                                                             \
    BITS_HAS(                                                                                      \
        ((GET_CONTROLLER(0).btns_pressed) | (GET_CONTROLLER(1).btns_pressed) |                     \
         (GET_CONTROLLER(2).btns_pressed) | (GET_CONTROLLER(3).btns_pressed)),                     \
        (buttons)                                                                                  \
    )

#endif
