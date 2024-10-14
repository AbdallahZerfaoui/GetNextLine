/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:27:20 by azerfaou          #+#    #+#             */
/*   Updated: 2024/10/14 16:05:41 by azerfaou         ###   ########.fr       */
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
	if (!ptr)
		return (NULL);
	// size = 0;
	// while (s[size])
	// {
	// 	ptr[size] = s[size];
	// 	size++;
	// }
	// ptr[size] = '\0';
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

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*str_result;
	// char	*str_result_backup;

	if (!s1 && !s2)
		return (NULL);
	str_result = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!str_result)
		return (NULL);
	ft_strncpy(str_result, s1, ft_strlen(s1));
	ft_strncpy(str_result + ft_strlen(s1), s2, ft_strlen(s2));
	// ft_strlcat_gnl(str_result, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	// free((char *)s1); // free remainder(s1) in get_next_line
	return (str_result);
}

void	*ft_calloc(size_t nitems, size_t size)
{
	void *ptr;
	size_t total_size;

	total_size = nitems * size;
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	while (total_size--)
		((unsigned char *)ptr)[total_size] = 0;
	return (ptr);
}
