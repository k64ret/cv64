/**
 * @file controller_pak.c
 *
 * This file contains functions used to wrap functionality with the controller pak,
 * used for saving the game in the western versions of the game.
 */

#include "cv64.h"
#include "controller_pak.h"

extern OSPfs pfs[MAXCONTROLLERS];
extern OSPfs D_800D72F0_A85C0[MAXCONTROLLERS];
extern u8 contpak_uninserted[MAXCONTROLLERS];

static s32 check_inserted_err(u8 cont_no);

/**
 * Iterates through each controller checking if they have a controller pak inserted
 */
void contpak_get_inserted_status(OSContStatus cont_status[]) {
    s32 i;

    osContStartQuery(&controllerMsgQ);
    osRecvMesg(&controllerMsgQ, NULL, OS_MESG_BLOCK);
    osContGetQuery(cont_status);

    for (i = 0; i < MAXCONTROLLERS; i++) {
        contpak_uninserted[i] = BITS_HAS(cont_status[i].status, CONT_CARD_ON) ? FALSE : TRUE;
    }
}

void contpak_init_all(void) {
    s32 i;

    for (i = 0; i != MAXCONTROLLERS; i++) {
        if (BITS_HAS(controller_status[i].status, CONT_CARD_ON)) {
            osPfsInitPak(&controllerMsgQ, &pfs[i], i);
            contpak_uninserted[i] = FALSE;
        } else {
            contpak_uninserted[i] = TRUE;
        }
    }
}

s32 contpak_init(u8 cont_no) {
    if (BITS_HAS(controller_status[cont_no].status, CONT_CARD_ON)) {
        contpak_uninserted[cont_no] = FALSE;
        return osPfsInitPak(&controllerMsgQ, &pfs[cont_no], cont_no);
    }

    contpak_uninserted[cont_no] = TRUE;
    return check_inserted_err(cont_no);
}

s32 contpak_alloc_file(u8 cont_no, OSPfsState* pfs_state, int file_size, s32* file_no) {
    if (contpak_uninserted[cont_no] == FALSE) {
        return osPfsAllocateFile(
            &pfs[cont_no],
            pfs_state->company_code,
            pfs_state->game_code,
            (u8*) &pfs_state->game_name,
            (u8*) &pfs_state->ext_name,
            file_size,
            file_no
        );
    }

    return check_inserted_err(cont_no);
}

s32 contpak_delete_file(u8 cont_no, OSPfsState* pfs_state) {
    if (contpak_uninserted[cont_no] == FALSE) {
        return osPfsDeleteFile(
            &pfs[cont_no],
            pfs_state->company_code,
            pfs_state->game_code,
            (u8*) &pfs_state->game_name,
            (u8*) &pfs_state->ext_name
        );
    }

    return check_inserted_err(cont_no);
}

s32 contpak_find_file(u8 cont_no, OSPfsState* pfs_state, s32* file_no) {
    if (contpak_uninserted[cont_no] == FALSE) {
        return osPfsFindFile(
            &pfs[cont_no],
            pfs_state->company_code,
            pfs_state->game_code,
            (u8*) &pfs_state->game_name,
            (u8*) &pfs_state->ext_name,
            file_no
        );
    }

    return check_inserted_err(cont_no);
}

s32 contpak_get_file_state(u8 cont_no, s32 file_no, OSPfsState* pfs_state) {
    if (contpak_uninserted[cont_no] == FALSE) {
        return osPfsFileState(&pfs[cont_no], file_no, pfs_state);
    }

    return check_inserted_err(cont_no);
}

// maybe static since it's not referenced in any other translation unit
s32 contpak_get_num_files(u8 cont_no, s32* max_files, s32* files_used) {
    if (contpak_uninserted[cont_no] == FALSE) {
        return osPfsNumFiles(&pfs[cont_no], max_files, files_used);
    }

    return check_inserted_err(cont_no);
}

s32 contpak_get_free_blks(u8 cont_no, s32* remaining) {
    if (contpak_uninserted[cont_no] == FALSE) {
        return osPfsFreeBlocks(&pfs[cont_no], remaining);
    }

    return check_inserted_err(cont_no);
}

s32 contpak_is_plug(u8* bitpattern) {
    return osPfsIsPlug(&controllerMsgQ, bitpattern);
}

s32 contpak_read_file(u8 cont_no, s32 file_no, int offset, int nbytes, u8* buf) {
    if (contpak_uninserted[cont_no] == FALSE) {
        return osPfsReadWriteFile(&pfs[cont_no], file_no, PFS_READ, offset, nbytes, buf);
    }

    return check_inserted_err(cont_no);
}

s32 contpak_write_file(u8 cont_no, s32 file_no, int offset, int nbytes, u8* buf) {
    if (contpak_uninserted[cont_no] == FALSE) {
        return osPfsReadWriteFile(&pfs[cont_no], file_no, PFS_WRITE, offset, nbytes, buf);
    }

    return check_inserted_err(cont_no);
}

/**
 * Checks for the following cases:
 *
 * - If a device other than the controller pak is inserted, it checks if it's a rumble pak.
 *   If it is, `PFS_ERR_DEVICE` is returned.
 *
 * - If a controller pak is indeed inserted, then it must be damaged or not connected properly,
 *   so `PFS_ERR_ID_FATAL` is returned.
 *
 * - Anything else means that a device isn't connected into the controller.
 */
s32 contpak_check_rumble_pak(u8 cont_no) {
    s32 ret;

    if (contpak_uninserted[cont_no] == FALSE) {
        if (osMotorInit(&controllerMsgQ, &pfs[cont_no], cont_no) == 0) {
            ret = PFS_ERR_DEVICE;
        } else {
            contpak_init(CONT_0);
            ret = PFS_ERR_ID_FATAL;
        }

        return ret;
    }

    return check_inserted_err(cont_no);
}

/**
 * If a controller pak is connected, but there was an error during its operation,
 * this function will return either:
 *
 * - `PFS_ERR_NEW_PACK`, if a different controller pak was inserted.
 *
 * - `PFS_ERR_NOPACK`, if the controller pak was disconnected.
 */
s32 check_inserted_err(u8 cont_no) {
    contpak_get_inserted_status(controller_status);

    if (BITS_HAS(controller_status[cont_no].status, CONT_CARD_ON)) {
        return PFS_ERR_NEW_PACK;
    }

    return PFS_ERR_NOPACK;
}

void contpak_8001AAA8(u8 cont_no) {
    D_800D72F0_A85C0[cont_no] = pfs[cont_no];
}

void contpak_8001AB18(u8 cont_no) {
    pfs[cont_no] = D_800D72F0_A85C0[cont_no];
}

s32 contpak_repair_id(u8 cont_no) {
    return osPfsRepairId(&pfs[cont_no]);
}
