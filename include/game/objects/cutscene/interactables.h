#ifndef INTERACTABLES_H
#define INTERACTABLES_H

#include "gfx/model.h"
#include "objects/effect/pickableItemFlash.h"
#include "objects/menu/mfds.h"
#include "actor.h"
#include "item.h"

// Pickable items and text spots, all of which are
// interacted with using C-Right

#define ITEM_FADE_TIMER self->header.timer

#define INTERACTABLES_SETTINGS_TYPE_ITEM      1
#define INTERACTABLES_SETTINGS_TYPE_TEXT_SPOT 2

// Variable 1: ID + 1 in `interactables_settings` to get the settings from
#define INTERACTABLES_SETTINGS_ENTRY_ID(id) (id - 1)
#define INTERACTABLES_VARIABLE_1(id)        (id + 1) // Used in the `interactables`'s actor config

// Variable 2:
// Items: Upper 2-bytes of the event flag
#define ITEM_EVENT_FLAG_UPPER_2BYTES settings->variable_2
// Text spots: Size of the trigger (X)
#define TEXT_SPOT_X_SIZE settings->variable_2

// Variable 3:
// Items: Lower 2-bytes of the event flag
#define ITEM_EVENT_FLAG_LOWER_2BYTES settings->variable_3
// White Jewel: Spawn number
#define WHITE_JEWEL_SPAWN_NUMBER settings->variable_3
// Text spots: Size of the trigger (Z)
#define TEXT_SPOT_Z_SIZE settings->variable_3

/**
 * Indexes corresponding to the entries from `interactables_settings`
 */
