#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>

// Standard functions (9)
char	*get_next_line(int fd);
char	*ft_strdup(const char *s);
// size_t	ft_strlcat_gnl(char *dst, const char *src, size_t dst_size);
size_t	ft_strlen(const char *s);
// int		ft_strcmp(const char *s1, const char *s2);
// void	*ft_memset(void *s, int c, size_t n);
char	*ft_strchr(const char *str, int search_chr);
char	*ft_strncpy(char *destination, const char *source, size_t n);
// size_t	ft_strlcpy(char *dst, const char *src, size_t dst_size);
char	*ft_strjoin_gnl(char const *s1, char const *s2);
void	*ft_calloc(size_t nitems, size_t size);

// Helper functions (3)
// char	*extract_line_and_update_remainder(char *new_line_ptr,
// 			char **remainder);
// ssize_t	read_and_append_remainder(int fd, char **remainder);
// void	handle_EOF(char **line, char **remainder);

#endif