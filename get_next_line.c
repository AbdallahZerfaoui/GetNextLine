/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:28:32 by azerfaou          #+#    #+#             */
/*   Updated: 2024/10/16 16:32:51 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line_and_update_remainder(char *new_line_ptr,
		char **remainder)
{
	size_t	line_len;
	char	*new_remainder;
	char	*line;

	new_remainder = NULL;
	line_len = new_line_ptr - *remainder + 1;
	line = (char *)ft_calloc(line_len + 1, sizeof(char));
	if (!line)
		return (NULL);
	line = ft_strncpy(line, *remainder, line_len);
	if (*(new_line_ptr + 1) != '\0')
	{
		new_remainder = ft_strdup(new_line_ptr + 1);
		if (!new_remainder)
			return (NULL);
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

	bytes_read = 1; // do i need it??
	new_remainder = NULL;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
		return (free(*remainder), *remainder = NULL, -1);
	if (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (!(*remainder))
			*remainder = ft_strdup(buffer);
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
		if (!*line)
			return ;
		free(*remainder);
		*remainder = NULL;
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
	static char	*remainder = NULL;
	ssize_t		bytes_read;
	char		*new_line_ptr;
	char		*line;

	// remainder = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = read_and_append_remainder(fd, &remainder);
	new_line_ptr = ft_strchr(remainder, '\n');
	if (new_line_ptr) // a revoir
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
