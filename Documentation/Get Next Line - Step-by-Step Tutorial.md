# Get Next Line - Step-by-Step Tutorial

## Overview

In this project, you will implement a function `get_next_line()` that reads and returns one line at a time from a file descriptor (e.g., a file or standard input). This function should be capable of reading multiple lines by repeatedly calling it in a loop. The goal is to manage memory efficiently, handle different buffer sizes, and learn how to use **static variables** in C.

---

## Step 1: Understand the Functionality

### The Prototype

The function should have the following prototype:

```c
char *get_next_line(int fd);
```

Where:

- `fd` is the file descriptor (an integer that represents the file or input you're reading).
- The function returns the next line read from the file descriptor or `NULL` if there's nothing left to read.

### Key Details:

- The returned line **must include the newline character (`\n`)** if it's found before the end of the file.
- If the end of the file is reached and no newline is found, return the remaining content without the `\n`.
- You will handle multiple calls to `get_next_line()` in a loop to read the entire file line by line.

---

## Step 2: Set Up the Project

### Required Files:

Create the following files:

1. `get_next_line.c` – contains the main logic of the function.
2. `get_next_line_utils.c` – contains helper functions.
3. `get_next_line.h` – the header file containing function prototypes and includes.

### Required External Functions:

You are allowed to use the following:

- `read()` – to read data from the file descriptor.
- `malloc()` – to allocate memory dynamically.
- `free()` – to free allocated memory.

### Forbidden Functions:

- `lseek()`
- Global variables

### **Example - read function**

```c
int fd = open("myfile.txt", O_RDONLY); // Open a file in read-only mode
char buffer[100];                      // Create a buffer of size 100
ssize_t bytes_read;

bytes_read = read(fd, buffer, 100);    // Read up to 100 bytes from fd into buffer
if (bytes_read > 0) {
    // Successfully read some data
    buffer[bytes_read] = '\0';         // Null-terminate the string for safe printing
    printf("Read: %s\n", buffer);
} else if (bytes_read == 0) {
    // Reached end of file (EOF)
    printf("End of file\n");
} else {
    // Error handling
    perror("Error reading file");
}

close(fd);                             // Close the file descriptor
```

## Step 3: Plan the Logic

### High-Level Flow:

1. **Read the file**: Use `read()` to get data from the file descriptor into a buffer.
2. **Process the data**: Search for a newline (`\n`). If found, return the data up to the newline.
3. **Handle left-over data**: Keep any leftover data (after the newline) for the next call to `get_next_line()`. You can use a **static variable** to store this data between calls.
4. **Return the line**: When a newline is encountered, return the line. If the file is finished, return `NULL`.

---

## Step 4: Implement the Function Step by Step

### 4.1: Write the `get_next_line()` Function

This function will:

- Use `read()` to fill a buffer with data from the file.
- Search the buffer for a newline character.
- If a newline is found, copy the line up to that point.
- Save any remaining characters in a static variable to be used in the next call.

Here’s a step-by-step breakdown of the function logic:

#### Step 4.1.1: Define the Static Variable

Since we need to retain the remaining part of the file between function calls, use a **static variable** to store this leftover data:

```c
static char *remainder;
```

#### Step 4.1.2: Read Data from File Descriptor

Use the `read()` function to read chunks of data into a buffer:

```c
char buffer[BUFFER_SIZE + 1];
int bytes_read = read(fd, buffer, BUFFER_SIZE);
```

- `BUFFER_SIZE` is the size of each chunk to be read.
- `buffer` holds the data read from the file descriptor.
- `read()` returns the number of bytes actually read.

#### Step 4.1.3: Find the Newline

You need to check if the buffer contains a newline (`\n`). If found, split the buffer at that point:

```c
char *newline_ptr = strchr(buffer, '\n');
```

- `newline_ptr` will point to the location of the first newline in the buffer.
- If a newline is found, return the string up to the newline.

#### Step 4.1.4: Handle Leftover Data

If there's data after the newline, store it in the static variable `remainder` for the next function call:

```c
if (newline_ptr) {
    remainder = strdup(newline_ptr + 1);  // Save everything after the newline
}
```

#### Step 4.1.5: Return the Line

Once a newline is found, return the line up to that point:

```c
char *line = strndup(buffer, newline_ptr - buffer + 1);
return line;
```

- This returns a string that includes the newline character if it's found.

### 4.2: Handle Edge Cases

#### Case 1: No More Data to Read

- If `read()` returns 0, it means the end of the file has been reached. Return `NULL` to indicate no more lines.

#### Case 2: Incomplete Line

- If the file ends without a newline (`\n`), return the remaining content.

---

## Step 5: Implement Helper Functions

### 5.1: Memory Management Functions

You will need functions to manage memory efficiently, such as:

- `ft_strdup()` – duplicates a string.
- `ft_strjoin()` – concatenates two strings.
- `ft_strchr()` – finds a character in a string.
- `ft_strndup()` – duplicates a string up to a given length.

Example: 

```c
char *ft_strjoin(char const *s1, char const *s2) {
    char *joined_str;
    if (!s1 || !s2)
        return (NULL);
    joined_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!joined_str)
        return (NULL);
    ft_strcpy(joined_str, s1);
    ft_strcat(joined_str, s2);
    return (joined_str);
}
```

---

## Step 6: Testing Your Code

### 6.1: Test with Various Buffer Sizes

Compile and test your code with different buffer sizes:

```bash
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
./a.out <file_to_read>
```

Try different buffer sizes like 1, 9999, and 1000000 to ensure that your function works with varying amounts of data read at once.

### 6.2: Test with Standard Input

Test the function with standard input by reading from the console:

```bash
./a.out
```

Type a few lines of text to ensure the function works as expected.

### 6.3: Test Edge Cases

Make sure your function handles:

- Empty files.
- Files without newline characters.
- Large files and small buffer sizes.

---

## Step 7: Bonus (Optional)

Once you’ve completed the mandatory part, try adding the following bonus features:

- **Multiple File Descriptors**: Allow the function to handle multiple file descriptors concurrently without mixing up data between them.

---

## Step 8: Submit Your Work

- Ensure that your `get_next_line.c`, `get_next_line_utils.c`, and `get_next_line.h` files are correctly named.
- Verify that your Makefile compiles everything as expected.
- Push your code to the assigned Git repository.

---

## Conclusion

This project is a great exercise in file handling, memory management, and working with static variables in C. Follow these steps carefully, and you'll have a solid implementation of the `get_next_line()` function.

Good luck!
