#ifndef MFDS_H
#define MFDS_H

/**
 * This header file contains structs that handle textboxes.
 */

#include "gfx/camera.h"
#include "gfx/model.h"
#include "gfx/graphic_container.h"
#include "objects/menu/lens.h"
#include "objects/menu/textboxAdvanceArrow.h"
#include "window.h"

/**
 * Converts an ASCII char to a character in the game's custom
 * text format
 */
#define ASCII_TO_CV64(ascii) (ascii - 0x1E)

// Special characters
#define PIXEL_HUD_0 0x68

// Control characters
#define CTRL_SET_COLOR(arg) (0xA200 | (arg & 0xFF))

#define TEXT_COLOR_WHITE 0
#define TEXT_COLOR_RED   1
#define TEXT_COLOR_BEIGE 2
#define TEXT_COLOR_BROWN 3

/**
 * Common menu text IDs
 *
 * Used in the `menu_text_ID` variable from `MfdsStateMiscTextIds`
 */
#define MENU_TEXT_KEY_CONFIG  1
#define MENU_TEXT_SOUND       2
#define MENU_TEXT_DEFAULT     3
#define MENU_TEXT_EXIT        4
#define MENU_TEXT_GAME_START  5
#define MENU_TEXT_DATA_COPY   6
#define MENU_TEXT_DATA_DELETE 7
#define MENU_TEXT_NEW_GAME    8
#define MENU_TEXT_USED_MEMORY 9 // Unused
#define MENU_TEXT_REINHARDT   10
#define MENU_TEXT_CARRIE      11
#define MENU_TEXT_CORNELL     12 // Unused
#define MENU_TEXT_COLLER      13 // Unused
#define MENU_TEXT_TYPE        14
#define MENU_TEXT_A           15
#define MENU_TEXT_B           16
#define MENU_TEXT_C           17
#define MENU_TEXT_STEREO      18
#define MENU_TEXT_MONOAURAL   19
#define MENU_TEXT_NO          20
#define MENU_TEXT_1           21
#define MENU_TEXT_2           22
#define MENU_TEXT_3           23
#define MENU_TEXT_OK_A        24
#define MENU_TEXT_CANCEL_B    25

#define TEXTBOX_OPTION_IDLE 0
#define TEXTBOX_OPTION_YES  1
#define TEXTBOX_OPTION_NO   2

typedef enum MfdsStateFlag {
    MFDS_FLAG_MENU_TEXT_ID_PRINTS_ITEM        = BIT(0),
    MFDS_FLAG_MENU_TEXT_ID_PRINTS_MENU_STRING = BIT(1),
    /**
     * This is used for the character names, so that they appear static while the text advances?
     */
    MFDS_FLAG_KEEP_SHOWING_LINE = BIT(2),
    MFDS_FLAG_00000008          = BIT(3),
    MFDS_FLAG_PRINT_NUMBER      = BIT(4),
    MFDS_FLAG_OPTION_SELECTION  = BIT(5),
    /**
     * Aka enable WindowWork
     */
    MFDS_FLAG_DISPLAY_LENS                    = BIT(6),
    MFDS_FLAG_ALLOC_TEXTBOX_IN_MENU_DATA_HEAP = BIT(14),
    MFDS_FLAG_8000                            = BIT(15),
    MFDS_FLAG_GAMEPLAYMENUMGR_TEXTBOX         = BIT(16),
    /**
     * Leaves a small space on the left of the text for the red selection arrow
     */
    MFDS_FLAG_LEAVE_SPACE_FOR_SELECTION_ARROW = BIT(17),
    /**
     * Allows the text to change the `primitive_color`'s alpha
     */
    MFDS_FLAG_ALLOW_TRANSPARENCY_CHANGE = BIT(18),
    /**
     * Allow updating the scale parameters from `MfdsState` struct
     */
    MFDS_FLAG_UPDATE_SCALE = BIT(19),
    /**
     * Forces the text speed to be 0
     */
    MFDS_FLAG_SLOW_TEXT_SPEED = BIT(20),
    /**
     * Allows the game to set the text speed from the `text_speed` field from `MfdsWork`.
     * Sets the text speed to 1 by default
     */
    MFDS_FLAG_ALLOW_VARIABLE_SPEED = BIT(21),
    /**
     * Forces the text speed to be 16. `MFDS_FLAG_ALLOW_VARIABLE_SPEED`
     * needs to be set in order for this flag to function properly.
     *
     * Setting this flag will also make the red textbox advance arrow to be automatically skipped.
     */
    MFDS_FLAG_FAST_TEXT_SPEED = BIT(22),
    /**
     * When set, the game will skip to the next string that should be printed.
     * This is often used to advance text during cutscenes
     */
    MFDS_FLAG_AUTO_SKIP_TEXT = BIT(23),
    MFDS_FLAG_UPDATE_STRING  = BIT(24),
    MFDS_FLAG_2000000        = BIT(25),
    MFDS_FLAG_CLOSE_TEXTBOX  = BIT(26),
    MFDS_FLAG_OPEN_TEXTBOX   = BIT(27),
    MFDS_FLAG_CLOSE_LENS     = BIT(28),
    MFDS_FLAG_OPEN_LENS      = BIT(29),
    /**
     * The text is completely processed
     */
    MFDS_FLAG_TEXT_IS_PARSED = BIT(30),
    MFDS_FLAG_HIDE_TEXTBOX   = BIT(31)
} MfdsStateFlag;

