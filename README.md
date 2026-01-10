*This project has been created as part of the 42 curriculum by <your_login>.*

# get_next_line

## Description

The **get_next_line** project consists of implementing a function that reads a file descriptor and returns one line at a time, ending with a newline character (`\n`) if present.

The goal of this project is to deepen understanding of:
- File descriptors and low-level I/O
- Static variables
- Memory management (allocation, freeing, leak prevention)
- Handling edge cases (EOF, errors, varying buffer sizes)

The function must behave correctly regardless of the value of `BUFFER_SIZE` and must handle multiple consecutive calls while preserving unread data between calls.


## Instructions

### Compilation

The project is compiled together with your own test file or a tester of your choice.

Example:
```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c
````

You may define `BUFFER_SIZE` at compile time:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

### Usage

Prototype:

```c
char *get_next_line(int fd);
```

Example usage:

```c
int fd = open("file.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)))
{
    printf("%s", line);
    free(line);
}
close(fd);
```

Each call returns:

* A line ending with `\n`, if one exists
* The last line without `\n` if EOF is reached
* `NULL` when there is nothing left to read or an error occurs


## Algorithm Explanation and Justification

The implementation is based on a **stash-based incremental reading algorithm**.

### Core Idea

Because a file cannot always be read line-by-line in a single `read()` call, unread data must be preserved between function calls. This is achieved using a **static buffer (stash)**.

### Algorithm Steps

1. **Persistent Storage (stash)**
   A static pointer stores leftover data that has been read but not yet returned.

2. **Reading Loop**

   * Allocate a temporary buffer of size `BUFFER_SIZE + 1`
   * Repeatedly call `read()` until:

     * A newline character is found in the stash, or
     * `read()` returns 0 (EOF), or
     * An error occurs

3. **Stash Expansion**

   * Each new buffer is appended to the stash using string concatenation
   * The previous stash is freed to prevent memory leaks

4. **Line Extraction**

   * A new string is allocated containing characters from the stash up to and including `\n` (if present)
   * This string is returned to the caller

5. **Stash Trimming**

   * The returned line is removed from the stash
   * Remaining content is preserved for the next call

6. **Cleanup and Edge Cases**

   * All allocated memory is freed when no longer needed
   * Errors and EOF are handled gracefully
   * No memory leaks occur

### Why This Algorithm?

* Guarantees correctness for any `BUFFER_SIZE`
* Efficient: reads only what is necessary
* Respects project constraints (no forbidden functions, controlled memory usage)
* Matches the expected behavior of real-world line readers


## Resources

### Documentation & References

* `man 2 read`
* `man 3 malloc`
* GNU C Library documentation
* 42 Network subject PDF
* Online articles about buffered file reading in C

### AI Usage Disclosure

AI tools (ChatGPT) were used for:

* Clarifying project requirements
* Debugging segmentation faults and memory leaks
* Understanding edge cases related to `BUFFER_SIZE`
* Improving algorithm structure and explanation clarity

All code was written, tested, and validated by the student.
AI assistance was used strictly as a learning and debugging aid.


## Notes

* The implementation follows **42 Norm** rules
* No memory leaks (verified with leak testers)
* Compatible with mandatory and bonus requirements (if implemented)
* Handles invalid file descriptors and edge cases correctly

