# Keyboard Driver

In this article we are going to write a keyboard driver.

Each key in a keyboard has a scancode value. We are going to use the scancode as an index into an array.

Create the file `keyboard.h` and write the following code.

```c
void init_keyboard();
```

Create the file `keyboard.c` and write the following value.

```c
u8int kbdus[128] =
{
   0,  27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */
 '9', '0', '-', '=', '\b', /* Backspace */
 '\t',         /* Tab */
 'q', 'w', 'e', 'r',   /* 19 */
 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', /* Enter key */
   0,          /* 29   - Control */
 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', /* 39 */
'\'', '`',   0,        /* Left shift */
'\\', 'z', 'x', 'c', 'v', 'b', 'n',            /* 49 */
 'm', ',', '.', '/',   0,              /* Right shift */
 '*',
   0,  /* Alt */
 ' ',  /* Space bar */
   0,  /* Caps lock */
   0,  /* 59 - F1 key ... > */
   0,   0,   0,   0,   0,   0,   0,   0,
   0,  /* < ... F10 */
   0,  /* 69 - Num lock*/
   0,  /* Scroll Lock */
   0,  /* Home key */
   0,  /* Up Arrow */
   0,  /* Page Up */
 '-',
   0,  /* Left Arrow */
   0,
   0,  /* Right Arrow */
 '+',
   0,  /* 79 - End key*/
   0,  /* Down Arrow */
   0,  /* Page Down */
   0,  /* Insert Key */
   0,  /* Delete Key */
   0,   0,   0,
   0,  /* F11 Key */
   0,  /* F12 Key */
   0,  /* All other keys are undefined */
};

static void keyboard_handler(registers_t regs)
{
   u8int scancode;

   scancode = read_byte_from_port(0x60);

   if (scancode & 0x80)
   {
       // do nothing for now
   }
   else
   {
       u8int key = kbdus[scancode];
       monitor_put(key);
   }
}

void init_keyboard()
{
   register_interrupt_handler(IRQ1, &keyboard_handler);
}
```

Then in `main.c`, write the following:

```c
int main(void* mboot_ptr) {
   init_descriptor_tables();
   init_keyboard();
}
```
