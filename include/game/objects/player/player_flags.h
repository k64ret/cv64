#ifndef PLAYER_FLAGS_H
#define PLAYER_FLAGS_H

typedef enum player_flags {
    PLAYER_FLAG_RUNNING                                     = 0x00000001,
    PLAYER_FLAG_JOGGING                                     = 0x00000002,
    PLAYER_FLAG_WALKING                                     = 0x00000004,
    PLAYER_FLAG_CROUCHING                                   = 0x00000008,
    PLAYER_FLAG_PLAY_TIRED_SFX_WHILE_IDLING_WITH_LOW_HEALTH = 0x00000020, // Unused. Used in LoD
    PLAYER_FLAG_OPENING_DOOR                                = 0x00000040,
    PLAYER_FLAG_ACTION_PERFORMED     = 0x00000080, // Pressed C-Right over item or door
    PLAYER_FLAG_ATTACKING_FROM_ABOVE = 0x00000100,
    PLAYER_FLAG_ATTACKING_IN_LEVEL =
        0x00000200, // Attacking while in level with the enemy (i.e. not from above or below it)
    PLAYER_FLAG_ATTACKING_FROM_BELOW =
        0x00000400, // Assumption. When the enemy target graphic is visible. See 0x803D4164
    PLAYER_FLAG_MELEE_ATTACK     = 0x00000800,
    PLAYER_FLAG_B_ATTACK         = 0x00001000,
    PLAYER_FLAG_SUBWEAPON_ATTACK = 0x00002000,
    PLAYER_FLAG_AIRBORNE         = 0x00004000,
    PLAYER_FLAG_JUMP_UP          = 0x00008000,
    PLAYER_FLAG_JUMPING          = 0x00010000,
    PLAYER_FLAG_RECOVER_FROM_FALL_DAMAGE =
        0x00020000, // Recover / wake up right after taking damage that causes the player to fall over
    PLAYER_FLAG_DAMAGED =
        0x000C0000, // TODO: Verify this flag value is 100% correct. It seems to be (0x80000 | 0x40000)
    PLAYER_FLAG_STANDING_UP_AFTER_BEING_ATTACKED_DOWN =
        0x000E0000, // TODO: Verify this flag value is 100% correct. It seems to be (0x80000 | 0x40000 | 0x20000)
    PLAYER_FLAG_SLOW_DOWN             = 0x00100000, // See 0x80024158
    PLAYER_FLAG_SLIDING               = 0x00200000,
    PLAYER_FLAG_STO                   = 0x00400000, // Unused
    PLAYER_FLAG_VAMP                  = 0x08000000,
    PLAYER_FLAG_POISON                = 0x10000000,
    PLAYER_FLAG_TIRED                 = 0x20000000,
    PLAYER_FLAG_DAMAGED_AT_LEAST_ONCE = 0x40000000,
    PLAYER_FLAG_DEAD                  = 0x80000000
} player_flags_t;

#endif
