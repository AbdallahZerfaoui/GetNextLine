/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 12:47:53 by azerfaou          #+#    #+#             */
/*   Updated: 2024/10/14 13:46:47 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int	main(void)
{
	// int fd = open("test_files/one_line_wo_nl.txt", O_RDONLY);
	int fd = open("test_files/test_file_1.txt", O_RDONLY);
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
		// line = get_next_line(fd);
	}
	close(fd);
}
