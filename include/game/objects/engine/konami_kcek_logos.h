#ifndef KONAMI_KCEK_LOGOS_H
#define KONAMI_KCEK_LOGOS_H

#include "gfx/model_info.h"
#include "object.h"

// ID: 0x000E
typedef struct cv64_ovl_konamilogo {
    cv64_object_hdr_t header;
    u8 padding1[4];
    cv64_model_inf_t* model;
    u8 padding2[OBJECT_SIZE - 0x28];
} cv64_ovl_konamilogo_t;

void cv64_ovl_konamilogo_entrypoint(cv64_ovl_konamilogo_t* self); // 0x801cfcd0
void cv64_ovl_konamilogo_check_btn_press(cv64_ovl_konamilogo_t* self
);                                                              // 0x801cfd40
void cv64_ovl_konamilogo_init(cv64_ovl_konamilogo_t* self);     // 0x801cfda0
void cv64_ovl_konamilogo_fade_in(cv64_ovl_konamilogo_t* self);  // 0x801cfe7c
void cv64_ovl_konamilogo_wait(cv64_ovl_konamilogo_t* self);     // 0x801cff08
void cv64_ovl_konamilogo_fade_out(cv64_ovl_konamilogo_t* self); // 0x801cff7c
void cv64_ovl_konamilogo_kcek_fade_in(cv64_ovl_konamilogo_t* self
);                                                               // 0x801cffdc
void cv64_ovl_konamilogo_kcek_wait(cv64_ovl_konamilogo_t* self); // 0x801d0058
void cv64_ovl_konamilogo_kcek_fade_out(cv64_ovl_konamilogo_t* self
); // 0x801d00e0

typedef void (*cv64_ovl_konamilogo_func_t)(cv64_ovl_konamilogo_t*);

typedef enum cv64_ovl_konamilogo_func_id {
    KONAMILOGO_INIT,
    KONAMILOGO_FADE_IN,
    KONAMILOGO_WAIT,
    KONAMILOGO_FADE_OUT,
    KONAMILOGO_KCEK_FADE_IN,
    KONAMILOGO_KCEK_WAIT,
    KONAMILOGO_KCEK_FADE_OUT,
    FUNC_8000E860
} cv64_ovl_konamilogo_func_id_t;

// These variables need to be extern'd,
// otherwise the code will vary slightly and won't match.
extern const u32 KONAMI_LOGO_DL;
extern const u32 KCEK_LOGO_DL;

#endif // KONAMI_KCEK_LOGOS_H
