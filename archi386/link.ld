/*
  We want GRUB to load the kernel at a memory address larger than or equal to 0x00100000, 1MB
  Because addresses lower than 1MB are used by GRUB, BIOS and memory mapped IO
*/

ENTRY(loader)                /* The name of the entry label */

SECTIONS {
  . = 0x00100000;            /* The code should be loaded at 1MB */

  .text ALIGN(0x1000) : {    /* Align at 4kb */
    *(.text)                 /* All text sections from all files */
  }

  .rodata ALIGN(0x1000):     /* Align at 4kb */
  {
    *(.rodata*)              /* All read-only data sections from all files */
  }

  .data ALIGN(0x1000):       /* Align at 4kb */
  {
    *(.data)                 /* All data sections from all files */
  }

  .bss ALIGN(0x1000):        /* Align at 4kb*/
  {
    *(COMMON)                /* All COMMON sections from all files */
    *(.bss)                  /* All bss sections from all files */
  }
}
