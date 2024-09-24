#ifndef TEXTBOX_ADVANCE_ARROW_H
#define TEXTBOX_ADVANCE_ARROW_H

#include "object.h"
#include "gfx/model_info.h"
#include "gfx/light.h"
#include "window.h"

// ID: 0x2138
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[4];
    Model* model;
    light* arrow_light;
    u8 field_0x2C[12];
    s32 fade_timer;
    u8 field_0x3C[28];
    s32 disable_arrow;
    u8 field_0x5C[24];
} textboxAdvanceArrow;

void textboxAdvanceArrow_entrypoint(textboxAdvanceArrow* self);
void textboxAdvanceArrow_init(textboxAdvanceArrow* self);
void textboxAdvanceArrow_loop(textboxAdvanceArrow* self);
void textboxAdvanceArrow_destroy(textboxAdvanceArrow* self);

typedef void (*cv64_ovl_textboxadvancearrow_func_t)(textboxAdvanceArrow*);

extern const u32 TEXTBOX_ADVANCE_ARROW_DL;

#endif
