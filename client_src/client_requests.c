/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_requests.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:48:45 by tcho              #+#    #+#             */
/*   Updated: 2019/03/14 17:06:18 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "common.h"
#include "client.h"

extern char g_message[4096];
extern char g_cwd[4096];

int		check_command(char *command)
{
	int		status;
	char	**args;

	status = 0;
	args = ft_strsplit(command, ' ');
	if (ft_strequ(args[0], "ls") || ft_strequ(args[0], "cd") ||
			ft_strequ(args[0], "pwd") || ft_strequ(args[0], "get") ||
			ft_strequ(args[0], "put") || ft_strequ(args[0], "quit") ||
			ft_strequ(args[0], "lrm") || ft_strequ(args[0], "lcd") ||
			ft_strequ(args[0], "lls") || ft_strequ(args[0], "lpwd") ||
			ft_strequ(args[0], "lmkdir") || ft_strequ(args[0], "rm") ||
			ft_strequ(args[0], "mkdir"))
		status = 1;
	return (status);
}

int		do_local(char *command)
{
	if (ft_strnequ(command, "lrm", 2))
		return (do_lrm(command));
	if (ft_strnequ(command, "lcd", 3))
		return (do_lcd(command));
	if (ft_strnequ(command, "lls", 3))
		return (do_lls(command));
	if (ft_strnequ(command, "lpwd", 4))
		return (do_lpwd(command));
	if (ft_strnequ(command, "lmkdir", 6))
		return (do_lmkdir(command));
	return (0);
}

int		do_op(int socket, char *command)
{
	if (ft_strnequ(command, "ls", 2))
		return (do_ls(socket, command));
	if (ft_strnequ(command, "cd", 2))
		return (do_cd_rm_mkdir(socket, command));
	if (ft_strnequ(command, "pwd", 3))
		return (get_pwd(socket, command));
	if (ft_strnequ(command, "get", 3))
		return (get_file(socket, command));
	if (ft_strnequ(command, "put", 3))
		return (put_file(socket, command));
	if (ft_strnequ(command, "rm", 2))
		return (do_cd_rm_mkdir(socket, command));
	if (ft_strnequ(command, "mkdir", 5))
		return (do_cd_rm_mkdir(socket, command));
	if (ft_strnequ(command, "quit", 4))
		return (do_quit(socket, command));
	if (do_local(command))
		return (1);
	return (0);
}

void	get_input(char *command)
{
	int bytes;

	bytes = read(0, command, 256);
	if (bytes)
		command[bytes - 1] = '\0';
}

void	handle_requests(int sd)
{
	int		keep_alive;
	char	command[256];

	keep_alive = 1;
	prompt();
	while (keep_alive)
	{
		ft_putstr(">> ");
		get_input(command);
		if (ft_strequ(command, ""))
			continue;
		else if (check_command(command) == 0)
			printf("%sError: Not a valid command.%s\n", RED, RESET);
		else if (ft_strchr(command, '/') != NULL)
			printf("%sError: Command contains slashes.%s\n", RED, RESET);
		else
			keep_alive = do_op(sd, command);
	}
}
