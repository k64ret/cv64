/**
 * @file interactuables_tables.c
 *
 * Contains tables used by interactuables and the different text spots.
 */

#include "A9560.h"
#include "event_flags.h"
#include "cutscene_ID.h"

cv64_actor_settings_t castleWallGratingMechanism_textSpotsActorSettings_openMechanism = {
    {257, 306, 71},
    CUTSCENE_INTERACTUABLES,
    INTERACT_ID_TEXT_72,
    7,
    6,
    DIFFICULTY_AND_SPAWN_SETTINGS_1(SPAWN_ON_ALL_DIFFICULTIES, SPAWN_SETTINGS_1),
    0
};

cv64_actor_settings_t castleWallGratingMechanism_textSpotsActorSettings_mechanismOpened = {
    {257, 306, 71},
    CUTSCENE_INTERACTUABLES,
    INTERACT_ID_TEXT_71,
    7,
    6,
    DIFFICULTY_AND_SPAWN_SETTINGS_1(SPAWN_ON_ALL_DIFFICULTIES, SPAWN_SETTINGS_1),
    0
};

door_item_open_verify_struct door_item_open_verify_list[] = {
    {ITEM_ID_ARCHIVES_KEY, EVENT_FLAG_ID_VILLA_INSIDE, EVENT_FLAG_VILLA_INSIDE_GET_ARCHIVES_KEY},
    {ITEM_ID_LEFT_TOWER_KEY,
     EVENT_FLAG_ID_CASTLE_WALL_MAIN,
     EVENT_FLAG_CASTLE_WALL_GET_LEFT_TOWER_KEY},
    {ITEM_ID_STOREROOM_KEY, EVENT_FLAG_ID_VILLA_INSIDE, EVENT_FLAG_VILLA_INSIDE_GET_STOREROOM_KEY},
    {ITEM_ID_GARDEN_KEY, EVENT_FLAG_ID_VILLA_INSIDE, EVENT_FLAG_VILLA_INSIDE_GET_GARDEN_KEY},
    {ITEM_ID_COPPER_KEY,
     EVENT_FLAG_ID_CASTLE_CENTER_4F_AND_MAZE_GARDEN,
     EVENT_FLAG_CASTLE_CENTER_4F_AND_MAZE_GARDEN_GET_COPPER_KEY},
    {ITEM_ID_CHAMBER_KEY,
     EVENT_FLAG_ID_CASTLE_CENTER_3F,
     EVENT_FLAG_CASTLE_CENTER_3F_GET_CHAMBER_KEY},
    {ITEM_ID_EXECUTION_KEY,
     EVENT_FLAG_ID_TOWER_EXECUTION_SORCERY_DUEL_ENDING,
     EVENT_FLAG_TOWER_EXECUTION_SORCERY_DUEL_ENDING_GET_EXECUTION_KEY},
    {ITEM_ID_SCIENCE_KEY1, EVENT_FLAG_ID_TOWER_SCIENCE, EVENT_FLAG_TOWER_SCIENCE_GET_KEY1},
    {ITEM_ID_SCIENCE_KEY2, EVENT_FLAG_ID_TOWER_SCIENCE, EVENT_FLAG_TOWER_SCIENCE_GET_KEY2},
    {ITEM_ID_SCIENCE_KEY3, EVENT_FLAG_ID_TOWER_SCIENCE, EVENT_FLAG_TOWER_SCIENCE_GET_KEY3},
    {ITEM_ID_CLOCKTOWER_KEY1, EVENT_FLAG_ID_CLOCK_TOWER, EVENT_FLAG_CLOCK_TOWER_GET_KEY1},
    {ITEM_ID_CLOCKTOWER_KEY2, EVENT_FLAG_ID_CLOCK_TOWER, EVENT_FLAG_CLOCK_TOWER_GET_KEY2},
    {ITEM_ID_CLOCKTOWER_KEY3, EVENT_FLAG_ID_CLOCK_TOWER, EVENT_FLAG_CLOCK_TOWER_GET_KEY3}
};

