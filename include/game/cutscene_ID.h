#ifndef CUTSCENE_ID_H
#define CUTSCENE_ID_H

typedef enum cv64_cutscene_id {
    CUTSCENE_ID_NONE                       = 0x00,
    CUTSCENE_ID_OPENING                    = 0x01,
    CUTSCENE_ID_TITLE                      = 0x02,
    CUTSCENE_ID_CASTLE_WALL_MOVING_GEARS   = 0x07,
    CUTSCENE_ID_LIBRARY_PUZZLE_SOLVED      = 0x13,
    CUTSCENE_ID_BLOW_UP_WALL_IN_BULL_ARENA = 0x14,
    CUTSCENE_ID_BLOW_UP_WALL_TO_LIBRARY    = 0x15,
    CUTSCENE_ID_FOREST_ACTIVATE_LEVER      = 0x1A,
    CUTSCENE_ID_FOREST_INTRO               = 0x3C,
    CUTSCENE_ID_CREDITS                    = 0x63
} cv64_cutscene_id_t;

#endif // CUTSCENE_ID_H
