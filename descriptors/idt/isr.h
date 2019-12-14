#include "../../common/types.h"

typedef struct registers
{
    u32int ds;
    u32int edi, esi, ebp, ebx, edx, ecx, eax;
    u32int int_no, err_code;
    u32int eip, cs, eflags, useresp, ss;
} registers_t;