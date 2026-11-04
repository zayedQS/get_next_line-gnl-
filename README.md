*This project has been created as part of the 42 curriculum by zhasan.*

# get_next_line

## Description

The **get_next_line** project is a fundamental C programming project in the 42 core curriculum. Its objective is to write a function that reads a line from a file descriptor (`fd`), up to and including the newline character (`\n`), or until the End-Of-File (`EOF`) is reached.

This project introduces key C programming concepts, including:

- Static variables and their persistence across function calls.
- Dynamic memory management (`malloc`, `free`) without memory leaks.
- Buffer manipulation and efficient handling of I/O operations.

## Algorithm Justification & Strategy

The implementation uses a **static buffer accumulator strategy**:

1. **Persistent state with a static variable:** A static variable `stash` holds the leftover data read from the file descriptor between consecutive calls.
2. **Chunk reading:** The function reads from the file descriptor in chunks of `BUFFER_SIZE` bytes into a temporary buffer.
3. **Accumulation:** Each chunk is appended to `stash` until it contains a newline character (`\n`) or `read` returns `0` (EOF).
4. **Extraction:** Once a newline or EOF is reached, `stash` is split:
   - Everything up to and including the first `\n` is allocated and returned as `line`.
   - The remaining content after `\n` is saved back into `stash` for the next call.
5. **Memory management:** If an allocation fails or reading finishes, `stash` is freed safely to guarantee zero memory leaks.

This approach processes the input in linear time, **O(N)**, relative to the amount of data read, and avoids redundant reads across buffer boundaries.

## Instructions

### Compilation

The project is compiled with `cc` using the flags `-Wall -Wextra -Werror` and a configurable `BUFFER_SIZE`:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c -o gnl_test
```

### Usage

Include the header file in your C program and call `get_next_line` in a loop:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("example.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```
## Resources

### References

- `read(2)`, `open(2)` and `close(2)` manual pages (POSIX I/O).
- GNU C Library documentation on storage duration and static variables.
- Valgrind Memcheck documentation for detecting memory leaks and invalid accesses.

Run the compiled executable:

## Bonus Part

The bonus part extends the project to support **multiple file descriptors simultaneously** without losing the reading thread of each file.

### Key Modifications
 **Static Array of Pointers:** The single `static char *stash` pointer is replaced with an array of pointers:
   ```c
   static char *stash[OPEN_MAX];

```bash
./gnl_test
```

**AI usage:** AI was used as a learning and to better understand certain concepts such as fd and buffer
  ,reviewing conceptual strategies for memory leak management during function exits.
---
