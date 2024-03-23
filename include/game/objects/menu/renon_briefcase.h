#include "cv64.h"
#include "object.h"
#include "gfx/model_info.h"
#include "animation.h"

typedef struct cv64_ovl_renonbriefcase {
    cv64_object_hdr_t header;
    u8 field_0x20[8];
    cv64_model_inf_t* model;
    u8 field_0x2C[8];
    s32 current_cutscene_time;
    animationMgr animMgr;
    u8 field_0x68[12];
} cv64_ovl_renonbriefcase_t;

typedef void (*cv64_ovl_renonbriefcase_func_t)(cv64_ovl_renonbriefcase_t*);
