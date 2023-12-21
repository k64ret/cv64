#ifndef ULTRA64_H
#define ULTRA64_H

#include "ultratypes.h"
// #include "exception.h"
// #include "rcp.h"
// #include "thread.h"
// #include "convert.h"
// #include "time.h"
// #include "message.h"
// #include "sptask.h"
// #include "gu.h"
// #include "vi.h"
// #include "pi.h"
#include "controller.h"
// #include "printf.h"
#include "mbi.h"
// #include "pfs.h"
// #include "motor.h"
// #include "R4300.h"
// #include "ucode.h"

#define VTX(x, y, z, s, t, crnx, cgny, cbnz, a)                                \
    {                                                                          \
        {                                                                      \
            {x, y, z}, 0, {s, t}, { crnx, cgny, cbnz, a }                      \
        }                                                                      \
    }

#endif
