/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:28:32 by azerfaou          #+#    #+#             */
/*   Updated: 2024/10/14 20:39:05 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


static char	*extract_line_and_update_remainder(char *new_line_ptr, char **remainder)
{
	size_t	line_len;
	char	*new_remainder = NULL;
	char	*line;

	line_len = new_line_ptr - *remainder + 1;
	line = (char *)ft_calloc(line_len + 1, sizeof(char));
	if (!line)
		return (NULL);
	line = ft_strncpy(line, *remainder, line_len); // consider using ft_strlcpy
	// ft_strlcpy(line, *remainder, line_len); // consider using ft_strlcpy
	// line[line_len] = '\0';
	if (*(new_line_ptr + 1) != '\0')
	{
		new_remainder = ft_strdup(new_line_ptr + 1);
		if (!new_remainder)
			return (NULL);
	}
	free(*remainder);
	*remainder = new_remainder;
	// if (!*new_remainder)
	// 	free(new_remainder);
	return (line);
}

static ssize_t	read_and_append_remainder(int fd, char **remainder)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes_read;
	char	*new_remainder;

	bytes_read = 1; //do i need it??
	new_remainder = NULL;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if (!(*remainder))
			*remainder = ft_strdup(buffer);
		else
		{
			new_remainder = ft_strjoin_gnl(*remainder, buffer);
			if (!new_remainder)
			{
				free(*remainder);
				*remainder = NULL;
				return (-1);
			}
			else
			{
				free(*remainder);
				*remainder = new_remainder;
			}
		}
	}

// dprintf(2,">>>%p<<<", new_remainder);
	return (bytes_read);
}

static void	handle_EOF(char **line, char **remainder)
{
	// int	remainder_len;

	if (*remainder)
	{
		*line = ft_strdup(*remainder);
		if (!*line)
			return ;
		free(*remainder);
		*remainder = NULL;
		// free(*remainder);
		// remainder_len = ft_strlen(*remainder);
		// while (remainder_len--)
		// 	(*remainder)[remainder_len] = '\0';
	}
	else
		*line = NULL;
}

char	*get_next_line(int fd)
{
	static char *remainder = NULL;
	ssize_t bytes_read = 0;
	char *new_line_ptr;
	char *line;

	line = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remainder)
	{
		bytes_read = read_and_append_remainder(fd, &remainder);
		if (bytes_read <= 0) // fix the invalid fd case in paco
		{
			free(remainder);
			remainder = NULL;
			return (NULL);
		}
	}
	new_line_ptr = ft_strchr(remainder, '\n');
	// Continue reading until a newline character is found or EOF is reached
	
	if (new_line_ptr) // a revoir
	{
		// free(line);
		line = extract_line_and_update_remainder(new_line_ptr, &remainder);
		return (line);
	}
	bytes_read = read_and_append_remainder(fd, &remainder);
	if (bytes_read == 0)
	{
		if (remainder && *remainder)
			return (handle_EOF(&line, &remainder), line);
		// return (NULL);
	}
	else if (bytes_read < 0)
	{
		free(remainder);
		remainder = NULL;
		return (NULL);
	}

	// line = get_next_line(fd);
	// return (line);
	// free(line);
	return (get_next_line(fd));
}
