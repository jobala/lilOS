# Writing To Screen

In this article, we are going to add functionality that will help the kernel write to the screen. Being able to write to a screen is incredibly useful during debugging.

## Directory Structure

Before we start, let’s add a few more directories. Under the `my-os/` directory add the directory `common/`, we’ll use this directory to keep files that are used by other modules. Writing to the screen involves writing our first driver, so create the `drivers/` directory under `my-os`. In the `drivers/` directory create another directory called `monitor/`, this is where we’ll keep the code that writes to the screen.

## Custom Types

Let’s define the custom types that we’ll need to use in other parts of our operating system. Create a new file called `types.h` and write the code below:

```c
typedef unsigned  int   u32int;
typedef           int   s32int;
typedef unsigned  short u16int;
typedef           short s16int;
typedef unsigned  char  u8int;
typedef           char  s8int;
```

All we are doing here is creating different size integers.

## FrameBuffer

> TODO: add diagrams

The FrameBuffer is a region of RAM that determines what is displayed on the screen. It starts at the memory address `0xB8000`. Think of it as an array containing 16 bit values at it’s indices. Putting the character `‘a’` at index 0 will display it at the top left part of the screen. While the FrameBuffer is one dimensional, the screen is not. The screen is two dimensional and has a length of 80 characters by 25 characters. How do we place a character in the 3rd row and 4th column in the screen then? The formula below maps a location in the screen to a location in the one dimensional FrameBuffer.

```
location = (y * 80) + x
Therefore, location in FrameBuffer will be
location = (3 * 80) + 4 = 244.
```

So writing a value in the 244th index in the FrameBuffer will make the screen display the value in the 3rd row and 4th column.

> [TODO: Add Diagrams]

In the previous paragraph, I mentioned that putting the character `‘a’` at index 0 will display it at the top left part of the screen. Well, I lied. Although it’s a nice exercise to see what that prints. We know that 16 bits makes two bytes. For the FrameBuffer, the least significant byte is known as the character byte and the most significant byte is known as the attribute byte. If we want to display a character in the screen then we need to make sure that it forms the least significant byte.

The attribute byte is split further into two. The 4 lower bits determines the foreground colour of the character and the upper 4 bits specifies the background colour.

## Writing To The Screen

Now we get to the exciting part, where we actually write some code. In the `monitor/` directory create the `monitor.h` file add the code below.

```c
#pragma once

void monitor_put(char);
void monitor_write(char*);
```

All the `#pragma once` does is allow us to include this header file in multiple places.

Create the `monitor.c` file under the monitor directory and add the code below.

```c
#include “../common/types.h”

u16int* video_memory = (u16int*) 0xB8000;
u16int cursor_x = 0;
u16int cursor_y = 0;
```

What this does is create a pointer to the FrameBuffer starting address in the `video_memory` variable. We then create two other variables `cursor_x` and `cursor_y` which we’ll use to determine where on the screen to write.

```c
void monitor_put(char c)
{
    u8int backColour = 0;
    u8int foreColour = 15;

    u8int  attributeByte = (backColour << 4) | (foreColour & 0x0F);

    u16int attribute = attributeByte << 8;

    if (c == 0x08 && cursor_x)
    {
        cursor_x--;
    }

    else if (c == 0x09)
    {
        cursor_x = (cursor_x+8) & ~(8-1);
    }

    else if (c == '\r')
    {
        cursor_x = 0;
    }

    else if (c == '\n')
    {
        cursor_x = 0;
        cursor_y++;
    }
    else if(c >= ' ')
    {
        location = cursor_y*80 + cursor_x
        video_memory[location] = c | attribute;
        cursor_x++;
    }

    if (cursor_x >= 80)
    {
        cursor_x = 0;
        cursor_y ++;
    }
}
```

The section below is what does the actual writing

```c
location = cursor_y*80 + cursor_x
video_memory[location] = c | attribute;
cursor_x++;
```

It calculates the cursor location, the at that index in the video_memory it stores the result of an OR operating between the attribute and the character.

Writing a string is a lot more easier. We just loop through the string and print the individual characters.

```c
void monitor_write(char *msg)
{
    int i = 0;
    while (msg[i])
    {
        monitor_put(msg[i++]);
    }
}
```

In the `main.c` file add the code below:

```c
#include “../common/types.h”
#include “../drivers/monitor/monitor.h”

int main(void* mboot_ptr)
{
    monitor_write(“Hello, Wolrd\nFrom myOS”);
}
```

Execute make run, and select your operating system. You should see that you message has been printed on the screen.
