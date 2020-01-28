/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:45:19 by tcho              #+#    #+#             */
/*   Updated: 2019/03/14 20:07:12 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "common.h"
#include "client.h"

extern char g_message[4096];
extern char g_cwd[4096];

int		put_file(int sd, char *command)
{
	int		fd;
	char	*file;
	char	buffer[256];

	ft_memset(buffer, 0, 256);
	ft_strcpy(buffer, command);
	if (ft_word_count(buffer, ' ') != 2)
		return (display("usage: put [file_name]", 1));
	file = ft_strrchr(buffer, ' ') + 1;
	if ((fd = open(file, O_RDONLY)) == -1)
		return (display("Error: Invalid directory, file, or permissions.", 1));
	send(sd, buffer, 256, 0);
	if (send_file_contents(sd, fd))
		printf("%sSuccess: %s has finished uploading.%s\n", GREEN, file, RESET);
	return (1);
}

void	read_file(char *file)
{
	int		fd;
	char	buffer[256];
	int		bytes;

	ft_memset(buffer, 0, sizeof(buffer));
	fd = open(file, O_RDONLY);
	while ((bytes = read(fd, buffer, sizeof(buffer) - 1)) > 0)
	{
		printf("%s%s%s", GREEN, buffer, RESET);
		fflush(stdout);
	}
	close(fd);
}

void	write_file_contents(int sd, int file_size, char *file_name)
{
	int		fd;
	int		nbytes;
	int		remaining;
	char	*buffer;

	buffer = malloc(sizeof(char) * file_size);
	remaining = file_size;
	error_check((fd = open(file_name, O_RDWR | O_CREAT, 0777)), "open");
	while (remaining > 0 && (nbytes = recv(sd, buffer, file_size, 0)) > 0)
	{
		if (!ft_strequ(file_name, ".tmp_ls"))
			printf("%s%d / %d bytes received%s\n", YELLOW,
					nbytes, file_size, RESET);
		write(fd, buffer, nbytes);
		remaining -= nbytes;
	}
	free(buffer);
	close(fd);
}

int		write_file(int sd, char *file_name)
{
	int file_size;

	recv(sd, &file_size, sizeof(file_size), 0);
	if (file_size == -1)
		return (display("Error: Invalid directory, file, or permissions.", 0));
	write_file_contents(sd, file_size, file_name);
	return (1);
}

int		get_file(int sd, char *command)
{
	char *file;

	if (ft_word_count(command, ' ') != 2)
		return (display("usage: get [file_name]", 1));
	send(sd, command, ft_strlen(command), 0);
	file = ft_strrchr(command, ' ') + 1;
	if (write_file(sd, file))
		printf("%sSuccess: %s has downloaded.%s\n", GREEN, file, RESET);
	return (1);
}
