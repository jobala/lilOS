; This is the kernel's entry point. We could either call main here, set up the stack
; or some other nice stuff. Like perhaps setting up the GDT and Segments. Note that
; interrupts are disabled at this point.


MBOOT_PAGE_ALIGN	equ 1<<0		 ; Load and kernel and modules on a page boundary
MBOOT_MEM_INFO 		equ 1<<1         ; Provide your kernel with memory info
MBOOT_HEADER_MAGIC  equ 0x1BADB002   ; Multiboot magic value
MBOOT_HEADER_FLAGS  equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM      equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

[BITS 32]                               ; All instructions should be 32 bit

[GLOBAL MBOOT]							; Make 'mboot' accessible from C
[EXTERN code]							; Start of the '.text' section
[EXTERN bss]							; Start of the '.bss' section
[EXTERN end]							; End of the last loadable section

mboot:
	dd MBOOT_HEADER_MAGIC				; Grub will search  for this value on each
										; 4-byte boundary in the kernel file
	dd MBOOT_HEADER_FLAGS				; How GRUB should load your file/settings
	dd MBOOT_CHECKSUM					; To ensure that the above values are correct

	dd mboot							; Location of this descriptor
	dd code 							; Start of the kernel's .text section (code)
	dd bss								; End of kernel's .data section 
	dd end								; End of kernel
	dd start							; Kernel entry point (initial EIP)

[GLOBAL start]							; Kernel's entry point
[EXTERN main]							; This is the entry point of our C code

start:
	push ebx							; Load multiboot header location

	; Execute the kernel
	cli									; Disable interrupts
	call main							; Call our main function
	jmp$								; Enter an infinite loop, to stop our processor from executing whatever is in the memory
										; after our kernel.
