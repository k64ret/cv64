#ifndef CV64_H
#define CV64_H

#define CV64_BIT(num) (1 << (num))

#include "ultratypes.h"

typedef u8 Addr[];

extern s16 code_execution_max_delay; // Maybe put this in another header

extern void end_master_display_list(void);

#endif // CV64_H
