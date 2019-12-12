#include "../../common/types.h"
#include "../../common/port/port.h"

u16int* video_memory = (u16int*) 0xB8000;

u16int cursor_y = 0;
u16int cursor_x = 0;

static void move_cursor() 
{
    u16int cursor_location = cursor_y * 80 + cursor_x;
    write_byte_to_port(0x3D4, 14);
    write_byte_to_port(0x3D5, cursor_location >> 8);
    write_byte_to_port(0x3D4, 15);
    write_byte_to_port(0x3D5, cursor_location);
}

static void scroll() {
    u8int attributeByte = (0 << 4) | (15 & 0x0F);
    u16int blank = 0x20 | (attributeByte << 8);

    if (cursor_y >= 25) {
        for (int i = 0; i < 24 * 80; i++) {
            video_memory[i] = video_memory[i+80];
        }

        for (int i = 24*80; i < 25*80; i++) {
            video_memory[i] = blank;
        }

        cursor_y = 24;
    }
}

void monitor_put(char c) 
{
    u8int backColor = 0;
    u8int foreColor  = 14;

    u8int attributeByte = (backColor << 4) | (foreColor & 0x0F);
    u16int attribute = attributeByte << 8;

    if (c == 0x08 && cursor_x) 
    {
        cursor_x--;
    } 
    else if (c == 0x09)
    {
        cursor_x = (cursor_x + 8) & ~(8 - 1);
    }
    else if (c == '\r')
    {
        cursor_x =0;
    }
    else if (c == '\n')
    {
        cursor_x = 0;
        cursor_y++;
    }
    else if (c >= ' ')
    {
        u8int cursor_location = (cursor_y * 80 + cursor_x);
        video_memory[cursor_location] = c | attribute;
        cursor_x++;
    }

    if (cursor_x >= 80)
    {
        cursor_x = 0;
        cursor_y++;
    }

    scroll();
    move_cursor();
}

void monitor_clear() {
    u8int attributeByte = (0 << 4) | (15 & 0x0F);
    u16int blank = 0x20 | (attributeByte << 8);

    for (int i = 0; i < 80 * 25; i++) 
    {
        video_memory[i] = blank;
    }

    cursor_x = 0;
    cursor_y = 0;
    move_cursor();
}

void monitor_write(char *msg)
{
    int i = 0;
    while (msg[i])
    {
        monitor_put(msg[i++]);
    }
}
