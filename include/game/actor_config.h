#ifndef ACTOR_CONFIG_H
#define ACTOR_CONFIG_H

#include "math.h"

/**
 * Encodes the spawn difficulty and spawn settings values so that it can be set into
 * field `difficulty__spawn_settings` of `ActorConfig`
 */
#define DIFFICULTY_AND_SPAWN_SETTINGS(difficulty, spawn_settings)                                  \
    (((difficulty << 4) & 0xF0) | (spawn_settings & 0x0F))

/**
 * Obtains the difficulty value from field `difficulty__spawn_settings` of `ActorConfig`
 */
#define GET_SPAWN_DIFFICULTY(difficulty__spawn_settings) ((difficulty__spawn_settings >> 4) & 3)

typedef enum ActorConfigDifficulty {
    SPAWN_ON_ALL_DIFFICULTIES,
    SPAWN_ON_EASY,
    SPAWN_ON_NORMAL,
    SPAWN_ON_HARD
} ActorConfigDifficulty;

typedef enum ActorConfigSpawnSettings {
    /**
     * If set, an actor will automatically become "spawnable only once"
     */
    SPAWN_ONLY_ONCE_AUTOMATICALLY = 0x00,
    /**
     * Spawn regardless of the value from `ActorConfigSpawnFlags`
     *
     * @note `ENABLE_ALTERNATE_BETWEEN_SPAWN_AND_DESPAWN` and `ALTERNATE_BETWEEN_SPAWN_AND_DESPAWN`
     * are still checked regardless
     */
    SPAWN_WITHOUT_CONDITIONS = 0x01,
    /**
     * If set, an actor will become "spawnable only once" when flag `SPAWN_ONLY_ONCE` from `ActorConfigSpawnFlags`
     * is set
     */
    ALLOW_SPAWN_ONLY_ONCE_MANUALLY = 0x02,
    /**
     * If set, everytime an actor is requested to be spawned, it will alternate between being able to spawn and not
     * in a repeated cycle.
     *
     * For example, if an actor spawns and then it despawns, the actor won't spawn that second time.
     * However, if you attempt to spawn it once more, it will despawn. And so on repeating the cycle.
     *
     * @note For actors *not* part of rooms, this behaviour is slightly bugged.
     * The bug makes the game only able to despawn the actor if the player first enters its spawn radius for a single frame.
     * The game checks if new actors should spawn everytime the player moves, so if the player moves for at least one more frame,
     * the actor in question will spawn again.
     */
    ENABLE_ALTERNATE_BETWEEN_SPAWN_AND_DESPAWN = 0x04,
    /**
     * Marks the end of an actor list
     */
    SETTING_END_OF_ACTOR_LIST = 0x80
} ActorConfigSpawnSettings;

typedef enum ActorConfigSpawnFlags {
    /**
     * Automatically set when an actor spawns, assuming it's *not* part of rooms
     * Allows the usage of `SPAWN_ONLY_ONCE_AUTOMATICALLY` from `ActorConfigSpawnSettings`
     */
    ALLOW_SPAWN_ONLY_ONCE_AUTOMATICALLY = 0x01,
    /**
     * Allows the usage of `ALLOW_SPAWN_ONLY_ONCE_MANUALLY` from `ActorConfigSpawnSettings`
     */
    SPAWN_ONLY_ONCE = 0x02,
    /**
     * An actor is currently spawned
     */
    SPAWNED = 0x04,
    /**
     * See `ENABLE_ALTERNATE_BETWEEN_SPAWN_AND_DESPAWN` from `ActorConfigSpawnSettings`
     */
    ALTERNATE_BETWEEN_SPAWN_AND_DESPAWN = 0x08
} ActorConfigSpawnFlags;

typedef struct ActorConfig {
    /**
     * Actor's initial position
     */
    Vec3 position;
    /**
     * The actor's object ID
     */
    s16 actor_ID;
    /**
     * The meaning of these three variables depend on the actor
     * that uses them
     */
    u16 variable_1;
    u16 variable_2;
    u16 variable_3;
    union {
        struct {
            /**
             * - difficulty: Determines if an actor should only spawn on a specific difficulty settings,
             *               or if it should spawn no matter the difficulty. 4 upper bits
             *
             * - spawn_settings: Used in conjuction with field `spawn_flags` to configure the actor's
             *                   spawn behaviour. See `ActorConfigSpawnSettings`. 4 lower bits
             */
            u8 difficulty__spawn_settings;

            /**
             * - spawn_flags:    Used in conjuction with field `spawn_settings` to configure the actor's
             *                   spawn behaviour. See `ActorConfigSpawnFlags`
             */
            u8 spawn_flags;
        };
        /**
         * Fields `difficulty__spawn_settings` and `spawn_flags` combined
         */
        u16 settings;
    };
} ActorConfig;

#endif
