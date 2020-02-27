# Loading The Kernel

In this article we are going to write our humble kernel and load it with a bootloader. 

## Directory Structure

Create a directory `my-os` and under it create a directory called `iso`. Under iso create a directory boot and under boot create the directory grub. In grub create a file `grub.cfg`. After creating these folders, the folder structure should be like the one below.

```
iso
|---boot
    |--- grub
        |--- grub.cfg
```

The grub.cfg file is a configuration file for the grub bootloader. Write the following code in it

```
menuentry "os" {
    multiboot /boot/kernel.elf
}
```

The menu entry “os” will be the name of the os shown by Grub for you to select. The multiboot property we specify the path to our kernel. This means, after compiling the kernel we should put the output kernel.elf file in the boot/ directory.

## Multiboot Specification

In the grub.cfg file we specified the path to our kernel file so GRUB will know where to find it. When GRUB finds the kernel it will look within the first 4 bytes for  multiboot headers. The multiboot headers are defined by the multiboot standard which defines a contract between the kernel and the bootloader. So the bootloader expects the kernel to have the multiboot headers within its first 4k bytes.

Create a directory load under `my-os`. In the directory create the following files; `load.s` and `link.ld`. The `load.s` file is the entry point for our operating system. It specifies the multiboot headers and transfers control to our kernel. Add the following code in `load.s`.

```
MBOOT_PAGE_ALIGN        equ 1<<0
MBOOT_MEM_INFO          equ 1<<1
MBOOT_HEADER_MAGIC      equ 0x1BADB002
MBOOT_HEADER_FLAGS      equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM          equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)
```

The code above defines constants, pay particular attention to `MBOOT_HEADER_MAGIC`, `MBOOT_HEADER_FLAGS` and `MBOOT_CHECKSUM`.

### `MBOOT_HEADER_MAGIC`

The kernel must have the magic number as `0x1BADB002`, note that those are zeros and not Os since it’s a hexadecimal number. This identifies the kernel as multiboot compliant. Which means it respects the contract defined by the multiboot standard.

### `MBOOT_HEADER_FLAGS`

This header has the value that is the result of the bitwise OR operation of `MBOOT_PAGE_ALIGN` and `MBOOT_MEM_INFO`. `MBOOT_PAGE_ALIGN` has the value (in bytes) `0000 0001`, which we then shift right by `0`, resulting in the same number `0000 0001`. Shifting by zero is like adding zero to a number, it doesn’t change the value of the resulting sum.

`MBOOT_PAGE_ALIGN` has the value (in bytes) of `0000 0010`. This is because we are shifting the bits in `1` to the right by one.

```
1 = 0000 0001
1 << 1 = 0000 0010
```

`MBOOT_HEADER_FLAGS` is the value of the `OR` operation between `MBOOT_PAGE_ALIGN` and `MBOOT_MEM_INFO`.

```
0000 0001 | 0000 0010 = 0000 0011
```

Therefore, `MBOOT_HEADER_FLAGS` has the value of `0000 0011`. Pay attention to the first two bits, they both have the value of `1`. Having these two bits set mean something to the bootloader. They mean, load the kernel on a page boundary and provide information about memory to the kernel.

### `MBOOT_CHECKSUM`

This field must sum up to zero when added to the `(mboot_header_magic + mboot_header_flags)`.

## More Assembly

On the next line after `MBOOT_CHECKSUM`, code below:

```
[BITS 32]

[GLOBAL MBOOT]
[EXTERN code]
[EXTERN bss]
[EXTERN end]

mboot:
    dd MBOOT_HEADER_MAGIC
    dd MBOOT_HEADER_FLAGS
    dd MBOOT_CHECKSUM
    
    dd mboot
    dd code
    dd bss
    dd end
    dd start
```

Don’t beat up yourself if you don’t know assembly and you don’t understand what is happening here. Although, I encourage you to make time to learn assembly. Learning is more fulfilling when you understand most of the things.  What this code does is setting the boot headers; magic, flags and checksum and the addresses of our code, bss, end and start sections.

## Calling The Kernel

To call the kernel, writing the following assembly code  below mboot section `mboot`:

```
   ...
   ...

[GLOBAL start]
[EXTERN main]

start:
    push ebx
    cli
    call main
    jpm$
```

`[GLOBAL start]` means that we want to use start in another file and indeed we are using in the linker script, which we will see later. `[EXTERN main]` tells the assembler that the main label is defined in some other file. The code under the `start` section push the multiboot header location in the ebx register, cancels interrupts, calls the main function, which we will define in a .c file and then enters an infinite loop.

What we have to do now is create a new directory under `my-os` called `kernel/` in it create the file `main.c`. Add the following code 

```c
int main() {
    return 0xDEADBABA;
}
```

This main function is what gets called in `load.s` with the `call main` assembly instruction.

## Linking It All Together

Now in the `link.ld` file that we created earlier write the code below. 

```masm
ENTRY(start)
SECTIONS 
{
    .text 0x100000:
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
    .bss:
    {
        bss = .; _bss = .; __bss = .;
        *(.bss)
        . = ALIGN(4096)
    }
    end = .; _end = .; __end = .;
}
```

What this code does is tells the bootloader to load us from the 1MB memory address. The memory spaces below 1MB is used by BIOS and the bootloader.

You can now install and run then OS with the make run command. If everything works fine you should see the GRUB menu, select `my-o`s and and you will be greeted with a black, blank screen. This is fine and expected. In the next article we write something to the screen.
