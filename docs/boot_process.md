# The Boot Process

The boot process is a sequence of steps that take place after you turn on your machine. The ultimate goal of the boot process is to load the operating system. In this article I give a description of this process.

When your machines turns on, the first software to run is BIOS an abbreviation for Basic Input/Output System. The BIOS comes with the hardware and is stored in ROM. It performs the POST test(Power On Self Test) making sure that all the hardware in the computer works and after this it transfers control to the MBR(Master Boot Record)

The Master Boot Record makes the first 512 bytes of a hard drive. It contains boot code and a partition table. You can think of the partition table as entries for the list of partitions on the hard drive. The boot code searches the partitions for an active partition. An active partition contains a bootloader program like GRUB. When it finds it, it transfers control to the bootloader.

The bootloader is now in charge. The bootloader then loads our Operating System. In the next article I talk about how a bootloader loads a kernel.
