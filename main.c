/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 12:47:53 by azerfaou          #+#    #+#             */
/*   Updated: 2024/10/22 12:19:52 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

// void int_to_ascii(int c)
// {
//     // Convert integer to string (ASCII representation)
//     dprintf(2, "%i\n", (int)c);

//     // return ascii_str;
// }

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	// printf("%s", "HELLO");
	
// 	line = NULL;
// 	fd = open("test_files/test_file_1.txt", O_RDONLY);
// 	// fd = open("test_files/only_nl.txt", O_RDONLY);
// 	printf("BUFFER_SIZE: %d\n", BUFFER_SIZE);
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		printf("%s", "|");
// 		printf("%s", line);
// 		// do
// 		// {
// 		// 	int_to_ascii(*line);
// 		// } while (line && *line && line++);
// 		free(line);
// 		line = NULL;
// 	}
// 	free(line);
// 	line = NULL;
// 	close(fd);
// }
