#ifndef KONAMI_LOGO_H
#define KONAMI_LOGO_H

#include "gfx/model_info.h"
#include "object.h"

// ID: 0x000E
typedef struct {
    object_header_t header;
    u8 padding1[4];
    model_info *model;
    u8 padding2[OBJECT_SIZE - 0x28];
} konamiLogo;

void konamiLogo_entrypoint(konamiLogo *self);       // 0x801cfcd0
void konamiLogo_checkButtonPress(konamiLogo *self); // 0x801cfd40
void konamiLogo_init(konamiLogo *self);             // 0x801cfda0
void konamiLogo_fade_in(konamiLogo *self);          // 0x801cfe7c
void konamiLogo_wait(konamiLogo *self);             // 0x801cff08
void konamiLogo_fade_out(konamiLogo *self);         // 0x801cff7c
void konamiLogo_KCEK_fade_in(konamiLogo *self);     // 0x801cffdc
void konamiLogo_KCEK_wait(konamiLogo *self);        // 0x801d0058
void konamiLogo_KCEK_fade_out(konamiLogo *self);    // 0x801d00e0

enum konamiLogo_functions_IDs {
    KONAMILOGO_INIT,
    KONAMILOGO_FADE_IN,
    KONAMILOGO_WAIT,
    KONAMILOGO_FADE_OUT,
    KONAMILOGO_KCEK_FADE_IN,
    KONAMILOGO_KCEK_WAIT,
    KONAMILOGO_KCEK_FADE_OUT,
    FUNC_8000E860
};

void (*konamiLogo_functions[])(konamiLogo *self) = {
    konamiLogo_init,          konamiLogo_fade_in,
    konamiLogo_wait,          konamiLogo_fade_out,
    konamiLogo_KCEK_fade_in,  konamiLogo_KCEK_wait,
    konamiLogo_KCEK_fade_out, func_8000E860};

// These variables need to be extern'd,
// otherwise the code will vary slightly and won't match.
extern const u32 KONAMI_LOGO_DL;
extern const u32 KCEK_LOGO_DL;

#endif
