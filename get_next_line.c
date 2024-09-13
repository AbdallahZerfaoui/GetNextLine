#include "get_next_line.h"


char *get_next_line(int fd)
{
    static char *remainder = NULL;
    ssize_t     bytes_read = 1;
    char        *new_line_ptr = NULL;
    char        *line;

    while (!(new_line_ptr = ft_strchr(remainder, '\n')) && bytes_read > 0)
    {
        bytes_read = read_and_append_remainder(fd, &remainder);
        if (bytes_read == 0)
        {
            handle_EOF(&line, &remainder);
            return (line);
        }
    }
    line = extract_line_and_update_remainder
                    (new_line_ptr, &remainder);
    return (line);
}