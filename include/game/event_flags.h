#ifndef EVENT_FLAGS_H
#define EVENT_FLAGS_H

#include "cv64.h"

#define CHECK_EVENT_FLAGS(event_flag_ID, value)                                                    \
    BITS_HAS(sys.SaveStruct_gameplay.event_flags[event_flag_ID], value)

#define SET_EVENT_FLAGS(event_flag_ID, value)                                                      \
    BITS_SET(sys.SaveStruct_gameplay.event_flags[event_flag_ID], value)

#define REMOVE_EVENT_FLAGS(event_flag_ID, value)                                                   \
    BITS_UNSET(sys.SaveStruct_gameplay.event_flags[event_flag_ID], value)

/*
 *  Event flag ID
 */
// Forest of Silence
// Any map not included below
#define EVENT_FLAG_ID_FOREST_AND_DEFAULT 0
// Villa (Foyer, rose garden, and servant entrance area)
// Villa (Hallway, bedroom, living room, storeroom, and archives area)
#define EVENT_FLAG_ID_VILLA_INSIDE 1
// Tunnel
// Castle Center (Top elevator room)
#define EVENT_FLAG_ID_WATERWAY_AND_CASTLE_CENTER_5F 2
// Castle Center (Broken staircase, friendly lizard-man, vampire butler room, and upper cracked wall area)
// Castle Center (Nitro, invention, and vampire maid room area.)
#define EVENT_FLAG_ID_CASTLE_CENTER_3F 3
// Tower of Execution
// Tower of Sorcery
// Duel Tower
// Ending map
#define EVENT_FLAG_ID_TOWER_EXECUTION_SORCERY_DUEL_ENDING 4
// Castle Keep (Exterior)
// Castle Keep (Interior)
// Clock Tower
#define EVENT_FLAG_ID_CLOCK_TOWER 5
// Dracula's desert
// Rose / Actriese Fan Room
// Villa's vampire crypt
// Room of Clocks
#define EVENT_FLAG_ID_MISC_STAGES 6
// Not assigned to any map. Instead, it's used for the Tower of Science turrets
#define EVENT_FLAG_ID_TOWER_SCIENCE_TURRETS 7
// Castle Center (Bottom elevator room)
// Castle Center (Gears)
#define EVENT_FLAG_ID_CASTLE_CENTER_1F_2F 8
// Villa (Front yard)
#define EVENT_FLAG_ID_VILLA_OUTSIDE 9
// Castle Wall (Main)
#define EVENT_FLAG_ID_CASTLE_WALL_MAIN 10
// Castle Center (Library)
// Maze Garden
#define EVENT_FLAG_ID_CASTLE_CENTER_4F_AND_MAZE_GARDEN 11
// Tunnel
#define EVENT_FLAG_ID_TUNNEL 12
// Castle Center (Main)
#define EVENT_FLAG_ID_CASTLE_CENTER_MAIN 13
// Castle Wall (Towers)
#define EVENT_FLAG_ID_CASTLE_WALL_TOWERS 14
// Tower of Science
#define EVENT_FLAG_ID_TOWER_SCIENCE 15

/*
 *  Event flags
 */
// EVENT_FLAG_ID_VILLA_INSIDE
#define EVENT_FLAG_VILLA_INSIDE_GET_STOREROOM_KEY 0x02000000
#define EVENT_FLAG_VILLA_INSIDE_GET_GARDEN_KEY    0x08000000
#define EVENT_FLAG_VILLA_INSIDE_GET_ARCHIVES_KEY  0x10000000

// EVENT_FLAG_ID_CASTLE_CENTER_3F
#define EVENT_FLAG_CASTLE_CENTER_3F_GET_CHAMBER_KEY                 0x00400000
#define EVENT_FLAG_CASTLE_CENTER_3F_DISABLED_UPPER_WALL_INTERACTION 0x00002000
#define EVENT_FLAG_CASTLE_CENTER_3F_NITRO_IN_UPPER_WALL             0x00004000
#define EVENT_FLAG_CASTLE_CENTER_3F_MANDRAGORA_IN_UPPER_WALL        0x00008000

// EVENT_FLAG_ID_TOWER_EXECUTION_SORCERY_DUEL_ENDING
#define EVENT_FLAG_TOWER_EXECUTION_SORCERY_DUEL_ENDING_GET_EXECUTION_KEY 0x00000040

// EVENT_FLAG_ID_CLOCK_TOWER
#define EVENT_FLAG_CLOCK_TOWER_GET_KEY1         0x00040000
#define EVENT_FLAG_CLOCK_TOWER_GET_KEY2         0x00080000
#define EVENT_FLAG_CLOCK_TOWER_GET_KEY3         0x00100000
#define EVENT_FLAG_CLOCK_TOWER_DEFEATED_DEATH   0x00000040
#define EVENT_FLAG_CLOCK_TOWER_DEFEATED_ACTRISE 0x00000080

// EVENT_FLAG_ID_MISC_STAGES
#define EVENT_FLAG_MISC_STAGES_ENTERED_ROOM_OF_CLOCKS 0x08000000

// EVENT_FLAG_ID_CASTLE_CENTER_1F_2F
#define EVENT_FLAG_CASTLE_CENTER_1F_2F_ELEVATOR_ACTIVATED 0x00000002

// EVENT_FLAG_ID_CASTLE_WALL_MAIN
#define EVENT_FLAG_CASTLE_WALL_GET_LEFT_TOWER_KEY            0x00000040
#define EVENT_FLAG_CASTLE_WALL_MAIN_WATCHED_DRACULA_CUTSCENE 0x00000100

// EVENT_FLAG_ID_CASTLE_CENTER_4F_AND_MAZE_GARDEN
#define EVENT_FLAG_CASTLE_CENTER_4F_AND_MAZE_GARDEN_GET_COPPER_KEY        0x00000020
#define EVENT_FLAG_CASTLE_CENTER_4F_AND_MAZE_GARDEN_LIBRARY_PUZZLE_SOLVED 0x01000000

// EVENT_FLAG_ID_CASTLE_CENTER_MAIN
#define EVENT_FLAG_CASTLE_CENTER_3F_RELEASED_BULL_ROOM_CRYSTAL_MAGIC 0x00000001
#define EVENT_FLAG_CASTLE_CENTER_3F_DISABLED_LOWER_WALL_INTERACTION  0x00000008
#define EVENT_FLAG_CASTLE_CENTER_3F_MANDRAGORA_IN_LOWER_WALL         0x00000100
#define EVENT_FLAG_CASTLE_CENTER_3F_NITRO_IN_LOWER_WALL              0x02000000

// EVENT_FLAG_ID_TOWER_SCIENCE
#define EVENT_FLAG_TOWER_SCIENCE_GET_KEY1 0x00000001
#define EVENT_FLAG_TOWER_SCIENCE_GET_KEY2 0x00000002
#define EVENT_FLAG_TOWER_SCIENCE_GET_KEY3 0x00000004

#endif
