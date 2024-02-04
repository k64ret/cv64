#ifndef TEXTBOX_ADVANCE_ARROW_H
#define TEXTBOX_ADVANCE_ARROW_H

#include "object.h"
#include "gfx/model_info.h"
#include "gfx/struct_47.h"
#include "window.h"

// ID: 0x2138
typedef struct {
    cv64_object_hdr_t header;
    u8 field_0x20[4];
    cv64_model_inf_t* model;
    struct_47* field_0x28;
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

void (*textboxAdvanceArrow_functions[])(textboxAdvanceArrow* self) = {
    textboxAdvanceArrow_init, textboxAdvanceArrow_loop,
    textboxAdvanceArrow_destroy};

extern const u32 TEXTBOX_ADVANCE_ARROW_DL;

#endif
