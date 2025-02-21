#ifndef TEXTBOX_ADVANCE_ARROW_H
#define TEXTBOX_ADVANCE_ARROW_H

#include "object.h"
#include "gfx/model.h"
#include "gfx/light.h"
#include "window.h"

// ID: 0x2138
typedef struct {
    ObjectHeader header;
    u8 field_0x20[4];
    struct Model* model;
    FigureLight* arrow_light;
    u8 field_0x2C[12];
    s32 fade_timer;
    u8 field_0x3C[28];
    s32 disable_arrow;
    u8 field_0x5C[24];
} TextboxAdvanceArrow;

void TextboxAdvanceArrow_entrypoint(TextboxAdvanceArrow* self);
void TextboxAdvanceArrow_init(TextboxAdvanceArrow* self);
void TextboxAdvanceArrow_loop(TextboxAdvanceArrow* self);
void TextboxAdvanceArrow_destroy(TextboxAdvanceArrow* self);

typedef void (*cv64_ovl_textboxadvancearrow_func_t)(TextboxAdvanceArrow*);

extern const u32 TEXTBOX_ADVANCE_ARROW_DL;

#endif