typedef enum InteractableID {
    //// Items ////
    // Visible + Doesn't vanish
    INTERACT_ID_NO_VANISH_WHITE_JEWEL       = 0x00,
    INTERACT_ID_NO_VANISH_RED_JEWEL_S       = 0x01,
    INTERACT_ID_NO_VANISH_RED_JEWEL_L       = 0x02,
    INTERACT_ID_NO_VANISH_SPECIAL1          = 0x03,
    INTERACT_ID_NO_VANISH_SPECIAL2          = 0x04,
    INTERACT_ID_NO_VANISH_ROAST_CHICKEN     = 0x05,
    INTERACT_ID_NO_VANISH_ROAST_BEEF        = 0x06,
    INTERACT_ID_NO_VANISH_HEALING_KIT       = 0x07,
    INTERACT_ID_NO_VANISH_PURIFYING         = 0x08,
    INTERACT_ID_NO_VANISH_CURE_AMPOULE      = 0x09,
    INTERACT_ID_NO_VANISH_POT_POURRI        = 0x0A, // Unused
    INTERACT_ID_NO_VANISH_POWERUP           = 0x0B,
    INTERACT_ID_NO_VANISH_HOLY_WATER        = 0x0C,
    INTERACT_ID_NO_VANISH_CROSS             = 0x0D,
    INTERACT_ID_NO_VANISH_AXE               = 0x0E,
    INTERACT_ID_NO_VANISH_KNIFE             = 0x0F,
    INTERACT_ID_NO_VANISH_WOODEN_STAKE      = 0x10, // Unused
    INTERACT_ID_NO_VANISH_ROSE              = 0x11, // Unused
    INTERACT_ID_NO_VANISH_THE_CONTRACT      = 0x12,
    INTERACT_ID_NO_VANISH_ENGAGEMENT_RING   = 0x13, // Unused
    INTERACT_ID_NO_VANISH_MAGICAL_NITRO     = 0x14,
    INTERACT_ID_NO_VANISH_MANDRAGORA        = 0x15,
    INTERACT_ID_NO_VANISH_SUN_CARD          = 0x16,
    INTERACT_ID_NO_VANISH_MOON_CARD         = 0x17,
    INTERACT_ID_NO_VANISH_INCANDESCENT_GAZE = 0x18, // Unused
    INTERACT_ID_NO_VANISH_500_GOLD          = 0x19,
    INTERACT_ID_NO_VANISH_300_GOLD          = 0x1A,
    INTERACT_ID_NO_VANISH_100_GOLD          = 0x1B,
    INTERACT_ID_NO_VANISH_ARCHIVES_KEY      = 0x1C,
    INTERACT_ID_NO_VANISH_LEFT_TOWER_KEY    = 0x1D,
    INTERACT_ID_NO_VANISH_STOREROOM_KEY     = 0x1E,
    INTERACT_ID_NO_VANISH_GARDEN_KEY        = 0x1F,
    INTERACT_ID_NO_VANISH_COPPER_KEY        = 0x20,
    INTERACT_ID_NO_VANISH_CHAMBER_KEY       = 0x21,
    INTERACT_ID_NO_VANISH_EXECUTION_KEY     = 0x22,
    INTERACT_ID_NO_VANISH_SCIENCE_KEY1      = 0x23,
    INTERACT_ID_NO_VANISH_SCIENCE_KEY2      = 0x24,
    INTERACT_ID_NO_VANISH_SCIENCE_KEY3      = 0x25,
    INTERACT_ID_NO_VANISH_CLOCKTOWER_KEY1   = 0x26,
    INTERACT_ID_NO_VANISH_CLOCKTOWER_KEY2   = 0x27,
    INTERACT_ID_NO_VANISH_CLOCKTOWER_KEY3   = 0x28,

    // Visible + Vanishes
    INTERACT_ID_VANISH_500_GOLD      = 0x29,
    INTERACT_ID_VANISH_300_GOLD      = 0x2A,
    INTERACT_ID_VANISH_100_GOLD      = 0x2B,
    INTERACT_ID_VANISH_RED_JEWEL_S   = 0x2C,
    INTERACT_ID_VANISH_RED_JEWEL_L   = 0x2D,
    INTERACT_ID_VANISH_HOLY_WATER    = 0x2E,
    INTERACT_ID_VANISH_CROSS         = 0x2F,
    INTERACT_ID_VANISH_AXE           = 0x30,
    INTERACT_ID_VANISH_KNIFE         = 0x31,
    INTERACT_ID_VANISH_POWERUP       = 0x32,
    INTERACT_ID_VANISH_PURIFYING     = 0x33,
    INTERACT_ID_VANISH_CURE_AMPOULE  = 0x34,
    INTERACT_ID_VANISH_ROAST_CHICKEN = 0x35,
    INTERACT_ID_VANISH_ROAST_BEEF    = 0x36,

    // Invisible + Doesn't vanish
    INTERACT_ID_INVISIBLE_RED_JEWEL_S   = 0x37,
    INTERACT_ID_INVISIBLE_RED_JEWEL_L   = 0x38,
    INTERACT_ID_INVISIBLE_ROAST_CHICKEN = 0x39,
    INTERACT_ID_INVISIBLE_ROAST_BEEF    = 0x3A,
    INTERACT_ID_INVISIBLE_HEALING_KIT   = 0x3B,
    INTERACT_ID_INVISIBLE_PURIFYING     = 0x3C,
    INTERACT_ID_INVISIBLE_CURE_AMPOULE  = 0x3D,
    INTERACT_ID_INVISIBLE_SUN_CARD      = 0x3E,
    INTERACT_ID_INVISIBLE_MOON_CARD     = 0x3F,
    INTERACT_ID_INVISIBLE_500_GOLD      = 0x40,
    INTERACT_ID_INVISIBLE_300_GOLD      = 0x41,
    INTERACT_ID_INVISIBLE_100_GOLD      = 0x42,

    //// Text spots ////
    /**
     * Text spots labelled with "GENERIC"
     * are used accross various maps, and are not specific
     * to certain situations.
     *
     * The number following the "GENERIC" labels
     * correspond to the text ID associated to them.
     */
    INTERACT_ID_TEXT_GENERIC_0                  = 0x43,
    INTERACT_ID_TEXT_GENERIC_1                  = 0x44,
    INTERACT_ID_TEXT_GENERIC_2                  = 0x45,
    INTERACT_ID_TEXT_GENERIC_3                  = 0x46,
    INTERACT_ID_TEXT_GENERIC_4                  = 0x47,
    INTERACT_ID_TEXT_GENERIC_5                  = 0x48,
    INTERACT_ID_TEXT_GENERIC_6                  = 0x49,
    INTERACT_ID_TEXT_GENERIC_7                  = 0x4A,
    INTERACT_ID_TEXT_GENERIC_8                  = 0x4B,
    INTERACT_ID_TEXT_GENERIC_9                  = 0x4C,
    INTERACT_ID_TEXT_GENERIC_10                 = 0x4D,
    INTERACT_ID_TEXT_GENERIC_11                 = 0x4E,
    INTERACT_ID_TEXT_4F                         = 0x4F,
    INTERACT_ID_TEXT_50                         = 0x50,
    INTERACT_ID_TEXT_51                         = 0x51,
    INTERACT_ID_TEXT_52                         = 0x52,
    INTERACT_ID_TEXT_53                         = 0x53,
    INTERACT_ID_TEXT_54                         = 0x54,
    INTERACT_ID_TEXT_55                         = 0x55,
    INTERACT_ID_TEXT_56                         = 0x56,
    INTERACT_ID_TEXT_57                         = 0x57,
    INTERACT_ID_TEXT_58                         = 0x58,
    INTERACT_ID_TEXT_59                         = 0x59,
    INTERACT_ID_TEXT_5A                         = 0x5A,
    INTERACT_ID_TEXT_5B                         = 0x5B,
    INTERACT_ID_TEXT_5C                         = 0x5C,
    INTERACT_ID_TEXT_5D                         = 0x5D,
    INTERACT_ID_TEXT_5E                         = 0x5E,
    INTERACT_ID_TEXT_5F                         = 0x5F,
    INTERACT_ID_TEXT_60                         = 0x60,
    INTERACT_ID_TEXT_61                         = 0x61,
    INTERACT_ID_TEXT_62                         = 0x62,
    INTERACT_ID_TEXT_63                         = 0x63,
    INTERACT_ID_TEXT_64                         = 0x64,
    INTERACT_ID_TEXT_65                         = 0x65,
    INTERACT_ID_TEXT_66                         = 0x66,
    INTERACT_ID_TEXT_67                         = 0x67,
    INTERACT_ID_TEXT_68                         = 0x68,
    INTERACT_ID_TEXT_69                         = 0x69,
    INTERACT_ID_TEXT_6A                         = 0x6A,
    INTERACT_ID_TEXT_6B                         = 0x6B,
    INTERACT_ID_TEXT_6C                         = 0x6C,
    INTERACT_ID_TEXT_6D                         = 0x6D,
    INTERACT_ID_TEXT_6E                         = 0x6E,
    INTERACT_ID_TEXT_6F                         = 0x6F,
    INTERACT_ID_CASTLE_WALL_MAIN_GRATING_OPENED = 0x70,
    INTERACT_ID_CASTLE_WALL_MAIN_OPEN_GRATING   = 0x71,
    INTERACT_ID_FOREST_LOCKED_DOOR              = 0x72,
    INTERACT_ID_FOREST_LEVER_WERETIGER          = 0x73,
    INTERACT_ID_FOREST_LEVER_LOWER_PLATFORMS    = 0x74,
    INTERACT_ID_FOREST_LEVER_OPEN_LEVER_4_DOOR  = 0x75,
    INTERACT_ID_FOREST_LOCKED_FENCE             = 0x76,
    INTERACT_ID_FOREST_LOCKED_LEVER_4_DOOR      = 0x77,
    INTERACT_ID_FOREST_DEAD_SKELETON            = 0x78,
    INTERACT_ID_TEXT_79                         = 0x79,
    INTERACT_ID_FOREST_LEVER_OPEN_BOSS_DOOR     = 0x7A,
    INTERACT_ID_FORET_LOCKED_FINAL_BOSS_DOOR    = 0x7B,
    INTERACT_ID_WATERWAY_DOOR_CLOSED            = 0x7C,
    NUM_INTERACTABLES
} InteractableID;

