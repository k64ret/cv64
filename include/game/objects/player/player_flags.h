#ifndef PLAYER_FLAGS_H
#define PLAYER_FLAGS_H

enum player_flags {
    RUNNING                                     = 0x00000001,
    JOGGING                                     = 0x00000002,
    WALKING                                     = 0x00000004,
    CROUCHING                                   = 0x00000008,
    PLAY_TIRED_SFX_WHILE_IDLING_WITH_LOW_HEALTH = 0x00000020, // Unused
    OPENING_DOOR                                = 0x00000040,
    ACTION_PERFORMED                            = 0x00000080, // pressed C-Right over item or door
    ATTACK_IS_ACTIVE                            = 0x00000200,
    MELEE_ATTACK                                = 0x00000800,
    B_ATTACK                                    = 0x00001000,
    SUBWEAPON_ATTACK                            = 0x00002000,
    AIRBORNE                                    = 0x00004000,
    JUMP_UP                                     = 0x00008000,
    JUMPING                                     = 0x00010000,
    SLOW_DOWN                                   = 0x00100000, // See 0x80024158
    SLIDING                                     = 0x00200000,
    STO                                         = 0x00400000, // Unused
    VAMP                                        = 0x08000000,
    POISON                                      = 0x10000000,
    TIRED                                       = 0x20000000,
    DAMAGED_AT_LEAST_ONCE                       = 0x40000000,
    DEAD                                        = 0x80000000
};

#endif
