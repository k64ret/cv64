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
// Castle Keep (Exterior), Castle Keep (Interior), Clock Tower
#define EVENT_FLAG_ID_CLOCK_TOWER 5
// Dracula's desert, Rose / Actriese Fan Room, Villa's vampire crypt, Room of
// Clocks
#define EVENT_FLAG_ID_MISC_STAGES 6
// Castle Wall (Main)
#define EVENT_FLAG_ID_CASTLE_WALL_MAIN 10

/*
 *  Event flags
 */
// EVENT_FLAG_ID_CLOCK_TOWER
#define EVENT_FLAG_CLOCK_TOWER_DEFEATED_DEATH   0x00000040
#define EVENT_FLAG_CLOCK_TOWER_DEFEATED_ACTRISE 0x00000080

// EVENT_FLAG_ID_MISC_STAGES
#define EVENT_FLAG_MISC_STAGES_ENTERED_ROOM_OF_CLOCKS 0x08000000

// EVENT_FLAG_ID_CASTLE_WALL_MAIN
#define EVENT_FLAG_CASTLE_WALL_MAIN_WATCHED_DRACULA_CUTSCENE 0x00000100

#endif