cv64_actor_settings_t* castleWallGratingMechanism_textSpotsActorSettings[1][3] = {
    {NULL,
     &castleWallGratingMechanism_textSpotsActorSettings_openMechanism,
     &castleWallGratingMechanism_textSpotsActorSettings_mechanismOpened}
};

// clang-format off

interactuables_settings interactuables_settings_table[] = {
    {ITEM_KIND_ITEM, ITEM_ID_WHITE_JEWEL, 0x0000, {0x00, 0x00}, 0x00000000, 5, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_RED_JEWEL_S, 0x0000, {0x00, 0x00}, 0x00000000, 5, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_RED_JEWEL_L, 0x0000, {0x00, 0x00}, 0x00000000, 7, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_SPECIAL1, 0x0000, {0x00, 0x00}, 0x00000000, 5, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_SPECIAL2, 0x0000, {0x00, 0x00}, 0x00000000, 5, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_ROAST_CHICKEN, 0x0000, {0x00, 0x00}, 0x00000000, 3, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_ROAST_BEEF, 0x0000, {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_HEALING_KIT, 0x0000, {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_PURIFYING, 0x0000, {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_CURE_AMPOULE, 0x0000, {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_POUT_POURRI, 0x0000, {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_POWERUP, 0x0000, {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_HOLY_WATER, 0x0000, {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_CROSS, 0x0000, {0x00, 0x00}, 0x00000000, 2, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_AXE, 0x0000, {0x00, 0x00}, 0x00000000, 2, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_KNIFE, 0x0000, {0x00, 0x00}, 0x00000000, 1, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_WOODEN_STAKE, 0x0000, {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_ROSE, 0x0000, {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_THE_CONTRACT, 0x0000, {0x00, 0x00}, 0x00000000, 1, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_ENGAGEMENT_RING, 0x0000, {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_MAGICAL_NITRO, 0x0000, {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_MANDRAGORA, 0x0000, {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_SUN_CARD, 0x0000, {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_MOON_CARD, 0x0000, {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_INCANDESCENT_GAZE, 0x0000, {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_GOLD_500, 0x0000, {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_GOLD_300, 0x0000, {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_GOLD_100, 0x0000, {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_ARCHIVES_KEY, 0x0000, {0x00, 0x00}, 0x00000000, 3, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_LEFT_TOWER_KEY, 0x0000, {0x00, 0x00}, 0x00000000, 3, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_STOREROOM_KEY, 0x0000, {0x00, 0x00}, 0x00000000, 3, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_GARDEN_KEY, 0x0000, {0x00, 0x00}, 0x00000000, 3, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_COPPER_KEY, 0x0000, {0x00, 0x00}, 0x00000000, 3, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_CHAMBER_KEY, 0x0000, {0x00, 0x00}, 0x00000000, 3, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_EXECUTION_KEY, 0x0000, {0x00, 0x00}, 0x00000000, 3, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_SCIENCE_KEY1, 0x0000, {0x00, 0x00}, 0x00000000, 3, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_SCIENCE_KEY2, 0x0000, {0x00, 0x00}, 0x00000000, 3, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_SCIENCE_KEY3, 0x0000, {0x00, 0x00}, 0x00000000, 3, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_CLOCKTOWER_KEY1, 0x0000, {0x00, 0x00}, 0x00000000, 3, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_CLOCKTOWER_KEY2, 0x0000, {0x00, 0x00}, 0x00000000, 3, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_CLOCKTOWER_KEY3, 0x0000, {0x00, 0x00}, 0x00000000, 3, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_GOLD_500, (ITEM_VANISH_OR_UPDATE_POSITION), {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_GOLD_300, (ITEM_VANISH_OR_UPDATE_POSITION), {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_GOLD_100, (ITEM_VANISH_OR_UPDATE_POSITION), {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_RED_JEWEL_S, (ITEM_VANISH_OR_UPDATE_POSITION), {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_RED_JEWEL_L, (ITEM_VANISH_OR_UPDATE_POSITION), {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_HOLY_WATER, (ITEM_VANISH_OR_UPDATE_POSITION), {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_CROSS, (ITEM_VANISH_OR_UPDATE_POSITION), {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_AXE, (ITEM_VANISH_OR_UPDATE_POSITION), {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_KNIFE, (ITEM_VANISH_OR_UPDATE_POSITION), {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_POWERUP, (ITEM_VANISH_OR_UPDATE_POSITION), {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_PURIFYING, (ITEM_VANISH_OR_UPDATE_POSITION), {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_CURE_AMPOULE, (ITEM_VANISH_OR_UPDATE_POSITION), {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_ROAST_CHICKEN, (ITEM_VANISH_OR_UPDATE_POSITION), {0x00, 0x00}, 0x00000000, 3, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_ROAST_BEEF, (ITEM_VANISH_OR_UPDATE_POSITION), {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_RED_JEWEL_S, (ITEM_DOES_NOT_FLASH | ITEM_INVISIBLE), {0x00, 0x00}, 0x00000000, 5, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_RED_JEWEL_L, (ITEM_DOES_NOT_FLASH | ITEM_INVISIBLE), {0x00, 0x00}, 0x00000000, 7, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_ROAST_CHICKEN, (ITEM_DOES_NOT_FLASH | ITEM_INVISIBLE), {0x00, 0x00}, 0x00000000, 3, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_ROAST_BEEF, (ITEM_DOES_NOT_FLASH | ITEM_INVISIBLE), {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_HEALING_KIT, (ITEM_DOES_NOT_FLASH | ITEM_INVISIBLE), {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_PURIFYING, (ITEM_DOES_NOT_FLASH | ITEM_INVISIBLE), {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_CURE_AMPOULE, (ITEM_DOES_NOT_FLASH | ITEM_INVISIBLE), {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_SUN_CARD, (ITEM_DOES_NOT_FLASH | ITEM_INVISIBLE), {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_MOON_CARD, (ITEM_DOES_NOT_FLASH | ITEM_INVISIBLE), {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_GOLD_500, (ITEM_DOES_NOT_FLASH | ITEM_INVISIBLE), {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_GOLD_300, (ITEM_DOES_NOT_FLASH | ITEM_INVISIBLE), {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_ITEM, ITEM_ID_GOLD_100, (ITEM_DOES_NOT_FLASH | ITEM_INVISIBLE), {0x00, 0x00}, 0x00000000, 4, 0x0000, 12, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0000, 0x0000, {0x00, 0x00}, 0x00000000, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0001, 0x0000, {0x00, 0x00}, 0x00000000, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0002, 0x0000, {0x00, 0x00}, 0x00000000, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0003, 0x0000, {0x00, 0x00}, 0x00000000, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0004, 0x0000, {0x00, 0x00}, 0x00000000, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0005, 0x0000, {0x00, 0x00}, 0x00000000, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0006, 0x0000, {0x00, 0x00}, 0x00000000, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0007, 0x0000, {0x00, 0x00}, 0x00000000, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0008, 0x0000, {0x00, 0x00}, 0x00000000, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0009, 0x0000, {0x00, 0x00}, 0x00000000, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x000A, 0x0000, {0x00, 0x00}, 0x00000000, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x000B, 0x0000, {0x00, 0x00}, 0x00000000, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x000C, 0x0000, {0x00, 0x00}, 0x00000000, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x000D, 0x0000, {0x00, 0x00}, 0x00000000, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x000E, 0x0000, {0x00, 0x00}, 0x00000000, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x000F, 0x0000, {0x00, 0x00}, 0x00000000, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0010, 0x0000, {0x00, 0x00}, 0x00000000, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0011, 0x0000, {0x00, 0x00}, 0x00000000, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0012, 0x0000, {0x00, 0x00}, 0x00000000, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0013, 0x0000, {0x00, 0x00}, 0x00000000, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0014, 0x0000, {0x00, 0x00}, 0x00000000, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0015, 0x0000, {0x00, 0x00}, 0x00000000, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0016, 0x0000, {0x00, 0x00}, 0x00000000, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0017, 0x0000, {0x00, 0x00}, 0x00000000, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0018, 0x0000, {0x00, 0x00}, 0x00000000, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0019, 0x0000, {0x00, 0x00}, 0x00000000, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x001A, 0x0000, {0x00, 0x00}, 0x00000000, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x001B, 0x0000, {0x00, 0x00}, 0x00000000, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0000, 0x0004, {0x00, 0x00}, 0x00000004, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0000, 0x0004, {0x00, 0x00}, 0x00000010, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0001, 0x0004, {0x00, 0x00}, 0x00000020, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0009, 0x0008, {0x00, 0x00}, 0x00000100, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0001, 0x0008, {0x00, 0x00}, 0x00000008, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0000, 0x0004, {0x00, 0x00}, 0x00000008, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0004, 0x0008, {0x00, 0x00}, 0x00000010, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0003, 0x0004, {0x00, 0x00}, 0x00000010, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0008, 0x0008, {0x00, 0x00}, 0x00000004, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0007, 0x0004, {0x00, 0x00}, 0x00000004, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0002, 0x0004, {0x00, 0x00}, 0x00000008, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0002, 0x0004, {0x00, 0x00}, 0x00000010, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0002, 0x0004, {0x00, 0x00}, 0x00000008, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0005, 0x0008, {0x00, 0x00}, 0x00000001, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0004, 0x0094, {0x00, 0x00}, 0x00000001, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0000, 0x0008, {0x00, 0x00}, 0x00000001, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0000, 0x0004, {0x00, 0x00}, 0x00000001, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0009, 0x0008, {0x00, 0x00}, 0x00000002, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0008, 0x0034, {0x00, 0x00}, 0x00000002, CUTSCENE_ID_CASTLE_WALL_MOVING_GEARS, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0001, 0x0004, {0x00, 0x00}, 0x00000100, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0006, 0x0034, {0x00, 0x00}, 0x00000800, CUTSCENE_ID_FOREST_ACTIVATE_LEVER, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0006, 0x0154, {0x00, 0x00}, 0x00000200, STAGE_OBJECT_LEVER, LEVER_TYPE_LOWER_PLATFORMS,   5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0006, 0x0154, {0x00, 0x00}, 0x00000400, STAGE_OBJECT_LEVER, LEVER_TYPE_OPEN_LEVER_4_DOOR, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0001, 0x0004, {0x00, 0x00}, 0x00000200, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0001, 0x0004, {0x00, 0x00}, 0x00000400, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0008, 0x0004, {0x00, 0x00}, 0x00000001, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0000, 0x0154, {0x00, 0x00}, 0x00020000, STAGE_OBJECT_LEVER, LEVER_TYPE_LOWER_PLATFORMS, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0006, 0x0154, {0x00, 0x00}, 0x00004000, STAGE_OBJECT_LEVER, LEVER_TYPE_OPEN_BOSS_DOOR,  5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x0001, 0x0004, {0x00, 0x00}, 0x00004000, 0x0000, 0x0000, 5, {0x00, 0x00}},
    {ITEM_KIND_TEXT_SPOT, 0x000A, 0x0004, {0x00, 0x00}, 0x00000010, 0x0000, 0x0000, 5, {0x00, 0x00}}
};

// TODO: `extern const u32` for the dlists
item_model_settings item_model_settings_list[] = {
    {0x060034C0, 1.00f, 0, 0, 255, 0x00, 0x01, 0x01, 0x00, 0x00},
    {0x060034C0, 1.00f, 0, 1, 255, 0x00, 0x02, 0x01, 0x00, 0x00},
    {0x060034C0, 1.30f, 0, 1, 255, 0x00, 0x03, 0x01, 0x00, 0x00},
    {0x060034C0, 1.00f, 0, 2, 255, 0x00, 0x04, 0x01, 0x00, 0x00},
    {0x060034C0, 1.00f, 0, 3, 255, 0x00, 0x05, 0x01, 0x00, 0x00},
    {0x06004C10, 1.00f, 255, 255, 255, 0x00, 0x06, 0x40, 0x00, 0x00},
    {0x06004A00, 1.00f, 255, 255, 255, 0x00, 0x07, 0x40, 0x00, 0x00},
    {0x06004590, 1.00f, 255, 255, 255, 0x00, 0x08, 0x40, 0x00, 0x00},
    {0x06003560, 1.30f, 255, 255, 255, 0x00, 0x09, 0x40, 0x00, 0x00},
    {0x06004E30, 1.00f, 255, 255, 255, 0x00, 0x0A, 0x40, 0x00, 0x00},
    {0x060051C0, 0.75f, 0, 0, 255, 0x00, 0x0B, 0x00, 0x00, 0x00},
    {0x06005F08, 1.00f, 255, 255, 255, 0x00, 0x0C, 0x00, 0x00, 0x00},
    {0x06005C60, 2.00f, 255, 255, 255, 0x00, 0x0E, 0x01, 0x00, 0x00},
    {0x06004328, 1.00f, 255, 255, 255, 0x00, 0x0F, 0x01, 0x00, 0x00},
    {0x06003A88, 1.00f, 255, 255, 255, 0x00, 0x10, 0x01, 0x00, 0x00},
    {0x06005490, 1.00f, 255, 255, 255, 0x00, 0x0D, 0x01, 0x00, 0x00},
    {0x060040A0, 1.00f, 255, 255, 255, 0x00, 0x11, 0x00, 0x00, 0x00},
    {0x06002E18, 1.00f, 255, 255, 255, 0x00, 0x12, 0x00, 0x00, 0x00},
    {0x06003D90, 1.00f, 255, 255, 255, 0x00, 0x13, 0x00, 0x00, 0x00},
    {0x060051C0, 0.50f, 0, 0, 191, 0x00, 0x14, 0x00, 0x00, 0x00},
    {0x060057F8, 1.00f, 255, 255, 255, 0x00, 0x15, 0x00, 0x00, 0x00},
    {0x06004788, 1.00f, 255, 255, 255, 0x00, 0x16, 0x00, 0x00, 0x00},
    {0x06003088, 1.00f, 0, 0, 255, 0x00, 0x17, 0x41, 0x00, 0x00},
    {0x06003088, 1.00f, 1, 1, 255, 0x00, 0x18, 0x41, 0x00, 0x00},
    {0x060051C0, 1.50f, 0, 0, 191, 0x00, 0x19, 0x00, 0x00, 0x00},
    {0x060051C0, 1.00f, 0, 2, 255, 0x00, 0x27, 0x00, 0x00, 0x00},
    {0x060051C0, 1.00f, 0, 1, 255, 0x00, 0x28, 0x00, 0x00, 0x00},
    {0x060051C0, 1.00f, 0, 0, 255, 0x00, 0x29, 0x00, 0x00, 0x00},
    {0x06003FE0, 1.00f, 0, 0, 255, 0x00, 0x1A, 0x01, 0x00, 0x00},
    {0x06003FE0, 1.00f, 0, 1, 255, 0x00, 0x1B, 0x01, 0x00, 0x00},
    {0x06003FE0, 1.00f, 0, 2, 255, 0x00, 0x1C, 0x01, 0x00, 0x00},
    {0x06003FE0, 1.00f, 0, 3, 255, 0x00, 0x1D, 0x01, 0x00, 0x00},
    {0x06003FE0, 1.00f, 0, 4, 255, 0x00, 0x1E, 0x01, 0x00, 0x00},
    {0x06003FE0, 1.00f, 0, 5, 255, 0x00, 0x1F, 0x01, 0x00, 0x00},
    {0x06003FE0, 1.00f, 0, 6, 255, 0x00, 0x20, 0x01, 0x00, 0x00},
    {0x06003FE0, 1.00f, 0, 2, 255, 0x00, 0x21, 0x01, 0x00, 0x00},
    {0x06003FE0, 1.00f, 0, 2, 255, 0x00, 0x22, 0x01, 0x00, 0x00},
    {0x06003FE0, 1.00f, 0, 2, 255, 0x00, 0x23, 0x01, 0x00, 0x00},
    {0x06003FE0, 1.00f, 0, 3, 255, 0x00, 0x24, 0x01, 0x00, 0x00},
    {0x06003FE0, 1.00f, 0, 3, 255, 0x00, 0x25, 0x01, 0x00, 0x00},
    {0x06003FE0, 1.00f, 0, 3, 255, 0x00, 0x26, 0x01, 0x00, 0x00}
};

// clang-format on
