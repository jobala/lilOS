#include "../common/types.h"
#include "../drivers/monitor/monitor.h"
#include "../descriptors/gdt/global_desc_table.h"

int main(void* mboot_ptr) {
    init_descriptor_tables();

    monitor_clear();
    monitor_write("Hello World\n");

    asm volatile("int $0x28");
    asm volatile("int $0x4");
}
