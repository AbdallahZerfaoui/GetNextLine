/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 12:47:53 by azerfaou          #+#    #+#             */
/*   Updated: 2024/10/16 13:50:04 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int fd = open("test_files/test_file_1_short.txt", O_RDONLY);
	// int fd = open("test_files/test_file_1.txt", O_RDONLY);
	char *line;

	printf("BUFFER_SIZE: %d\n", BUFFER_SIZE);
	// line = get_next_line(fd);
	// if (!line)
	// {
	// 	printf("NULL\n");
	// 	return (0);
	// }
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", "|");
		printf("%s", line);
		free(line);
		line = NULL;
		// line = get_next_line(fd);
	}
	close(fd);
	// system("leaks get_next_line.exe");
}
