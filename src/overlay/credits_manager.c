/*
 * File: creditsMgr.c
 * Description: Creates the credits cutscene and resets the game once it's over.
 * Associated objects: 0x201B
 *
 * Mapped by the TLB? = Yes
 */

#include "objects/engine/creditsMgr.h"
#include "objects/engine/DMAMgr.h"
#include "atari.h"
#include "system_work.h"
#include "gamestate.h"
#include "cutscene_ID.h"

void (*cv64_ovl_creditsmgr_funcs[])(creditsMgr* self
) = {creditsMgr_init, creditsMgr_loop, creditsMgr_exit};

void creditsMgr_entrypoint(creditsMgr* self) {
    ENTER(self, cv64_ovl_creditsmgr_funcs);
}

// https://decomp.me/scratch/JvchH
void creditsMgr_init(creditsMgr* self) {
    u8 i;

    if (((*fade_isFading)() == FALSE) && (sys.file_load_array_ID == 0) &&
        (ptr_DMAMgr->DMAChunkMgr != NULL)) {
        (*fade_setSettings)(FADE_IN, 30, 0, 0, 0);
        sys.cutscene_flags = 0;
        // Both variables have to be assigned the value like this so that
        // it can match (which prevents a t1 vs t0 regswap)
        sys.cutscene_ID = sys.entrance_cutscene_ID = CUTSCENE_ID_NONE;
        (*atari_work_table_init)();
        for (i = 0; i < 16; i++) {
            self->field_0x34[i] = 0;
        }
        if ((*objectList_findFirstObjectByID)(CUTSCENE_CUTSCENEMGR) == NULL) {
            (*object_createAndSetChild)(self, CUTSCENE_CUTSCENEMGR);
        }
        sys.field89_0x2644c = 0;
        sys.cutscene_ID = CUTSCENE_ID_CREDITS;
        (*object_curLevel_goToNextFuncAndClearTimer)(
            self->header.current_function, &self->header.functionInfo_ID
        );
    }
}

// https://decomp.me/scratch/AgrnA
void creditsMgr_loop(creditsMgr* self) {
    if (sys.cutscene_ID == CUTSCENE_ID_NONE &&
        (*objectList_findFirstObjectByID)(CUTSCENE_CUTSCENE_CREDITS) == NULL) {
        // In practice all the code below this line goes unused
        // because the credits cutscene switches gamestate before
        // creditsMgr has a chance to do so

        self->field_0x34[3] = 2;
        if (1) {
        } // Needed for matching

        if (self->field_0x34[3] == 2) {
            (*fade_setSettings)(FADE_OUT, 30, 0, 0, 0);
            (*object_curLevel_goToNextFuncAndClearTimer)(
                self->header.current_function, &self->header.functionInfo_ID
            );
        }
    }
}

void creditsMgr_exit(creditsMgr* self) {
    if ((*fade_isFading)() == FALSE) {
        (*gamestate_change)(GAMESTATE_KONAMI_LOGO);
    }
}
