/* This script tell ld how to set up our kernel image 
 * 1. Tells ld that the start location of our binary should be the symbol start
 * 2. Tells ld that .text section should be first and should start at 0x100000
 * 3. The .data and .bss sections should be next and each should be page aligned
 * */
ENTRY(start)
SECTIONS
{
    .text 0x100000 :
    {
        code = .; _code = .; __code = .;
        *(.text)
        . = ALIGN(4096);

      }

      .data :
      {
          data = .; _data = .; __data = .;
          *(.data)
              *(.rodata)
              . = ALIGN(4096);

      }

      .bss :
      {
          bss = .; _bss = .; __bss = .;
          *(.bss)
          . = ALIGN(4096);

      }

      end = .; _end = .; __end = .;
}
