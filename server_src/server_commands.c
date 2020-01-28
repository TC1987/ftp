/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:11:07 by tcho              #+#    #+#             */
/*   Updated: 2019/03/14 20:07:48 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "libft.h"
#include "common.h"
#include "server.h"

int		send_ls(int sd, char *command)
{
	int		fd;
	pid_t	pid;
	char	**args;

	error_check((fd = open(".tmp_ls",
					O_RDWR | O_TRUNC | O_CREAT, 0777)), "open");
	args = ft_strsplit(command, ' ');
	error_check((pid = fork()), "fork");
	if (pid == 0)
	{
		dup2(fd, 1);
		dup2(fd, 2);
		execv("/bin/ls", args);
	}
	else
	{
		wait4(pid, NULL, 0, NULL);
		send_file_contents(sd, fd);
		unlink(".tmp_ls");
		free_list(args);
	}
	return (1);
}

int		change_dir(int sd, char *command)
{
	char	*path;
	char	*current_path;

	path = ft_strrchr(command, ' ') + 1;
	current_path = ft_strdup(g_path);
	if (chdir(path) == -1 || !ft_strnequ(g_jail,
				getcwd(g_path, sizeof(g_path)), ft_strlen(g_jail)))
	{
		ft_strcpy(g_path, current_path);
		chdir(g_path);
		ft_strcpy(g_message, "Error: Invalid path or directory.");
	}
	else
		ft_strcpy(g_message, g_path);
	send(sd, g_message, sizeof(g_message), 0);
	free(current_path);
	return (1);
}

int		send_pwd(int sd)
{
	send(sd, g_path, ft_strlen(g_path), 0);
	return (1);
}

int		do_rm(int sd, char *command)
{
	char *file;

	file = ft_strrchr(command, ' ') + 1;
	if (unlink(file) == -1)
		ft_strcpy(g_message, "Error: Invalid directory, file, or permissions.");
	else
	{
		ft_strcpy(g_message, "Success: ");
		ft_strcat(g_message, file);
		ft_strcat(g_message, " has been successfully removed.");
	}
	send(sd, g_message, sizeof(g_message), 0);
	return (1);
}

int		do_mkdir(int sd, char *command)
{
	char *dir;

	dir = ft_strrchr(command, ' ') + 1;
	if (mkdir(dir, 0777) == -1)
	{
		ft_strcpy(g_message, "Error: ");
		ft_strcat(g_message, dir);
		ft_strcat(g_message, " already exists.");
	}
	else
	{
		ft_strcpy(g_message, "Success: ");
		ft_strcat(g_message, dir);
		ft_strcat(g_message, " has been successfully created.");
	}
	send(sd, g_message, sizeof(g_message), 0);
	return (1);
}
