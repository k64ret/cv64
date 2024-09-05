/**
 * @file controller_pak.c
 *
 * This file contains functions used to wrap functionality with the controller pak,
 * used for saving the game in the western versions of the game.
 */

#include "controller_pak.h"

extern OSPfs pfs[MAXCONTROLLERS];
extern OSPfs D_800D72F0_A85C0[MAXCONTROLLERS];
extern u8 contPak_notInserted[MAXCONTROLLERS];

s32 contPak_getInsertedStatus(OSContStatus cont_status[]) {
    s32 i;

    osContStartQuery(&controllerMsgQ);
    osRecvMesg(&controllerMsgQ, NULL, OS_MESG_BLOCK);
    osContGetQuery(cont_status);

    for (i = 0; i < MAXCONTROLLERS; i++) {
        contPak_notInserted[i] = (cont_status[i].status & CONT_CARD_ON) ? FALSE : TRUE;
    }
}

void contPak_initAllPaks() {
    s32 i;

    for (i = 0; i != MAXCONTROLLERS; i++) {
        if (controller_status[i].status & CONT_CARD_ON) {
            osPfsInitPak(&controllerMsgQ, &pfs[i], i);
            contPak_notInserted[i] = FALSE;
        } else {
            contPak_notInserted[i] = TRUE;
        }
    }
}

s32 contPak_initPak(u8 cont_number) {
    if (controller_status[cont_number].status & CONT_CARD_ON) {
        contPak_notInserted[cont_number] = FALSE;
        return osPfsInitPak(&controllerMsgQ, &pfs[cont_number], cont_number);
    } else {
        contPak_notInserted[cont_number] = TRUE;
        return contPak_checkInsertedStatus(cont_number);
    }
}

s32 contPak_allocateFile(u8 cont_number, OSPfsState* pfs_state, int file_size, s32* file_no) {
    if (contPak_notInserted[cont_number] == FALSE) {
        return osPfsAllocateFile(
            &pfs[cont_number],
            pfs_state->company_code,
            pfs_state->game_code,
            &pfs_state->game_name,
            &pfs_state->ext_name,
            file_size,
            file_no
        );
    } else {
        return contPak_checkInsertedStatus(cont_number);
    }
}

s32 contPak_deleteFile(u8 cont_number, OSPfsState* pfs_state) {
    if (contPak_notInserted[cont_number] == FALSE) {
        return osPfsDeleteFile(
            &pfs[cont_number],
            pfs_state->company_code,
            pfs_state->game_code,
            &pfs_state->game_name,
            &pfs_state->ext_name
        );
    } else {
        return contPak_checkInsertedStatus(cont_number);
    }
}

s32 contPak_findFile(u8 cont_number, OSPfsState* pfs_state, s32* file_no) {
    if (contPak_notInserted[cont_number] == FALSE) {
        return osPfsFindFile(
            &pfs[cont_number],
            pfs_state->company_code,
            pfs_state->game_code,
            &pfs_state->game_name,
            &pfs_state->ext_name,
            file_no
        );
    } else {
        return contPak_checkInsertedStatus(cont_number);
    }
}

s32 contPak_getFileState(u8 cont_number, s32 file_no, OSPfsState* pfs_state) {
    if (contPak_notInserted[cont_number] == FALSE) {
        osPfsFileState(&pfs[cont_number], file_no, pfs_state);
    } else {
        return contPak_checkInsertedStatus(cont_number);
    }
}

s32 contPak_getNumFiles(u8 cont_number, s32* max_files, s32* files_used) {
    if (contPak_notInserted[cont_number] == FALSE) {
        osPfsNumFiles(&pfs[cont_number], max_files, files_used);
    } else {
        return contPak_checkInsertedStatus(cont_number);
    }
}

s32 contPak_getFreeBlocks(u8 cont_number, s32* remaining) {
    if (contPak_notInserted[cont_number] == FALSE) {
        return osPfsFreeBlocks(&pfs[cont_number], remaining);
    } else {
        return contPak_checkInsertedStatus(cont_number);
    }
}

s32 contPak_IsPlug(u8* bitpattern) {
    return osPfsIsPlug(&controllerMsgQ, bitpattern);
}

s32 contPak_readFile(u8 cont_number, s32 file_no, int offset, int nbytes, u8* data_buffer) {
    if (contPak_notInserted[cont_number] == FALSE) {
        return osPfsReadWriteFile(
            &pfs[cont_number], file_no, PFS_READ, offset, nbytes, data_buffer
        );
    } else {
        return contPak_checkInsertedStatus(cont_number);
    }
}

s32 contPak_writeFile(u8 cont_number, s32 file_no, int offset, int nbytes, u8* data_buffer) {
    if (contPak_notInserted[cont_number] == FALSE) {
        osPfsReadWriteFile(&pfs[cont_number], file_no, PFS_WRITE, offset, nbytes, data_buffer);
    } else {
        return contPak_checkInsertedStatus(cont_number);
    }
}

s32 contPak_checkRumblePak(u8 cont_number) {
    s32 ret;

    if (contPak_notInserted[cont_number] == FALSE) {
        if (osMotorInit(&controllerMsgQ, &pfs[cont_number], cont_number) == 0) {
            ret = PFS_ERR_DEVICE;
        } else {
            contPak_initPak(CONT_0);
            ret = PFS_ERR_ID_FATAL;
        }
        return ret;
    }

    return contPak_checkInsertedStatus(cont_number);
}

s32 contPak_checkInsertedStatus(u8 cont_number) {
    contPak_getInsertedStatus(controller_status);
    if (controller_status[cont_number].status & CONT_CARD_ON) {
        return PFS_ERR_NEW_PACK;
    } else {
        return PFS_ERR_NOPACK;
    }
}

void contPak_8001aaa8(u8 cont_number) {
    D_800D72F0_A85C0[cont_number] = pfs[cont_number];
}

void contPak_8001ab18(u8 cont_number) {
    pfs[cont_number] = D_800D72F0_A85C0[cont_number];
}

s32 contPak_repairID(u8 cont_number) {
    return osPfsRepairId(&pfs[cont_number]);
}
