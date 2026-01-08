/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laraus <laraus@student.lisboa42.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:06:30 by laraus            #+#    #+#             */
/*   Updated: 2026/01/08 16:43:14 by laraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