typedef enum MfdsWorkFlag {
    MFDS_WORK_FLAG_TEXT_SHOULD_SCROLL = BIT(0)
} MfdsWorkFlag;

typedef enum MfdsStateNumberVisualFlag {
    /**
     * Print number in hexadecimal. Unused.
     */
    NUMBER_VISUAL_FLAG_PRINT_IN_HEX                           = BIT(0),
    NUMBER_VISUAL_FLAG_PRINT_PLUS_SYMBOL_FOR_POSITIVE_NUMBERS = BIT(1),
    NUMBER_VISUAL_FLAG_ADD_LEADING_ZEROES                     = BIT(2),
    NUMBER_VISUAL_FLAG_ADD_NEW_LINE                           = BIT(3),
    NUMBER_VISUAL_FLAG_USE_GOLD_JEWEL_FONT                    = BIT(4),
    /**
     * Used in Renon's Shop after the gold amount
     */
    NUMBER_VISUAL_FLAG_ADD_G_AFTER_NUMBER = BIT(5)
} MfdsStateNumberVisualFlag;

typedef enum MfdsWorkArrowState {
    NOT_DISPLAYING_TEXTBOX_ARROW = 0,
    DISPLAYING_TEXTBOX_ARROW     = 1,
    TEXTBOX_ARROW_AUTO_ADVANCING = 2
} MfdsWorkArrowState;

typedef struct MfdsColorAnimData {
    u16 color;
    u16 time;
} MfdsColorAnimData;

// Real name: `mfds_color_animation_state`
typedef struct MfdsColorAnimationState {
    u8 field_0x00;
    u8 transition_time[4];
    u8 field_0x05[4];
    u8 transition_point[4];
    u8 field_0x0D[3];
    MfdsColorAnimData* color_anim_data[4];
    u8 max_transition_time[4];
} MfdsColorAnimationState;

// Real name: `mfds_work`
typedef struct MfdsWork {
    u16* parsed_text_ptr;
    s8 text_speed;
    u8 field_0x05;
    s16 indentation;
    /**
     * For the current printing character, the first byte is the Y pos offset,
     * and the second byte is the X pos offset
     */
    s16 Y_and_X_pos_offsets;
    /**
     * Timer for when a line is scrolling up to view the rest of the text
     */
    u8 scroll_timer;
    u8 palette;
    /**
     * Index in the `MfdsTexBuffer` entries array
     */
    s8 current_tex_buffer_entry;
    s8 textbox_advance_arrow_state;
    s16 time_until_auto_advance_textbox;
    u8 flags;
    u8 field_0x11;
    Vec2 current_position;
    Vec2 initial_position;
    u8 left_margin;
    u8 num_options;
    u8 current_option;
    u8 field_0x1D;
    u8 option_selection_IDs[6];
    u8 field_0x24[10];
    u8 display_time;
    u8 field_0x2F;
    MfdsColorAnimationState* color_anim_state;
} MfdsWork;

typedef struct MfdsTexBufferEntry {
    u8 field_0x00;
    u8 field_0x01;
    u16 text_char;
    s16 field_0x04;
    u8 field_0x06;
    u8 field_0x07;
    u8 field_0x08;
    u8 char_tex_buffer[128]; // Raw pixels for the text char
    u8 field_0x89;
} MfdsTexBufferEntry;

// Real name: `mfds_tex_buffer`
typedef struct MfdsTexBuffer {
    MfdsTexBufferEntry entries[5];
} MfdsTexBuffer;

typedef struct MfdsLtexBufferEntry {
    u16 text_char;
    u16 field_0x02;
    u8 field_0x04;
    u16 char_texture_raw_data[49];
    u8 field_0x67;
} MfdsLtexBufferEntry;

// Real name: `mfds_ltex_buffer`
typedef struct MfdsLtexBuffer {
    MfdsLtexBufferEntry entries[5];
} MfdsLtexBuffer;

