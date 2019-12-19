#include "../../common/types.h"

#define IRQ0    32
#define IRQ1    33

typedef struct registers
{
    u32int ds;
    u32int edi, esi, ebp, ebx, edx, ecx, eax;
    u32int err_code, int_no;
    u32int eip, cs, eflags, useresp, ss;
} registers_t;

typedef void (*isr_t)(registers_t);
void register_interrupt_handler(u8int entry, isr_t handler);
