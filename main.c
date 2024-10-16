/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 12:47:53 by azerfaou          #+#    #+#             */
/*   Updated: 2024/10/16 19:26:36 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int		fd;
	char	*line;

	line = NULL;
	// fd = open("test_files/read_error.txt", O_RDONLY);
	fd = open("test_files/1char.txt", O_RDONLY);
	printf("BUFFER_SIZE: %d\n", BUFFER_SIZE);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", "|");
		printf("%s", line);
		free(line);
		line = NULL;
	}
	close(fd);
}