enum InteractableConfigFlag {
    ITEM_VANISH_OR_UPDATE_POSITION             = BIT(0),
    TEXT_SPOT_DESTROY_AFTER_INTERACTION        = BIT(1),
    TEXT_SPOT_DESTROY_IF_EVENT_FLAG_IS_SET     = BIT(2),
    TEXT_SPOT_DISABLE_IF_EVENT_FLAG_IS_NOT_SET = BIT(3),
    /**
     * Yes / No selection textbox
     */
    TEXT_SPOT_DO_ACTION_AFTER_SELECTING_OPTION = BIT(4),
    TEXT_SPOT_IF_YES_START_CUTSCENE            = BIT(5),
    TEXT_SPOT_IF_YES_CHANGE_ACTOR_STATE        = BIT(6),
    TEXT_SPOT_IF_YES_SET_EVENT_FLAG            = BIT(7),
    /**
     * Yes / No selection textbox
     */
    TEXT_SPOT_IF_YES_PULL_LEVER = BIT(8),
    ITEM_DOES_NOT_FLASH         = BIT(10),
    ITEM_INVISIBLE              = BIT(11)
};

/**
 * Accepts values from `InteractableConfigFlag` OR'ed together
 */
typedef u16 InteractableConfigFlags;

typedef struct InteractableConfig {
    u16 type;
    union {
        u16 item;
        u16 text_ID;
    };
    InteractableConfigFlags flags;
    u8 field_0x06[2];
    u32 event_flag;
    union {
        u16 cutscene_ID;
        u16 actor_ID;
        u16 pickable_item_flash_height;
    };
    u16 actor_variable_1;
    u16 trigger_size;
    u8 field_0x12[2];
} InteractableConfig;

