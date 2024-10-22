/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:28:32 by azerfaou          #+#    #+#             */
/*   Updated: 2024/10/22 12:24:40 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlcpy(char *dst, char *src, size_t dstsize)
{
	unsigned long	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

// void	gnl_bzero(void *s, size_t n)
// {
// 	unsigned char	*d;

// 	d = s;
// 	while (0 < n)
// 		d[n-- - 1] = 0;
// }

// char	*ft_strjoin_gnl(char const *s1, char const *s2)
// {
// 	int		i;
// 	int		j;
// 	char	*ptr;

// 	i = -1;
// 	j = -1;
// 	if (s1 == NULL)
// 		return (gnl_bzero((char *)s2, ft_strlen(s2)), NULL);
// 	ptr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
// 	if (ptr == NULL)
// 		return (NULL);
// 	while (s1 && s1[++i])
// 		ptr[i] = s1[i];
// 	while (s2 && s2[++j])
// 		ptr[i + j] = s2[j];
// 	ptr[i + j] = '\0';
// 	free(s1);
// 	s1 = NULL;
// 	return (ptr);
// }

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*str_result;

	// if (!s1 && !s2)
	// 	return (NULL);
	if (!s1)
		return (memset((char *)s2, 0, ft_strlen(s2)), NULL);
	str_result = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1,
			sizeof(char));
	// str_result = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	// fprintf(file, "str_result from join: %p\n", str_result);
	if (!str_result)
		return (NULL);
	if (s1 && *s1)
		ft_strncpy(str_result, s1, ft_strlen(s1));
		// gnl_strlcpy(str_result, (char *)s1, ft_strlen(s1));
	if (s2 && *s2)
		ft_strncpy(str_result + ft_strlen(s1), s2, ft_strlen(s2));
		// gnl_strlcpy(str_result + ft_strlen(s1), (char *)s2, ft_strlen(s2));
	// str_result[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (str_result);
}

static char	*extract_and_update(char *new_line_ptr,
		char **remainder)
{
	size_t	line_len;
	char	*new_remainder;
	char	*line = NULL;

	new_remainder = NULL;

	line_len = new_line_ptr - *remainder + 1;
	if (line_len >= 0)
		line = (char *)ft_calloc(line_len + 1, sizeof(char));
	if (!line)
		return (line = NULL, NULL);
	line = ft_strncpy(line, *remainder, line_len);
	if (*(new_line_ptr + 1) != '\0')
	{
		new_remainder = ft_strdup(new_line_ptr + 1);
		if (!new_remainder)
			return (free(line), free(new_remainder), new_remainder = NULL, NULL);
	}
	free(*remainder);
	*remainder = new_remainder;
	return (line);
}

static ssize_t	read_and_append(int fd, char **remainder)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes_read;
	char	*new_remainder;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
		return (free(*remainder), *remainder = NULL, -1);
	if (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (!(*remainder))
		{
			*remainder = ft_strdup(buffer);
			if (!*remainder)
				return (-1);
		}
		else
		{
			new_remainder = ft_strjoin_gnl(*remainder, buffer);
			if (!new_remainder)
			{
				if (*remainder && **remainder)
				{
					// free(new_remainder);
					free(*remainder);
					*remainder = NULL;
					new_remainder = NULL;
				}
				return (-1);
			}
			else if (*remainder && **remainder)
			{
				free(*remainder);
				*remainder = new_remainder;
			}
		}
	}
	return (bytes_read);
}
/***
 * @brief this function handles the end of file
 * @param line the line to be returned
 * @param remainder the remainder of the file
 * @return void
 *
 * @note you must free the reminder before checking line
 */
static void	handle_eof(char **line, char **remainder)
{
	if (*remainder && **remainder)
	{
		*line = ft_strdup(*remainder);
		free(*remainder);
		*remainder = NULL;
		if (!*line)
			return ;
	}
	else
		*line = NULL;
}

/**
 * @brief fgsfgdofgdfgdg
 * @param fd bye
 * @return char*
 *
 * @note fgsfgdofgdfgdg
 */
char	*get_next_line(int fd)
{
	ssize_t	bytes_read;
	char	*new_line_ptr = NULL;
	char	*line = NULL; //to remove if not needed
	static char *remainder = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (free(remainder), free(line), remainder = NULL, line = NULL, NULL);
		// return(gnl_bzero(remainder, ft_strlen(remainder)), NULL);
	while(1)
	{
		bytes_read = read_and_append(fd, &remainder);
		if (bytes_read < 0)
			return (free(remainder), remainder = NULL, NULL);
		new_line_ptr = ft_strchr(remainder, '\n');
		if (new_line_ptr)
			return (line = extract_and_update(new_line_ptr, &remainder), line);
		if (bytes_read == 0 && remainder && *remainder)
			return (handle_eof(&line, &remainder), remainder = NULL, line);
		else if (bytes_read == 0)
			return (free(remainder), remainder = NULL, NULL);
	}
}
