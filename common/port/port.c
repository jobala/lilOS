#include "../types.h"

void write_byte_to_port(u16int port, u8int value) 
{
    asm volatile ("outb %1, %0": : "dN" (port), "a" (value));
}

u8int read_byte_from_port(u16int port) 
{
    u8int ret;
    asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

u16int read_word_from_port(u16int port)
{
    u16int ret;
    asm volatile ("inw %1, %0": "=a" (ret) : "dN" (port));
    return ret;
}
