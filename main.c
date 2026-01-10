/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laraus <laraus@student.lisboa42.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:06:30 by laraus            #+#    #+#             */
/*   Updated: 2026/01/10 15:20:07 by laraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
    int fd;
    char *line;
    int i;

    // --- TEST 1: Read from a normal text file ---
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("open test.txt");
        return (1);
    }
    printf("----- Reading test.txt -----\n");
    i = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line %d: [%s]\n", i, line);
        free(line);
        i++;
        if (i > 100) // prevent infinite loops if GNL is broken
            break;
    }
    close(fd);

    // --- TEST 2: Read from empty file ---
    fd = open("empty.txt", O_RDONLY);
    if (fd != -1)
    {
        printf("----- Reading empty.txt -----\n");
        line = get_next_line(fd);
        if (!line)
            printf("Correctly returned NULL for empty file\n");
        close(fd);
    }

    // --- TEST 3: Read from terminal (stdin) ---
    printf("----- Reading from terminal -----\n");
    printf("Enter lines (Ctrl+D to stop):\n");
    i = 0;
    while ((line = get_next_line(0)) != NULL)
    {
        printf("STDIN line %d: [%s]\n", i, line);
        free(line);
        i++;
        if (i > 50)
            break;
    }

    // --- TEST 4: File with consecutive newlines ---
    fd = open("newlines.txt", O_RDONLY);
    if (fd != -1)
    {
        printf("----- Reading newlines.txt -----\n");
        i = 0;
        while ((line = get_next_line(fd)) != NULL)
        {
            printf("Line %d: [%s]\n", i, line);
            free(line);
            i++;
        }
        close(fd);
    }

    // --- TEST 5: File with very long line (larger than BUFFER_SIZE) ---
    fd = open("longline.txt", O_RDONLY);
    if (fd != -1)
    {
        printf("----- Reading longline.txt -----\n");
        i = 0;
        while ((line = get_next_line(fd)) != NULL)
        {
            printf("Line %d: [%s]\n", i, line);
            free(line);
            i++;
            if (i > 10) // just in case
                break;
        }
        close(fd);
    }

    return (0);
}
*/

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char *files[] = {
		"files/empty",
		"files/nl",
		"files/41_no_nl",
		"files/41_with_nl",
		"files/42_no_nl",
		"files/42_with_nl",
		"files/43_no_nl",
		"files/43_with_nl",
		"files/multiple_nlx5",
		"files/multiple_line_no_nl",
		"files/multiple_line_with_nl",
		"files/alternate_line_nl_no_nl",
		"files/alternate_line_nl_with_nl",
		"files/big_line_no_nl",
		"files/big_line_with_nl"
	};

	int num_files = sizeof(files) / sizeof(files[0]);
	for (int i = 0; i < num_files; i++)
	{
		int fd = open(files[i], O_RDONLY);
		if (fd < 0)
		{
			perror(files[i]);
			continue;
		}

		printf("\n=== Testing file: %s ===\n", files[i]);
		char *line;
		int line_num = 1;  // track line numbers for clarity
		while ((line = get_next_line(fd)) != NULL)
		{
			// Print line number, file, and brackets
			printf("%2d | [%s]\n", line_num, line);
			free(line);
			line_num++;
		}
		close(fd);
		printf("=== End of %s ===\n", files[i]);
	}

	return 0;
}