// Real name: `mfds_dl_size`
typedef struct MfdsDlSize {
    u32 dlist_buffer_size;
    /**
     * Offset within the current graphic buffer where the dlists will start
     */
    u32 dlist_graphic_buffer_start_offset;
    /**
     * Offset within the current graphic buffer where the vertices will start
     */
    u32 vertices_graphic_buffer_start_offset;
} MfdsDlSize;

// Real name: `mfds_number_work`
typedef struct MfdsNumberWork {
    u16 text_buffer[13];
} MfdsNumberWork;

typedef union MfdsStateMiscTextIds {
    /**
     * Used for displaying some menu-related strings
     *
     * @note When using this field to know what string to display,
     * it won't be necessary to manually set the message pointer,
     * so we can call `textbox_setMessagePtr` with passing a NULL string pointer.
     */
    u8 menu_text_ID;
    /**
     * Used for displaying item names when picking them up. Real name: `item_no`
     */
    u8 item_ID;
} MfdsStateMiscTextIds;

typedef struct MfdsHeightWidthParams {
    s8 height;
    s8 width;
} MfdsHeightWidthParams;

// Real name: `mfds_state`
typedef struct MfdsState {
    u32 flags;
    Camera* display_camera;
    u16* text; // Real name: `str1`
    u16* item_amount_text;
    MfdsWork* mfds_work;
    Vec2 position;
    f32 position_Z;
    Vec2f scale;
    s32 number;
    s32 previous_number;
    u16 width;
    u8 previous_textbox_option;
    u8 textbox_option;
    u8 line;
    u8 field_0x31;
    u8 character_spacing;
    u8 left_margin;
    u8 palette;
    MfdsStateMiscTextIds misc_text_IDs[5];
    u8 number_visual_flags;
    u8 display_time;
    /**
     * @note The 11th entry of this array appears to be the number of vertical and horizontal
     *       vertices of the quadrilateral that encapsulates the text's texture.
     */
    MfdsHeightWidthParams height_and_width_per_line[11];
    u8 field_0x52;
    u8 field_0x53;
    u32 window_flags;
    f32 window_closing_speed;
    ObjLens* lens;
} MfdsState;

// ID: 0x0127
// Real name: `obj_mfds`
typedef struct ObjMfds {
    ObjectHeader header;
    u16 field_0x20;
    u16 field_0x22;
    u8 field_0x24[4];
    struct Model* model;
    u8 field_0x2C[8];
    GraphicContainerHeader* mfds_double; // Real name
    void* field_0x38;
    void* field_0x3C;
    struct TextboxAdvanceArrow* advance_arrow;
    void* field_0x44;
    void* field_0x48;
    void* field_0x4C;
    union {
        u16* mfds_menu_string; // Real name
        u16* mfds_item_form;   // Real name
    };
    MfdsNumberWork* number;
    MfdsColorAnimationState* color_anim_state;
    WindowWork* window;
    MfdsDlSize* dl_size;
    MfdsLtexBuffer* ltex_buffer;
    MfdsTexBuffer* tex_buffer;
    MfdsWork* work;
    MfdsState* state;
} ObjMfds;

extern MfdsState* textbox_create(ObjectHeader* parent_object, Camera* display_camera, u32 flags);
extern void
textbox_setDimensions(MfdsState* self, u8 line, u16 width, u8 param_4, u8 character_spacing);
extern void textbox_setPos(MfdsState* self, u16 x, u16 y, s32);
extern void
textbox_setMessagePtr(MfdsState* self, u16* text, u16* item_amount_number_text, s16 number);
extern void textbox_enableLens(MfdsState* self, u32 window_work_flags, f32 window_closing_speed);
extern u16* text_getMessageFromPool(u16* message_pool_base_ptr, s32 id);
extern void textbox_setScaleParameters(
    MfdsState* self,
    u8 number_of_vertical_vertices,
    u8 number_of_horizontal_vertices,
    f32 position_Z,
    f32 scale_X,
    f32 scale_Y,
    u8 allow_transparency_change,
    u8 leave_space_for_selection_arrow
);
extern void
text_convertSignedIntegerToText(u32 number, u16* dest, u8 number_of_chars, u32 number_visual_flags);
extern u16* text_findCharInString(u16* text, u16 char_to_find);
extern u16* convertUTF16ToCustomTextFormat(u16* text_buffer);
extern void textbox_setHeightAndWidth(MfdsState* self, u32 index, u8 text_height, u8 text_width);
extern MfdsState* gameplayCommonTextbox_getMapMessage(u16 text_ID, u8 textbox_display_time);

extern MfdsColorAnimData text_color_anim_data_table[4][8];

#endif
