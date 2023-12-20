#ifndef C64_H
#define C64_H

#define C64_BIT(num) (1 << (num))

#include "ultratypes.h"

typedef u8 Addr[];

extern s16 code_execution_max_delay; // Maybe put this in another header

#endif // C64_H