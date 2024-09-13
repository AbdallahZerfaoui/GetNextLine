#include "get_next_line.h"
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
    int fd = open("test_files/test_file_1.txt", O_RDONLY);
    char *line;

    printf("BUFFER_SIZE: %d\n", BUFFER_SIZE);
    line = get_next_line(fd);
    while (strcmp(line, "") != 0)
    {
        // printf("i: %d\n", i);
        if (line)
        {
            printf("%s", "|");
            printf("%s", line);
            // printf("%s\n", "|");
            free(line);
        }
        line = get_next_line(fd);
    }
    close(fd);
}