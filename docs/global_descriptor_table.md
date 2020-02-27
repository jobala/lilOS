# Global Descriptor Table

For a program to run, you need at least two segments, the code and data segments. Segment descriptors are used to determine the properties of a segment ie the privilege level of the segment, it’s base and limit address so on and so forth. The Global Descriptor Table is an array of segment descriptors.

## Segment Descriptor

A segment descriptor follow a particular bit pattern.


Offset (bits) | Name | Meaning
------ | ------ | -----------------------------
`0..15` | `Limit` | Lower 4 bytes of the descriptor’s limit
`16..32` | `Base` | Lower 4 bytes of the descriptor’s base address
`32..39` | `Base` | Middle 2 bytes of the descriptor;s base address
`40..47` | `Access Byte` | A group of bit flags defining who has access to the memory referenced by this descriptor
`52..55` | `Flags` | Four flags influencing  segment size
`56..63` | `Base` | Upper 2bytes of the descriptor’s base address


If you stare at this long enough you’ll find that a segment descriptor is made up of four fields:

- `Limit` - The limit of the segment. It’s a 20 bit value so can only reference upto 1mb of memory. However, with the page granularity bit set, it can reference upto 4gb of memory. 
- `Base` - The starting address of the segments. It spread around 3 places in the descriptor. It’s a 32 bit value so can reference anywhere in the 4gb address space.
- `Flags` - Among other properties, the page granularity bit is set here.
- `Access Byte` - Access byte sets a segment’s privilege level, whether it’s a data or code segment etc.

Spread around a 64 bit data structure.

We have seen that GDT is an array of segment descriptors. To implement this in code, we have to define a segment descriptor struct.

```c
struct gdt_entry_struct 
{    
    u16int limit_low;
    u16int base_low;
    u8int  base_middle;
    u8int  access;
    u8int  granularity;
     u8int  base_high;
}__attribute__((packed));

typedef struct gdt_entry_struct gdt_entry_t;
```

`__attribute__((packed))` prevents the compiler from padding the struct. For example, in a 32 bit machine, the compiler uses 32 bits to represent values. If an instruction uses only 16 bits then the remaining 16 bits will be padded with 0s. This is efficient for the processor. In this case the CPU expects the value in the struct to follow this exact bit pattern with no padding.

We’ll need another struct to represent the GDT table, this one is  a lot less complex. It contains the base address and limit of our GDT table.

```c
struct gdt_ptr_struct
{
    u16int limit;
    u32int base;
};

typedef struct gdt_ptr_struct gdt_ptr_t;
```

Next we define a few variables:

```c
gdt_entry_t gdt_entries[3];
gdt_ptr_t gdt_ptr;
```

`gdt_entries` is an array data structure containing segment descriptors as entries. `gdt_ptr` is a data structure containing information about the GDT, it’s base address and limit.

Now we need to write the function that places the right bits in the right place. The function below moves bits around so that we conform to the specific bit structure.

```c
static void gdt_set_gate(entry, base, limit, access, gran)
{
    gdt_entries[entry].base_low = (base & 0xFFFF);
    gdt_entries[entry].base_middle = (base >> 16) & 0xFF;
    gdt_entries[entry].base_high = (base >> 24) & 0xFF;

    gdt_entries[entry].limit_low = (limit & 0xFFFF);
    gdt_entries[entry].granularity = (limit >> 16) & 0x0F;

    gdt_entries[entry].granularity |= gran &0xF0;
    gdt_entries[entry].access = access;
}
```

Finally we get to initialize the GDT. Write the function below:

```c
static void init_gdt()
{
    gdt_ptr.limit = (sizeof(gdt_entry_t) * 3) - 1;
    gdt_ptr.base  = (u32int) &gdt_entries;

    gdt_set_gate(0, 0, 0, 0, 0);
    gdt_set_gate(1, 0xFFFFFFFF, 0x9A, 0xCF);
    gdt_set_gate(2, 0xFFFFFFFF, 0x92, 0xCF);

    gdt_flush((u32int) &gdt_ptr)
}
```

We first set the base and limit of the GDT, add 3 segment descriptors to the GDT and finally call `gdt_flush`. Which is defined in an assembly proram that we’ll write next. We pass a pointer to `gdt_ptr` to `gdt_flush`. 

Create `gdt.s` and write the code below:

> Code here - [`/descriptors/gdt/gdt.s`](../descriptors/gdt/gdt.s)

This is the definition of the `gdt_flush` function that we used before. We load the GDT table with the `lgdt` instruction. In the data segment and similar registers we set an offset to our data segment descriptor. Then we jump to the offset with the code segment descriptor.
