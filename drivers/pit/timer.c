#include "timer.h"
#include "../../descriptors/idt/isr.h"
#include "../monitor/monitor.h"
#include "../../common/port/port.h"

u32int tick = 0;

static void timer_callback(registers_t regs)
{
    tick++;
    monitor_write("Tick: ");
    monitor_write_dec(tick);
    monitor_write("\n");
}

void init_timer(u32int frequency)
{
    // Register handler callback
    register_interrupt_handler(IRQ0, &timer_callback);

    u32int divisor = 1193180 / frequency;
    write_byte_to_port(0x43, 0x36);

    u8int l = (u8int) (divisor & 0xFF);
    u8int h = (u8int) (divisor >> 8);

    write_byte_to_port(0x40, divisor & 0xFF);
    write_byte_to_port(0x40, divisor >> 8);
}