# Getting Started

This is a step-by-step guide for setting up your dev environment and testing LilOS on Windows (and Linux).

## Emmulator Setup
- install [XMing Server](https://sourceforge.net/projects/xming/) so as to run the Bosch emulator on WSL
- For XMing to connect with Bosch emulator, you need to export this environment (you can add it in your .`~/zshrc` or `~/.profile` file):
    ```
    export DISPLAY=:0
    ```

## Dev Setup
- Set up your Dev Environment, see docs here

## Build and Run
- From the root of the folder, run: `make run`
- The emulator starts in debug mode, so hits the first break-point. Type `c` to continue execution.


## Next Docs

The next docs explain the process taken to write this OS.

> They are rough drafts, feel free to make PRs to update any sections with more details, links, etc.

The content is as follows, there are some missing parts that are not done and we need contributions on, those marked with TBD. More PRs please 😊

- [What is an OS](./01_os_basics.md)
- [Environment Set Up](./02_env_setup.md)
- [The boot process](./03_boot_process.md)
- [Loading the kernel with GRUB](./04_loading_the_kernel.md)
- [Writing](./05_keyboard_driver.md) To [The Screen](./05_writing_to_screen.md)
- [The Global Descriptor Table (GDT)](./06_global_descriptor_table.md)
- [The Interrupt Descriptor Table (IDT)](./07_interrupt_descriptor_table.md)
- [IRQ and PIT](./08_interrupt_requests.md)
- Paging - _TBD_
- The Heap - _TBD_
- The VFS and the initrd - _TBD_
- Multitasking - _TBD_
- User Mode - _TBD_

