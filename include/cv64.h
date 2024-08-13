#ifndef CV64_H
#define CV64_H

#include "gfx/model_info.h"
#include "math.h"
#include <ultra64.h>

// Unknown types
typedef u8 UNK8;
typedef u16 UNK16;
typedef s32 UNK32;
typedef void* UNKPTR;

#define CV64_BIT(num) (1 << (num))
/**
 * Apply `mask` on top of `value`.
 */
#define BITS_MASK(value, mask) ((value) & (mask))
/**
 * Apply `mask` on top of `value` and assign result to `value`.
 */
#define BITS_ASSIGN_MASK(value, mask) ((value) &= (mask))
/**
 * Check if `bits` is set in `value`.
 */
#define BITS_HAS(value, bits) BITS_MASK(value, bits)
/**
 * Check if `bits` is set in `value`.
 */
#define BITS_NOT_HAS(value, bits) !BITS_HAS(value, bits)
/**
 * Set `bits` in `value`.
 */
#define BITS_SET(value, bits) ((value) |= (bits))
/**
 * Unset `bits` in `value`.
 */
#define BITS_UNSET(value, bits) ((value) &= ~(bits))

typedef u8 Addr[];

extern u32 D_80092F50;
extern Gfx* gDisplayListHead; // 0x800B49E0
extern u32 map_misc_event_flags;
extern u8 PLAYER_HAS_MAX_HEALTH;
extern u32 map_text_segment_address[28]; // 0x8016D008

typedef enum cv64_moon_visibility {
    MOON_VISIBILITY_DAY   = 0, // Moon is invisible
    MOON_VISIBILITY_NIGHT = 1, // Moon is visible
    /**
     * New moons have been observed to happen during the following situations. During these times,
     * the moon is not supposed to be visible:
     * - From 18:00 to 23:59 on the 7th day of the week, but only if the current week number is even.
     * - When spawning in Forest of Silence from 00:00 to 06:00 of the 1st day of the week,
     *   but only if the current week number is even.
     */
    MOON_VISIBILITY_NEW_MOON = 2 // Moon is invisible
} cv64_moon_visibility_t;

/**
 * Most of the time, these two variables are accessed as two separate `s16`.
 * However, some code accesses both variables at the same time, as an `s32`,
 * hence why we have this as a union.
 */
typedef union {
    struct {
        s16 moonVisibility;
        /**
         * Don't update `moonVisibility` by calling the `updateMoonVisibility` function,
         * so that other code can update it on its own, or not update it at all.
         */
        s16 dontUpdateMoonVisibility;
    };
    s32 integer;
} union_moonVisibilityVars;

extern union_moonVisibilityVars moonVisibilityVars;

typedef enum cv64_menu_id {
    MENU_ID_NOT_ON_MENU = 0,
    MENU_ID_PAUSE       = 9,
    MENU_ID_RENON_SHOP  = 10,
    MENU_ID_GAME_OVER   = 14
} cv64_menu_id_t;

extern void end_master_display_list();
extern s32 menuButton_selectNextOption(s32* option, s16* param_2, s16 number_of_options);
extern u32 NisitenmaIchigo_checkAndStoreLoadedFile(u32 file_ID);
extern void func_800010A0_1CA0();
extern void func_8001248C_1308C();
extern void func_8000C6D0();
extern void updateGameSound();
extern void figure_update();
extern void drawFog();
extern void func_80005658();
extern u32 getMapEventFlagID(s16 stage_ID);
s32 func_8001A250_1AE50(s32* arg0, u16* arg1, s16 arg2);
extern void func_80066400(s32);
extern void* NisitenmaIchigoFiles_segmentToVirtual(u32 segment_address, s32 file_ID);

#define NPTR             0
#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0])) // Get number of elements in the array
#define ARRAY_START(arr) &arr[0]                             // Get start address of array
#define ARRAY_END(arr)   &arr[ARRAY_COUNT(arr)]              // Get end address of array

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

