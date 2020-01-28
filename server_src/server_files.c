/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:08:19 by tcho              #+#    #+#             */
/*   Updated: 2019/03/14 20:05:01 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include "libft.h"
#include "common.h"
#include "server.h"

int		get_file(int sd, char *command)
{
	int		fd;
	int		remaining;
	int		file_size;
	int		nbytes;
	char	*buffer;

	recv(sd, &file_size, sizeof(int), 0);
	if (file_size == -1)
		return (display("Must be a valid file.", 1));
	remaining = file_size;
	buffer = malloc(sizeof(char) * file_size);
	error_check((fd = open(ft_strchr(command, ' ') + 1,
					O_WRONLY | O_CREAT | O_TRUNC, 0777)), "open");
	while (remaining > 0 && (nbytes = recv(sd, buffer, file_size, 0)) > 0)
	{
		printf("%d / %d received\n", nbytes, file_size);
		write(fd, buffer, nbytes);
		remaining -= nbytes;
	}
	close(fd);
	printf("Success: %s has downloaded.\n", ft_strchr(command, ' ') + 1);
	free(buffer);
	return (1);
}

int		send_file(int sd, char *command)
{
	int		fd;
	char	*file;

	if (ft_word_count(command, ' ') != 2)
		return (1);
	file = ft_strrchr(command, ' ') + 1;
	fd = open(file, O_RDONLY);
	if (send_file_contents(sd, fd))
		printf("Success: %s has been sent.\n", file);
	return (1);
}
