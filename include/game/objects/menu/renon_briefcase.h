#include "cv64.h"
#include "object.h"
#include "gfx/model_info.h"
#include "animation.h"

#define PLAY_SD_RENON_BRIEFCASE_SPIN_2  self->field_0x34[1]
#define RENON_BRIEFCASE_NUMBER_OF_LIMBS 3
#define RENON_BRIEFCASE_ANIM_SPEED      1.0f

/**
 * ID: 0x213C
 */
typedef struct cv64_ovl_renonbriefcase {
    cv64_object_hdr_t header;
    u8 field_0x20[8];
    cv64_model_inf_t* model;
    u8 field_0x2C[8];
    union {
        struct {
            u32 current_cutscene_time;
            animation_info anim_info;
            u8 field_0x4C[40];
        };
        u32 field_0x34[16];
    };
} cv64_ovl_renonbriefcase_t;

void cv64_ovl_renonbriefcase_entrypoint(cv64_ovl_renonbriefcase_t* self);
void cv64_ovl_renonbriefcase_init(cv64_ovl_renonbriefcase_t* self);
void cv64_ovl_renonbriefcase_loop(cv64_ovl_renonbriefcase_t* self);
void cv64_ovl_renonbriefcase_destroy(cv64_ovl_renonbriefcase_t* self);

extern const u32 RENON_BRIEFCASE_LOWER_LID;
extern const u32 RENON_BRIEFCASE_UPPER_LID;

typedef void (*cv64_ovl_renonbriefcase_func_t)(cv64_ovl_renonbriefcase_t*);
