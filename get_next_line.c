/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:28:32 by azerfaou          #+#    #+#             */
/*   Updated: 2024/10/16 20:04:34 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*str_result;

	if (!s1 && !s2)
		return (NULL);
	str_result = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1,
			sizeof(char));
	// fprintf(file, "str_result from join: %p\n", str_result);
	if (!str_result)
		return (NULL);
	ft_strncpy(str_result, s1, ft_strlen(s1));
	ft_strncpy(str_result + ft_strlen(s1), s2, ft_strlen(s2));
	return (str_result);
}

static char	*extract_line_and_update_remainder(char *new_line_ptr,
		char **remainder)
{
	size_t	line_len;
	char	*new_remainder;
	char	*line;

	new_remainder = NULL;
	line_len = new_line_ptr - *remainder + 1;
	line = (char *)ft_calloc(line_len + 1, sizeof(char));
	// fprintf(file, "line from extract: %p\n", line);
	if (!line)
		return (line = NULL, NULL);
	line = ft_strncpy(line, *remainder, line_len);
	if (*(new_line_ptr + 1) != '\0')
	{
		new_remainder = ft_strdup(new_line_ptr + 1);
		if (!new_remainder)
			return (free(line), new_remainder = NULL, NULL);
	}
	free(*remainder);
	*remainder = new_remainder;
	return (line);
}

static ssize_t	read_and_append_remainder(int fd, char **remainder)
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
				return (free(*remainder), *remainder = NULL, -1);
			else
			{
				free(*remainder);
				*remainder = new_remainder;
			}
		}
	}
	return (bytes_read);
}

static void	handle_eof(char **line, char **remainder)
{
	if (*remainder)
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
	char	*new_line_ptr;
	char	*line;
	static char *remainder = NULL; //???? is it norminette friendly

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = read_and_append_remainder(fd, &remainder);
	if (bytes_read < 0)
		return (free(remainder), remainder = NULL, NULL);
	new_line_ptr = ft_strchr(remainder, '\n');
	// printf("line: %s && reminder : %s\n", line, remainder);
	if (new_line_ptr)
	{
		line = extract_line_and_update_remainder(new_line_ptr, &remainder);
		return (line);
	}
	if (bytes_read == 0)
	{
		if (remainder && *remainder)
			return (handle_eof(&line, &remainder), line);
		else
			return (free(remainder), remainder = NULL, NULL);
	}
	return (get_next_line(fd));
}
