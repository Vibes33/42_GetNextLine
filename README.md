# 42_Get_Next_Line

![Score](https://img.shields.io/badge/Score-110%2F100-success)
![Language](https://img.shields.io/badge/Language-C-blue)
![Norm](https://img.shields.io/badge/Norm-passing-brightgreen)

## 📋 Table of Contents
- [Description](#description)
- [Project Overview](#project-overview)
- [How It Works](#how-it-works)
- [Project Structure](#project-structure)
- [Implementation Details](#implementation-details)
- [Compilation](#compilation)
- [Usage](#usage)
- [Bonus Features](#bonus-features)
- [Technical Challenges](#technical-challenges)
- [Testing](#testing)
- [Author](#author)

## 🔍 Description

**Get Next Line** (GNL) is a crucial project at 42 School that challenges you to create a function that reads a line from a file descriptor. This function is designed to be called in a loop to read a text file line by line, regardless of the buffer size.

The project teaches fundamental concepts such as:
- Static variables
- File descriptor manipulation
- Dynamic memory allocation
- Buffer management
- Edge case handling

This implementation successfully passed all tests and earned **110/100** points, including bonus features.

## 🎯 Project Overview

The main function prototype is:

```c
char *get_next_line(int fd);
```

### Function Behavior

- **Returns**: A line read from the file descriptor, including the `\n` character (if present)
- **Returns NULL**: When there's nothing left to read or an error occurs
- **Works with**: Files, standard input, network connections, or any valid file descriptor

### Key Features

- ✅ Reads one line at a time from any file descriptor
- ✅ Works with variable `BUFFER_SIZE` (can be defined at compilation)
- ✅ Handles multiple consecutive calls correctly
- ✅ Efficient memory management (no leaks)
- ✅ Static variable for persistent data between calls
- ✅ Edge case handling (empty files, no newline at EOF, large files)

## ⚙️ How It Works

### Workflow

```
┌─────────────────────────────────────────────────────┐
│  1. Read BUFFER_SIZE bytes from file descriptor    │
│  2. Store read content in static variable (stash)   │
│  3. Check if '\n' is present in stash               │
│  4. If no '\n', continue reading and appending      │
│  5. Extract line up to '\n' (or EOF)                │
│  6. Update stash with remaining content             │
│  7. Return the extracted line                       │
└─────────────────────────────────────────────────────┘
```

### Visual Example

```
File content: "Hello\nWorld\nTest"
BUFFER_SIZE: 5

Call 1: Read "Hello" → Stash: "Hello"
        Read "\nWor"  → Stash: "Hello\nWor"
        Return: "Hello\n"
        Stash: "Wor"

Call 2: Read "ld\nTe" → Stash: "World\nTe"
        Return: "World\n"
        Stash: "Te"

Call 3: Read "st"    → Stash: "Test"
        Return: "Test"
        Stash: NULL

Call 4: Return: NULL (EOF reached)
```

## 📁 Project Structure

```
42_GetNextLine/
├── get_next_line.h         # Header file with function prototypes
├── get_next_line.c         # Main GNL function and line extraction
└── get_next_line_utils.c   # Helper functions (strlen, strjoin, etc.)
```

### File Breakdown

#### `get_next_line.h`
- Function prototypes
- Structure definition (`t_gnl` with static stash)
- BUFFER_SIZE definition (default: 1234)
- Required includes

#### `get_next_line.c`
- `get_next_line()` - Main function that reads from fd
- `extract_line()` - Extracts a complete line from stash
- `find_line_end()` - Finds the position of '\n' or end of string
- `copy_line()` - Creates a new string with the line content
- `create_new_stash()` - Updates stash with remaining content

#### `get_next_line_utils.c`
- `ft_strlen()` - Calculates string length (NULL-safe)
- `has_newline()` - Checks if string contains '\n'
- `ft_strjoin_free()` - Joins two strings and frees the first one
- `ft_copy_strings()` - Helper for string concatenation

## 🔧 Implementation Details

### Static Variable Structure

```c
typedef struct s_gnl
{
    char *stash;
}   t_gnl;
```

The static structure persists between function calls, maintaining the buffer state.

### Main Function Logic

```c
char *get_next_line(int fd)
{
    static t_gnl    gnl;
    char            buffer[BUFFER_SIZE + 1];
    ssize_t         bytes_read;
    
    // Input validation
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    
    // Read until newline is found
    while (!has_newline(gnl.stash))
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read <= 0)
            break;
        buffer[bytes_read] = '\0';
        gnl.stash = ft_strjoin_free(gnl.stash, buffer);
    }
    
    // Extract and return line
    return (extract_line(&gnl.stash));
}
```

### Line Extraction Process

1. **Find line end**: Locate '\n' or end of stash
2. **Copy line**: Allocate and copy characters up to line end
3. **Create new stash**: Save remaining content after line end
4. **Free old stash**: Clean up previous allocation
5. **Return line**: Give caller the extracted line

### Memory Management

```c
char *ft_strjoin_free(char *s1, char *s2)
{
    char *result;
    
    result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!result)
        return (NULL);
    
    // Copy both strings
    ft_copy_strings(result, s1, s2);
    
    // Free only s1 (stash), keep s2 (buffer)
    free(s1);
    
    return (result);
}
```

### Edge Cases Handled

✅ **Invalid file descriptor** (fd < 0)  
✅ **Invalid BUFFER_SIZE** (≤ 0)  
✅ **Empty file** (returns NULL)  
✅ **No newline at EOF** (returns remaining content)  
✅ **Multiple consecutive newlines** (returns empty lines)  
✅ **Very long lines** (handles any line length)  
✅ **Read errors** (returns NULL and cleans up)  

## 🔨 Compilation

### Basic Compilation

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

### Variable Buffer Size

You can define `BUFFER_SIZE` at compilation:

```bash
# Small buffer
cc -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c -o gnl_test

# Medium buffer
cc -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -o gnl_test

# Large buffer
cc -D BUFFER_SIZE=10000 get_next_line.c get_next_line_utils.c -o gnl_test
```

### With Your Main

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
   get_next_line.c get_next_line_utils.c main.c -o test_gnl
```

## 💻 Usage

### Basic Example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;
    
    // Open file
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
        return (1);
    
    // Read file line by line
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    
    close(fd);
    return (0);
}
```

### Reading from Standard Input

```c
#include "get_next_line.h"
#include <stdio.h>

int main(void)
{
    char *line;
    
    printf("Enter text (Ctrl+D to stop):\n");
    
    while ((line = get_next_line(0)) != NULL)  // fd = 0 (stdin)
    {
        printf("You wrote: %s", line);
        free(line);
    }
    
    return (0);
}
```

### Multiple File Descriptors

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd1, fd2;
    char    *line;
    
    fd1 = open("file1.txt", O_RDONLY);
    fd2 = open("file2.txt", O_RDONLY);
    
    // Read from both files alternately
    line = get_next_line(fd1);
    printf("File1: %s", line);
    free(line);
    
    line = get_next_line(fd2);
    printf("File2: %s", line);
    free(line);
    
    line = get_next_line(fd1);
    printf("File1: %s", line);
    free(line);
    
    close(fd1);
    close(fd2);
    
    return (0);
}
```

## 🎁 Bonus Features

### Multiple File Descriptors Support

The bonus part requires handling multiple file descriptors simultaneously using a single static variable.

**Implementation with array of structures:**

```c
#define MAX_FD 1024

typedef struct s_gnl
{
    char *stash;
}   t_gnl;

char *get_next_line(int fd)
{
    static t_gnl gnl[MAX_FD];  // Array for multiple fds
    
    if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
        return (NULL);
    
    // Use gnl[fd] instead of gnl
    // ... rest of implementation
}
```

### Bonus Features Achieved (110/100)

✅ Single static variable for multiple file descriptors  
✅ Efficient memory management across multiple fds  
✅ Independent reading from different files  
✅ No cross-contamination between file descriptors  

## 🎯 Technical Challenges

### 1. **Static Variables**
Understanding how static variables persist between function calls and managing their lifecycle.

### 2. **Buffer Management**
Efficiently handling varying buffer sizes and concatenating read chunks.

### 3. **Memory Leaks**
Ensuring all allocated memory is properly freed, especially in error cases.

### 4. **Newline Detection**
Correctly identifying line boundaries and handling edge cases (no newline at EOF).

### 5. **Multiple File Descriptors**
Managing separate buffers for multiple open files simultaneously (bonus).

### 6. **Edge Cases**
- Files with no newline at end
- Empty lines (consecutive newlines)
- Very long lines (exceeding BUFFER_SIZE)
- Read errors
- Invalid file descriptors

## 🧪 Testing

### Create Test Files

```bash
echo -e "Line 1\nLine 2\nLine 3" > test.txt
echo -e "A\nB\nC\nD\nE" > short.txt
echo -n "No newline at end" > no_newline.txt
```

### Comprehensive Test Program

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;
    int     line_count;
    
    // Test 1: Normal file
    printf("=== TEST 1: Normal File ===\n");
    fd = open("test.txt", O_RDONLY);
    line_count = 1;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line %d: %s", line_count++, line);
        free(line);
    }
    close(fd);
    
    // Test 2: Empty file
    printf("\n=== TEST 2: Empty File ===\n");
    fd = open("empty.txt", O_RDONLY);
    line = get_next_line(fd);
    printf("Result: %s\n", line ? line : "NULL (correct)");
    free(line);
    close(fd);
    
    // Test 3: No newline at EOF
    printf("\n=== TEST 3: No Newline at EOF ===\n");
    fd = open("no_newline.txt", O_RDONLY);
    line = get_next_line(fd);
    printf("Line: %s\n", line);
    free(line);
    close(fd);
    
    // Test 4: Invalid fd
    printf("\n=== TEST 4: Invalid FD ===\n");
    line = get_next_line(-1);
    printf("Result: %s\n", line ? line : "NULL (correct)");
    
    // Test 5: Standard input
    printf("\n=== TEST 5: stdin (type something) ===\n");
    line = get_next_line(0);
    printf("You entered: %s", line);
    free(line);
    
    return (0);
}
```

### Recommended Testers

- **[gnlTester](https://github.com/Tripouille/gnlTester)** by Tripouille
- **[GNL_lover](https://github.com/charMstr/GNL_lover)** by charMstr
- **[42TESTERS-GNL](https://github.com/Mazoise/42TESTERS-GNL)** by Mazoise
- Manual testing with `valgrind` for memory leaks

### Valgrind Testing

```bash
valgrind --leak-check=full --show-leak-kinds=all ./test_gnl
```

## 📊 Performance Considerations

### Buffer Size Impact

| BUFFER_SIZE | Performance | Memory Usage |
|-------------|-------------|--------------|
| 1           | Slow (many syscalls) | Low |
| 42          | Balanced | Medium |
| 1024        | Fast | Higher |
| 10000       | Very Fast | High |

### Optimization Tips

- **Small files**: Use smaller BUFFER_SIZE (1-42)
- **Large files**: Use larger BUFFER_SIZE (1024-8192)
- **Network sockets**: Use medium BUFFER_SIZE (128-512)
- **Balance**: Consider memory vs. speed tradeoff

## 🎓 Learning Outcomes

This project teaches:

- **Static variables** - Persistent data between function calls
- **File I/O** - Reading from file descriptors
- **Buffer management** - Handling partial reads
- **Memory allocation** - Dynamic memory and proper cleanup
- **Edge cases** - Robust error handling
- **System calls** - Understanding `read()` behavior

## 👨‍💻 Author

**rydelepi (Vibes33)** - 42 Student

*This project was validated with a score of 110/100, successfully completing all mandatory requirements and bonus features.*

---

## 📝 Notes

- Only allowed functions: `read`, `malloc`, `free`
- Must work with any valid `BUFFER_SIZE` (including 1 and very large values)
- Must handle multiple file descriptors (bonus)
- No global variables allowed
- Must follow the 42 Norm strictly

## 🚀 Future Use Cases

This function will be reused in future 42 projects:
- **FdF** - Reading map files
- **Fract-ol** - Reading configuration
- **minishell** - Reading command input
- **cub3D** - Parsing scene files
- **miniRT** - Reading scene descriptions

---

*Part of the 42 School Common Core curriculum*
