/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:27:20 by azerfaou          #+#    #+#             */
/*   Updated: 2024/10/16 19:54:14 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	if (!s)
		return (size);
	while (*s)
	{
		size++;
		s++;
	}
	return (size);
}

char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	size;

	size = 0;
	while (s[size])
		size++;
	ptr = (char *)ft_calloc(size + 1, sizeof(char));
	// fprintf(file, "ptr from strdup: %p\n", ptr);
	if (!ptr)
		return (NULL);
	ptr = ft_strncpy(ptr, s, size);
	return (ptr);
}

char	*ft_strchr(const char *str, int search_chr)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == search_chr)
			return ((char *)str);
		str++;
	}
	if (*str == search_chr)
		return ((char *)str);
	return (NULL);
}

char	*ft_strncpy(char *destination, const char *source, size_t n)
{
	size_t	i;

	i = 0;
	while (source[i] && i < n)
	{
		destination[i] = source[i];
		i++;
	}
	while (i < n)
	{
		destination[i] = '\0';
		i++;
	}
	return (destination);
}

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*ptr;
	size_t	total_size;

	total_size = nitems * size;
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	while (total_size--)
		((unsigned char *)ptr)[total_size] = 0;
	return (ptr);
}
