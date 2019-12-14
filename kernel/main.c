#include "../common/types.h"
#include "../drivers/monitor/monitor.h"
#include "../descriptors/global_desc_table.h"

int main(void* mboot_ptr) {
    init_descriptor_tables();

    monitor_clear();
    monitor_write("Hello, World\nHello, lilOS");
}
