# get_next_line — École 42

> A function that reads a file descriptor line by line, handling multiple fd simultaneously.

---

## Description

`get_next_line` returns one line at a time from a file descriptor each time it is called. It works with files, standard input, or any valid fd — and the bonus version handles multiple file descriptors at once without losing track of each one's reading progress.

---

## Prototype

```c
char *get_next_line(int fd);
```

- **Returns** the next line including the trailing `\n` (if present)
- **Returns** `NULL` when the file is fully read or if an error occurs
- The returned string is heap-allocated — the caller must `free()` it

---

## Files

| File | Description |
|---|---|
| `get_next_line.c` | Core function |
| `get_next_line_utils.c` | Helper functions |
| `get_next_line.h` | Header |
| `get_next_line_bonus.c` | Bonus — multiple fd support |
| `get_next_line_utils_bonus.c` | Bonus helper functions |
| `get_next_line_bonus.h` | Bonus header |

---

## How it works

### Buffer & static variable
Each call reads up to `BUFFER_SIZE` bytes from the fd into a buffer. A `static` variable retains leftover data between calls so nothing is lost between two reads.

### Multiple fd (bonus)
The bonus version uses a `static char *stash[OPEN_MAX]` array — one saved buffer per fd — allowing independent tracking of multiple file descriptors simultaneously.

---

## Compilation

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

You can set `BUFFER_SIZE` to any positive value at compile time:

```bash
-D BUFFER_SIZE=1      # minimal reads
-D BUFFER_SIZE=4096   # larger reads, better performance on big files
```

---

## Usage example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("file.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### Bonus — reading from multiple fd

```c
char *line1 = get_next_line(fd1);
char *line2 = get_next_line(fd2);
char *line3 = get_next_line(fd1); // picks up where fd1 left off
```

---

## Edge cases handled

- `BUFFER_SIZE` of 1 or very large values
- Files with no trailing newline on the last line
- Empty files
- Reading from `stdin` (fd = 0)
- Multiple fd open at the same time (bonus)

---

## École 42

Project completed as part of the École 42 curriculum. Only `read`, `malloc`, and `free` are used — no `lseek`, no global variables.
