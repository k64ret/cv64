#ifndef CUTSCENE_MGR_H
#define CUTSCENE_MGR_H

#include "cutscene.h"
#include "CSFilmReel.h"

// ID: 0x002A
typedef struct {
    ObjectHeader header;
    u8 field_0x20[32];
    CSFilmReel* csFilmReel;
    /**
     * NOTE:
     * Follows the cutscene ID listing WITHOUT the empty slots (for example,
     * cutscene 0x3C here is 0x32)
     */
    u32 cutscene_ID;
    cutscene* cutscene_object;
    u8 field_0x4C[40];
} cutsceneMgr;

void cutsceneMgr_entrypoint(cutsceneMgr* self);
void cutsceneMgr_main(cutsceneMgr* self);
void cutsceneMgr_createCutscene(cutsceneMgr* self);
void cutsceneMgr_setCameraClippingAndScissoring(cutsceneMgr* self);
void cutsceneMgr_loop(cutsceneMgr* self);
void cutsceneMgr_stopCutscene(cutsceneMgr* self);

typedef enum cv64_cutsceneMgr_func_id {
    CUTSCENEMGR_MAIN,
    CUTSCENEMGR_CREATE_CUTSCENE,
    CUTSCENEMGR_SET_CAMERA_CLIPPING_AND_SCISSORING,
    CUTSCENEMGR_LOOP,
    CUTSCENEMGR_STOP_CUTSCENE
} cv64_cutsceneMgr_func_id_t;

typedef void (*cv64_cutscenemgr_func_t)(cutsceneMgr*);

extern cutsceneMgr* ptr_cutsceneMgr;

#endif
