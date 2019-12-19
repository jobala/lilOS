#include "../common/types.h"
#include "../drivers/monitor/monitor.h"
#include "../drivers/pit/timer.h"
#include "../descriptors/gdt/global_desc_table.h"

int main(void* mboot_ptr) {
    init_descriptor_tables();

    // monitor_clear();
    init_timer(100);
}