// Text IDs for Castle Center (Main)
#define CASTLE_CENTER_MAIN_WALL_INFO           2
#define CASTLE_CENTER_MAIN_TAKE_MANDRAGORA     10
#define CASTLE_CENTER_MAIN_OBTAINED_MANDRAGORA 11
#define CASTLE_CENTER_MAIN_MANDRAGORA_INFO     13
#define CASTLE_CENTER_MAIN_SET_NITRO           14
#define CASTLE_CENTER_MAIN_SET_MANDRAGORA      15
#define CASTLE_CENTER_MAIN_ITEM_ALREADY_SET    16
#define CASTLE_CENTER_MAIN_NITRO_SET           17
#define CASTLE_CENTER_MAIN_MANDRAGORA_SET      18
#define CASTLE_CENTER_MAIN_READY_FOR_BLASTING  19
// Text IDs for Castle Center (Bottom Elevator)
#define CASTLE_CENTER_1F_ACTIVATE_ELEVATOR          1
#define CASTLE_CENTER_1F_ELEVATOR_ACTIVATED         2
#define CASTLE_CENTER_1F_CANT_ACTIVATE_ELEVATOR_YET 3
#define CASTLE_CENTER_1F_ELEVATOR_ALREADY_USED      4
#define CASTLE_CENTER_1F_ELEVATOR_NOT_MOVING        5
#define CASTLE_CENTER_1F_DISPOSAL_WITH_NITRO        7
#define CASTLE_CENTER_1F_DISPOSAL_WITHOUT_NITRO     8
// Text IDs for Castle Center (Gears)
#define CASTLE_CENTER_2F_DISPOSAL_WITH_NITRO    2
#define CASTLE_CENTER_2F_DISPOSAL_WITHOUT_NITRO 3
// Text IDs for Castle Center (Friendly lizard-man)
#define CASTLE_CENTER_3F_WALL_INFO              0
#define CASTLE_CENTER_3F_DISPOSAL_WITH_NITRO    3
#define CASTLE_CENTER_3F_DISPOSAL_WITHOUT_NITRO 4
#define CASTLE_CENTER_3F_NITRO_INFO             5
#define CASTLE_CENTER_3F_TAKE_NITRO             6
#define CASTLE_CENTER_3F_NITRO_WARNING          7
#define CASTLE_CENTER_3F_SET_NITRO              12
#define CASTLE_CENTER_3F_SET_MANDRAGORA         13
#define CASTLE_CENTER_3F_ITEM_ALREADY_SET       14
#define CASTLE_CENTER_3F_NITRO_SET              15
#define CASTLE_CENTER_3F_MANDRAGORA_SET         16
#define CASTLE_CENTER_3F_READY_FOR_BLASTING     17
// Text IDs for Castle Center (Library)
#define CASTLE_CENTER_4F_LIBRARY_PUZZLE_DESCRIPTION 7
#define CASTLE_CENTER_4F_LIBRARY_PUZZLE_GOLD_PIECE  8
// Text IDs for Castle Center
#define CASTLE_CENTER_TRY_HAVING_MANDRAGORA_AND_NITRO_SAME_TIME 12

/**
 * Obtain the un-mapped address of data from a Nisitenma-Ichigo file
 * This is needed if data is trying to be accessed when said data is not mapped by the TLB
 * (which usually happens with data within overlays)
 */
#define GET_UNMAPPED_ADDRESS(file_ID, data_ptr)                                                    \
    (u32) sys.Nisitenma_Ichigo_loaded_files_ptr[file_ID] + BITS_MASK((u32) data_ptr, 0xFFFFFF)

/**
 * Obtain the VRAM address of the message pool inside a map assets file, given its segment address
 * in the `map_text_segment_address` array
 */
#define GET_MAP_MESSAGE_POOL_PTR()                                                                 \
    (*NisitenmaIchigoFiles_segmentToVirtual)(                                                      \
        map_text_segment_address[sys.SaveStruct_gameplay.map], MAP_ASSETS_FILE_ID                  \
    )

extern const u32 MENU_RED_BACKGROUND_DL;
#define NI_ASSETS_MENU_BUFFER_SIZE 0x30000

