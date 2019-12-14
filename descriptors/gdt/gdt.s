[GLOBAL gdt_flush]

gdt_flush:
    mov eax, [esp+4]        ; Get the pointer to the GDT, passed as a parameter
    lgdt [eax]              ; Load the new GDT pointer

    mov ax, 0x10            ; Is the offset in the GDT to our data segment
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush         ; 0x08 is the offset to the code code segment
.flush
    ret