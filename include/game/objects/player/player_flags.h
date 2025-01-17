#ifndef PLAYER_FLAGS_H
#define PLAYER_FLAGS_H

#include "cv64.h"

typedef enum cv64_player_flag {
    PLAYER_FLAG_RUNNING   = BIT(0),
    PLAYER_FLAG_JOGGING   = BIT(1),
    PLAYER_FLAG_WALKING   = BIT(2),
    PLAYER_FLAG_CROUCHING = BIT(3),
    /**
     * Unused. Used in LoD
     */
    PLAYER_FLAG_PLAY_TIRED_SFX_WHILE_IDLING_WITH_LOW_HEALTH = BIT(5),
    PLAYER_FLAG_OPENING_DOOR                                = BIT(6),
    /**
     * Pressed C-Right over item or door
     */
    PLAYER_FLAG_ACTION_PERFORMED     = BIT(7),
    PLAYER_FLAG_ATTACKING_FROM_ABOVE = BIT(8),
    /**
     * Attacking while in level with the enemy (i.e. not from above or below it)
     */
    PLAYER_FLAG_ATTACKING_IN_LEVEL = BIT(9),
    /**
     * Assumption. When the enemy target graphic is visible. See 0x803D4164
     */
    PLAYER_FLAG_ATTACKING_FROM_BELOW = BIT(10),
    PLAYER_FLAG_MELEE_ATTACK         = BIT(11),
    PLAYER_FLAG_B_ATTACK             = BIT(12),
    PLAYER_FLAG_SUBWEAPON_ATTACK     = BIT(13),
    PLAYER_FLAG_AIRBORNE             = BIT(14),
    PLAYER_FLAG_JUMP_UP              = BIT(15),
    PLAYER_FLAG_JUMPING              = BIT(16),
    /**
     * Recover / wake up right after taking damage that causes the player to fall over
     */
    PLAYER_FLAG_RECOVER_FROM_FALL_DAMAGE = BIT(17),
    /**
     * TODO: Verify this flag value is 100% correct. It seems to be (0x80000 | 0x40000)
     */
    PLAYER_FLAG_DAMAGED = BIT(18) | BIT(19),
    /**
     * TODO: Verify this flag value is 100% correct. It seems to be (0x80000 | 0x40000 | 0x20000)
     */
    PLAYER_FLAG_STANDING_UP_AFTER_BEING_ATTACKED_DOWN = BIT(17) | BIT(18) | BIT(19),
    /**
     * See 0x80024158
     */
    PLAYER_FLAG_SLOW_DOWN = BIT(20),
    PLAYER_FLAG_SLIDING   = BIT(21),
    /**
     * Unused
     */
    PLAYER_FLAG_STO                   = BIT(26),
    PLAYER_FLAG_VAMP                  = BIT(27),
    PLAYER_FLAG_POISON                = BIT(28),
    PLAYER_FLAG_TIRED                 = BIT(29),
    PLAYER_FLAG_DAMAGED_AT_LEAST_ONCE = BIT(30),
    PLAYER_FLAG_DEAD                  = BIT(31)
} cv64_player_flag_t;

#endif
