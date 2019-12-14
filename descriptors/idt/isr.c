#include "../../common/types.h"
#include  "../../drivers/monitor/monitor.h"
#include "isr.h"

void isr_handler(registers_t regs)
{
    monitor_write("Received an interrupt: ");
    monitor_write_hex(regs.int_no);
    monitor_write("\n");
}