// ID: 0x0027
typedef struct Interactable {
    ObjectHeader header;
    u8 field_0x04[4];
    Model* model;
    u8 field_0x28[12];
    f32 item_falling_target_height;
    /**
     * Index into `interactables_settings`. Will be value from `InteractableID`.
     */
    u16 idx;
    u8 field_0x3A[2];
    u32 interacting_with_interactable;
    u32 textbox_is_active;
    union {
        u16 item_doesnt_vanish_or_fall;
        u16 item_doesnt_flash;
    };
    u16 item_falling_height_multiplier;
    u16 current_flash_inactive_time;
    u8 field_0x4A[2];
    u32 time_when_flash_appears_over_item;
    RGBA primitive_color;
    u16 map_event_flag_ID;
    u16 item_model_settings_flags;
    u32 event_flag; // Save event flag that gets set when interacting with the item
    s16 trigger_X_size;
    s16 trigger_Z_size;
    union {
        pickableItemFlash* flash;
        MfdsState* textbox;
    };
    Vec3f position;
    ActorConfig* settings;
} Interactable;

void Interactable_Entrypoint(Interactable* self);
void Interactable_Init(Interactable* self);
void Interactable_Main(Interactable* self);
void Interactable_InitCheck(Interactable* self);
void Interactable_SelectTextboxOption(Interactable* self);
void Interactable_StopCheck(Interactable* self);
void Interactable_Destroy(Interactable* self);

enum InteractableFuncID {
    INTERACTABLE_INIT,
    INTERACTABLE_MAIN,
    INTERACTABLE_INIT_CHECK,
    INTERACTABLE_SELECT_TEXTBOX_OPTION,
    INTERACTABLE_STOP_CHECK,
    INTERACTABLE_DESTROY
};

typedef void (*InteractableFunc)(Interactable*);

/**
 * Table mapping interactables to their settings
 */
extern InteractableConfig interactables_settings[NUM_INTERACTABLES];

#endif
