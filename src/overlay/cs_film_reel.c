#include "cv64.h"

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cs_film_reel/CSFilmReelDraw_entrypoint.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cs_film_reel/CSFilmReelDraw_checkInitialConditions.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cs_film_reel/CSFilmReelDraw_init.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cs_film_reel/CSFilmReelDraw_loop.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cs_film_reel/CSFilmReelDraw_destroy.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cs_film_reel/CSFilmReelDraw_draw.s")

// clang-format on
