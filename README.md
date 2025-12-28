# get_next_line

Reads one line at a time from a file descriptor.

This 42 project focuses on reading files efficiently while practicing dynamic memory management.

## What’s in it
- Reads from any file descriptor
- Handles lines of any length
- Minimal memory usage

## How to use
A Makefile is included. Simply run:
```bash
make
```
This will compile get_next_line.c and create get_next_line.a.

Include get_next_line.h in your project and link with the library.

## Example:

```
#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
```
---
## Note

This code is for educational purposes only and should not be copied for assignments or projects elsewhere.
