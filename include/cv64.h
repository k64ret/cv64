#ifndef CV64_H
#define CV64_H

#include "bit.h"
#include "math.h"
#include "nisitenma_ichigo.h"
#include <ultra64.h>

// Unknown types
typedef u8 UNK8;
typedef u16 UNK16;
typedef s32 UNK32;
typedef void* UNKPTR;

typedef u8 Addr[];

extern u32 D_80092F50;
extern Gfx* gDisplayListHead; // 0x800B49E0
extern u32 map_misc_event_flags;
extern u16 item_pickables_text[];
extern u32 map_text_segment_address[28]; // 0x8016D008
/**
 * If set to `TRUE`, the dynamic map lighting won't be updated
 * (for example, when transitioning from day to night)
 */
extern u32 dont_update_map_lighting;

typedef enum TimeOfDay {
    TIME_DAY,
    TIME_EVENING_MORNING,
    TIME_NIGHT
} TimeOfDay;

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

typedef enum MenuID {
    MENU_ID_NOT_ON_MENU = 0,
    MENU_ID_PAUSE       = 9,
    MENU_ID_RENON_SHOP  = 10,
    MENU_ID_GAME_OVER   = 14
} MenuID;

extern void end_master_display_list();
extern s32 menuButton_selectNextOption(s32* option, s16* param_2, s16 number_of_options);
extern void func_800010A0_1CA0();
extern void func_8001248C_1308C();
extern void func_8000C6D0();
extern void updateGameSound();
extern void drawFog();
extern void func_80005658();
extern u32 getMapEventFlagID(s16 stage_ID);
s32 func_8001A250_1AE50(s32* arg0, u16* arg1, s16 arg2);
extern void func_80066400(s32);
extern void Map_SetCameraParams();
extern void player_status_init();

#define NPTR 0
// Gets the offset of a struct member variable
#define OFFSET_OF(type, member) ((u32) & ((type*) 0)->member)
#define ARRAY_COUNT(arr)        (s32)(sizeof(arr) / sizeof(arr[0])) // Get number of elements in the array
#define ARRAY_START(arr)        &arr[0]                             // Get start address of array
#define ARRAY_END(arr)          &arr[ARRAY_COUNT(arr)]              // Get end address of array

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

// Text IDs for `entranceMapNameDisplay_mapList`
#define ENTRANCE_MAP_NAME_MORI         0
#define ENTRANCE_MAP_NAME_TOUOKUJI     1
#define ENTRANCE_MAP_NAME_NAKANIWA     2
#define ENTRANCE_MAP_NAME_CHIKA_KODO   3
#define ENTRANCE_MAP_NAME_CHIKA_SUIRO  4
#define ENTRANCE_MAP_NAME_HONMARU_B1F  5
#define ENTRANCE_MAP_NAME_KETTOU_TOU   6
#define ENTRANCE_MAP_NAME_KAGAKU_TOU   7
#define ENTRANCE_MAP_NAME_SHOKEI_TOU   8
#define ENTRANCE_MAP_NAME_MAHOU_TOU    9
#define ENTRANCE_MAP_NAME_TOU_TURO     10
#define ENTRANCE_MAP_NAME_TOKEITOU_NAI 11
#define ENTRANCE_MAP_NAME_TENSHU       12
#define ENTRANCE_MAP_NAME_NONE         -1

// Text IDs for Forest of Silence
#define FOREST_LOCKED_DOOR 1
/**
 * "The lady who blesses and restores" statue,
 * right before the final King Skeleton boss door
 */
#define FOREST_LADY_WHO_BLESSES_INSCRIPTION 4
#define FOREST_LADY_WHO_BLESSES_STATUE      5
#define FOREST_ACTIVATE_LEVER               6
#define FOREST_DEAD_SKELETON                8
#define FOREST_DEAD_BODY                    10
// Text IDs for Villa (Front Yard)
#define VILLA_OUTSIDE_CHIMERA_STATUE 6
// Text IDs for Castle Wall (Main)
#define CASTLE_WALL_MAIN_OPEN_GRATING           8
#define CASTLE_WALL_MAIN_GRATING_ALREADY_OPENED 9
// Text IDs for Undeground Waterway
#define WATERWAY_DOOR_CLOSED 10
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
#define CASTLE_CENTER_4F_LIBRARY_PUZZLE_RED_PIECE   9
#define CASTLE_CENTER_4F_LIBRARY_PUZZLE_BLUE_PIECE  10
#define CASTLE_CENTER_4F_LIBRARY_PUZZLE_FAIL        11
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

/**
 * Same as `GET_MAP_MESSAGE_POOL_PTR`, but this is not accessed through a function pointer
 */
#define GET_MAP_MESSAGE_POOL_PTR_NO_FUNC_PTR()                                                     \
    NisitenmaIchigoFiles_segmentToVirtual(                                                         \
        map_text_segment_address[sys.SaveStruct_gameplay.map], MAP_ASSETS_FILE_ID                  \
    )

extern const u32 MENU_RED_BACKGROUND_DL;

#endif // CV64_H
