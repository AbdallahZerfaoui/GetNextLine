#include "get_next_line.h"

char *extract_line_and_update_remainder
        (char *new_line_ptr, char **remainder)
{
    size_t line_len;
    char *new_remainder;
    char *line;

    line_len = new_line_ptr - *remainder + 1; // +1 to include the newline character
    line = (char *) malloc(line_len + 1); // +1 for the NULL termination
    line = ft_strncpy(line, *remainder, line_len); // consider using ft_strlcpy
    line[line_len] = '\0';
    new_remainder = ft_strdup(new_line_ptr + 1);
    free(*remainder);
    *remainder = new_remainder;
    return (line);
}

ssize_t read_and_append_remainder(int fd, char **remainder)
{
    char    buffer[BUFFER_SIZE + 1];
    ssize_t bytes_read = 1;

        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read > 0)
        {
            buffer[bytes_read] = '\0';
            
            if (!(*remainder))
                *remainder = ft_strdup(buffer);
            else
                *remainder = ft_strjoin_gnl(*remainder, buffer);
        }
        return bytes_read;
}

void handle_EOF(char **line, char **remainder)
{
    *line = ft_strdup(*remainder);
    if (ft_strcmp(*remainder, "") != 0)
        free(*remainder);
    ft_memset(*remainder, '\0', ft_strlen(*remainder));
}