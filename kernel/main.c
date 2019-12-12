#include "../common/types.h"
#include "../drivers/monitor/monitor.h"

int main(void* mboot_ptr) {
    monitor_clear();
    monitor_write("Hello, World\nHello, lilOS");
}
