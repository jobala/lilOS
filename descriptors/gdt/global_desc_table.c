#include "../../common/types.h"
#include "global_desc_table.h"
#include "../idt/interrupt_table.h"

extern void gdt_flush(u32int);

static void  init_gdt();
static void  gdt_set_gate(s32int, u32int, u32int, u8int, u8int);

gdt_entry_t gdt_entries[3];
gdt_ptr_t   gdt_ptr;

void init_descriptor_tables()
{
    init_gdt();
    init_idt();
}

static void init_gdt()
{
    gdt_ptr.limit = (sizeof(gdt_entry_t) * 3) - 1;
    gdt_ptr.base  = (u32int) &gdt_entries;

    gdt_set_gate(0, 0, 0, 0, 0);
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    gdt_flush((u32int) &gdt_ptr);
}

static void gdt_set_gate(s32int num, u32int base, u32int limit, u8int access, u8int gran)
{
    gdt_entries[num].base_low = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high   = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;

    gdt_entries[num].granularity |= gran & 0xF0;
    gdt_entries[num].access  = access;
}