// Nisitenma-Ichigo file IDs
#define NI_ASSETS_01                           0x01
#define NI_ASSETS_DEBUG_FONT                   0x02
#define NI_ASSETS_REINHARDT                    0x03
#define NI_ASSETS_REINHARDT_ALT_COSTUME        0x04
#define NI_ASSETS_REINHARDT_WHIP               0x05
#define NI_ASSETS_CARRIE                       0x06
#define NI_ASSETS_CARRIE_ALT_COSTUME           0x07
#define NI_ASSETS_ENEMY_TARGET_GRAPHIC         0x08
#define NI_ASSETS_UNUSED_3_HEAD_WOLF           0x09
#define NI_ASSETS_CERBERUS                     0x0A
#define NI_ASSETS_WHITE_DRAGON                 0x0B
#define NI_ASSETS_GARDENER                     0x0C
#define NI_ASSETS_STONE_DOG                    0x0D
#define NI_ASSETS_BEHEMOTH                     0x0E
#define NI_ASSETS_WERETIGER                    0x0F
#define NI_ASSETS_WEREWOLF                     0x10
#define NI_ASSETS_HELL_KNIGHT                  0x11
#define NI_ASSETS_GHOST                        0x12
#define NI_ASSETS_ICEMAN_PUDDLE                0x13
#define NI_ASSETS_MUDMAN_LAVAMAN               0x14
#define NI_ASSETS_BLOOD_JELLY                  0x15
#define NI_ASSETS_ICEMAN                       0x16
#define NI_ASSETS_FIRE_BAT                     0x17
#define NI_ASSETS_FLYING_SKULL                 0x18
#define NI_ASSETS_BAT                          0x19
#define NI_ASSETS_MEDUSA_HEAD                  0x1A
#define NI_ASSETS_PILLAR_OF_BONES              0x1B
#define NI_ASSETS_UNDEAD_MAIDEN                0x1C
#define NI_ASSETS_VAMPIRE_MAID                 0x1D
#define NI_ASSETS_VAMPIRE_VILLAGER             0x1E
#define NI_ASSETS_VAMPIRE_BUTLER               0x1F
#define NI_ASSETS_VINCENT                      0x20
#define NI_ASSETS_WEREJAGUAR                   0x21
#define NI_ASSETS_SPIDER_CENTAUR               0x22
#define NI_ASSETS_LIZARD_MAN                   0x23
#define NI_ASSETS_SKELETON_WARRIOR             0x24
#define NI_ASSETS_GLASS_KNIGHT                 0x25
#define NI_ASSETS_KING_SKELETON                0x26
#define NI_ASSETS_SKELETON_BIKER               0x27
#define NI_ASSETS_TRUE_DRACULA                 0x28
#define NI_ASSETS_MALUS                        0x29
#define NI_ASSETS_MALUS_HORSE                  0x2A
#define NI_ASSETS_DEMON_DRACULA                0x2B
#define NI_ASSETS_VAMPIRE_GILDRE               0x2C
#define NI_ASSETS_RENON                        0x2D
#define NI_ASSETS_RENON_DEMON                  0x2E
#define NI_ASSETS_DEATH                        0x2F
#define NI_ASSETS_DEMONIC_FISH                 0x30
#define NI_ASSETS_ROSA                         0x31
#define NI_ASSETS_32                           0x32
#define NI_ASSETS_CAMILLA                      0x33
#define NI_ASSETS_ACTRIESE                     0x34
#define NI_ASSETS_CAMILLA_FIGHT                0x35
#define NI_ASSETS_36                           0x36
#define NI_ASSETS_37                           0x37
#define NI_ASSETS_38                           0x38
#define NI_ASSETS_39                           0x39
#define NI_ASSETS_3A                           0x3A
#define NI_ASSETS_3B                           0x3B
#define NI_ASSETS_3C                           0x3C
#define NI_MAP_FOREST_OF_SILENCE               0x3D
#define NI_MAP_CASTLE_WALL_TOWERS              0x3E
#define NI_MAP_CASTLE_WALL_MAIN                0x3F
#define NI_MAP_VILLA_YARD                      0x40
#define NI_MAP_VILLA_FOYER                     0x41
#define NI_MAP_VILLA_HALLWAY                   0x42
#define NI_MAP_VILLA_MAZE_GARDEN               0x43
#define NI_MAP_TUNNEL                          0x44
#define NI_MAP_UNDERGROUND_WATERWAY            0x45
#define NI_MAP_CASTLE_CENTER_MAIN              0x46
#define NI_MAP_CASTLE_CENTER_BOTTOM_ELEVATOR   0x47
#define NI_MAP_CASTLE_CENTER_LIZARD            0x48
#define NI_MAP_CASTLE_CENTER_BROKEN_STAIRCASE  0x49
#define NI_MAP_CASTLE_CENTER_LIBRARY           0x4A
#define NI_MAP_CASTLE_CENTER_NITRO_ROOM        0x4B
#define NI_MAP_CASTLE_CENTER_TOP_ELEVATOR_ROOM 0x4C
#define NI_MAP_TOWER_OF_EXECUTION              0x4D
#define NI_MAP_TOWER_OF_SORCERY                0x4E
#define NI_MAP_TOWER_OF_SCIENCE                0x4F
#define NI_MAP_DUEL_TOWER                      0x50
#define NI_MAP_CASTLE_KEEP_EXTERIOR            0x51
#define NI_MAP_CASTLE_KEEP                     0x52
#define NI_MAP_INTRO_NARRATION                 0x53
#define NI_MAP_CLOCK_TOWER                     0x54
#define NI_MAP_DRACULA_DESERT                  0x55
#define NI_MAP_ROSE_ACTRICE_MEET_ROOM          0x56
#define NI_MAP_VILLA_CRYPT_AREA                0x57
#define NI_MAP_ROOM_OF_CLOCKS                  0x58
#define NI_MAP_ENDING                          0x59
#define NI_ASSETS_PICKABLE_ITEM_ASSETS         0x5A
#define NI_ASSETS_SKYBOX                       0x5B
#define NI_MAP_TEST_GRID                       0x5C
#define NI_ASSETS_KONAMI_AND_KCEK_LOGOS        0x5D
#define NI_ASSETS_SCROLL                       0x5E
#define NI_ASSETS_TITLE                        0x5F
#define NI_ASSETS_MENU                         0x60
#define NI_ASSETS_NECRONOMICON                 0x61
#define NI_ASSETS_CHARACTER_SELECTION_SCREEN   0x62
#define NI_ASSETS_GAMEPLAY_HUD                 0x63
#define NI_ASSETS_GAME_OVER                    0x64
#define NI_ASSETS_FILE_SELECT                  0x65
#define NI_ASSETS_CONTROLLER_BUTTONS           0x66
#define NI_ASSETS_RENON_BRIEFCASE              0x67
#define NI_ASSETS_FILM_REEL_CUTSCENE_EFFECT    0x68
#define NI_ASSETS_CUTSCENE_01                  0x69
#define NI_ASSETS_CUTSCENE_02                  0x6A
#define NI_ASSETS_CUTSCENE_2B                  0x6B
#define NI_ASSETS_CUTSCENE_2C                  0x6C
#define NI_ASSETS_CUTSCENE_2E                  0x6D
#define NI_ASSETS_CUTSCENE_3F                  0x6E
#define NI_ASSETS_CUTSCENE_2D                  0x6F
#define NI_ASSETS_CUTSCENE_0A                  0x70
#define NI_ASSETS_SMILEY_FACE                  0x71
#define NI_OVL_CERBERUS                        0x72
#define NI_OVL_WHITE_DRAGON                    0x73
#define NI_OVL_GARDENER                        0x74
#define NI_OVL_STONE_DOG                       0x75
#define NI_OVL_MALUS                           0x76
#define NI_OVL_BEHEMOTH                        0x77
#define NI_OVL_WERETIGER                       0x78
#define NI_OVL_WEREWOLF                        0x79
#define NI_OVL_HELL_KNIGHT                     0x7A
#define NI_OVL_GHOST                           0x7B
#define NI_OVL_ICEMAN                          0x7C
#define NI_OVL_ICEMAN_ASSETS_LOADER            0x7D
#define NI_OVL_7E                              0x7E
#define NI_OVL_FLYING_SKULL                    0x7F
#define NI_OVL_BAT                             0x80
#define NI_OVL_MEDUSA_HEAD                     0x81
#define NI_OVL_PILLAR_OF_BONES                 0x82
#define NI_OVL_VAMPIRES                        0x83
#define NI_OVL_VINCENT                         0x84
#define NI_OVL_85                              0x85
#define NI_OVL_86                              0x86
#define NI_OVL_87                              0x87
#define NI_OVL_88                              0x88
#define NI_OVL_89                              0x89
#define NI_OVL_SPIDER_CENTAUR                  0x8A
#define NI_OVL_LIZARD_MAN                      0x8B
#define NI_OVL_SKELETON_WARRIOR                0x8C
#define NI_OVL_KING_SKELETON                   0x8D
#define NI_OVL_SKELETON_BIKER                  0x8E
#define NI_OVL_TRUE_DRACULA                    0x8F
#define NI_OVL_90                              0x90
#define NI_OVL_91                              0x91
#define NI_OVL_MALUS_CUTSCENE                  0x92
#define NI_OVL_MALUS_HORSE                     0x93
#define NI_OVL_DEMON_DRACULA                   0x94
#define NI_OVL_DEMON_DRACULA_ASSETS_LOADER     0x95
#define NI_OVL_96                              0x96
#define NI_OVL_97                              0x97
#define NI_OVL_VAMPIRE_GILDRE                  0x98
#define NI_OVL_99                              0x99
#define NI_OVL_RENON_DEMON                     0x9A
#define NI_OVL_DEATH                           0x9B
#define NI_OVL_9C                              0x9C
#define NI_OVL_ROSA                            0x9D
#define NI_OVL_CAMILLA                         0x9E
#define NI_OVL_ACTRISE                         0x9F
#define NI_OVL_A0                              0xA0
#define NI_OVL_A1                              0xA1
#define NI_OVL_A2                              0xA2
#define NI_OVL_A3                              0xA3
#define NI_OVL_A4                              0xA4
#define NI_OVL_HELL_KNIGHT_STATIC              0xA5
#define NI_OVL_A6                              0xA6
#define NI_OVL_SCROLL                          0xA7
#define NI_OVL_A8                              0xA8
#define NI_OVL_GAMENOTE_DELETE_MGR             0xA9
#define NI_OVL_TITLE_SCREEN                    0xAA
#define NI_OVL_AB                              0xAB
#define NI_OVL_AC                              0xAC
#define NI_OVL_TITLE_DEMO                      0xAD
#define NI_OVL_CREDITSMGR                      0xAE
#define NI_OVL_PAUSE_MENU                      0xAF
#define NI_OVL_CHARACTER_SELECT                0xB0
#define NI_OVL_GAME_OVER                       0xB1
#define NI_OVL_SAVE_GAME_RESULTS               0xB2
#define NI_OVL_B3                              0xB3
#define NI_OVL_SAVE_GAME                       0xB4
#define NI_OVL_TEXTBOX_ADVANCE_ARROW           0xB5
#define NI_OVL_BUTTON_CONFIG_OPTION_MENU       0xB6
#define NI_OVL_ENTRANCE_MAP_NAME_DISPLAY       0xB7
#define NI_OVL_CONTRACTMGR                     0xB8
#define NI_OVL_RENONS_BRIEFCASE                0xB9
#define NI_OVL_BA                              0xBA
#define NI_OVL_EASY_MODE_ENDING_MSG            0xBB
#define NI_OVL_BC                              0xBC
#define NI_OVL_NITRO_MANDRAGORA_DISPLAY        0xBD
#define NI_OVL_BE                              0xBE
#define NI_OVL_BF                              0xBF
#define NI_OVL_C0                              0xC0
#define NI_OVL_C1                              0xC1
#define NI_OVL_C2                              0xC2
#define NI_OVL_FILM_REEL_CUTSCENE_EFFECT       0xC3
#define NI_OVL_CUTSCENE_01                     0xC4
#define NI_OVL_CUTSCENE_03                     0xC5
#define NI_OVL_CUTSCENE_04                     0xC6
#define NI_OVL_CUTSCENE_05                     0xC7
#define NI_OVL_CUTSCENE_06                     0xC8
#define NI_OVL_CUTSCENE_07                     0xC9
#define NI_OVL_CUTSCENE_08                     0xCA
#define NI_OVL_CUTSCENE_09                     0xCB
#define NI_OVL_CUTSCENE_0A                     0xCC
#define NI_OVL_CUTSCENE_0B                     0xCD
#define NI_OVL_CUTSCENE_0C                     0xCE
#define NI_OVL_CUTSCENE_0D                     0xCF
#define NI_OVL_CUTSCENE_0E                     0xD0
#define NI_OVL_CUTSCENE_0F                     0xD1
#define NI_OVL_CUTSCENE_10                     0xD2
#define NI_OVL_CUTSCENE_11                     0xD3
#define NI_OVL_CUTSCENE_12                     0xD4
#define NI_OVL_CUTSCENE_13                     0xD5
#define NI_OVL_CUTSCENE_14                     0xD6
#define NI_OVL_CUTSCENE_15                     0xD7
#define NI_OVL_CUTSCENE_16                     0xD8
#define NI_OVL_CUTSCENE_17                     0xD9
#define NI_OVL_CUTSCENE_18                     0xDA
#define NI_OVL_CUTSCENE_19                     0xDB
#define NI_OVL_CUTSCENE_1A                     0xDC
#define NI_OVL_CUTSCENE_1B                     0xDD
#define NI_OVL_CUTSCENE_1C                     0xDE
#define NI_OVL_CUTSCENE_1E                     0xDF
#define NI_OVL_CUTSCENE_1F                     0xE0
#define NI_OVL_CUTSCENE_21                     0xE1
#define NI_OVL_CUTSCENE_22                     0xE2
#define NI_OVL_CUTSCENE_23                     0xE3
#define NI_OVL_CUTSCENE_24                     0xE4
#define NI_OVL_CUTSCENE_25                     0xE5
#define NI_OVL_CUTSCENE_26                     0xE6
#define NI_OVL_CUTSCENE_27                     0xE7
#define NI_OVL_CUTSCENE_28                     0xE8
#define NI_OVL_CUTSCENE_29                     0xE9
#define NI_OVL_CUTSCENE_2A                     0xEA
#define NI_OVL_CUTSCENE_2B                     0xEB
#define NI_OVL_CUTSCENE_2C                     0xEC
#define NI_OVL_CUTSCENE_2D                     0xED
#define NI_OVL_CUTSCENE_2E                     0xEE
#define NI_OVL_CUTSCENE_32                     0xEF
#define NI_OVL_CUTSCENE_33                     0xF0
#define NI_OVL_CUTSCENE_34                     0xF1
#define NI_OVL_CUTSCENE_35                     0xF2
#define NI_OVL_CUTSCENE_3C                     0xF3
#define NI_OVL_CUTSCENE_3D                     0xF4
#define NI_OVL_CUTSCENE_3E                     0xF5
#define NI_OVL_CUTSCENE_3F                     0xF6
#define NI_OVL_CUTSCENE_44                     0xF7
#define NI_OVL_CUTSCENE_45                     0xF8
#define NI_OVL_CUTSCENE_52                     0xF9
#define NI_OVL_CUTSCENE_54                     0xFA
#define NI_OVL_CUTSCENE_55                     0xFB
#define NI_OVL_CUTSCENE_56                     0xFC
#define NI_OVL_CUTSCENE_57                     0xFD
#define NI_OVL_CUTSCENE_63                     0xFE

#endif // CV64_H
