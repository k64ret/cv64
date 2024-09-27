#include "objects/cutscene/cs_film_reel.h"

// clang-format off

CSFilmReel_func CSFilmReel_functions[] = {
    CSFilmReel_CheckInitialConditions,
    CSFilmReel_Init,
    CSFilmReel_Loop,
    CSFilmReel_Destroy
};

// clang-format on

// clang-format off

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cs_film_reel/CSFilmReel_Entrypoint.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cs_film_reel/CSFilmReel_CheckInitialConditions.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cs_film_reel/CSFilmReel_Init.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cs_film_reel/CSFilmReel_Loop.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cs_film_reel/CSFilmReel_Destroy.s")

#pragma GLOBAL_ASM("../asm/nonmatchings/overlay/cs_film_reel/CSFilmReel_Draw.s")

// clang-format on
