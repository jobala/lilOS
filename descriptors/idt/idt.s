[GLOBAL idt_flush]

idt_flush:
    mov eax, [esp+4]        ; Get the pointer to the idt, passed as a paramet
    lidt [eax]              ; Load the IDT pointer.
    ret
