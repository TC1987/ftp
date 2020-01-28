/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:47:05 by tcho              #+#    #+#             */
/*   Updated: 2019/03/14 17:05:35 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "common.h"
#include "client.h"

extern char g_message[4096];
extern char g_cwd[4096];

int		do_ls(int sd, char *command)
{
	send(sd, command, ft_strlen(command), 0);
	write_file(sd, ".tmp_ls");
	read_file(".tmp_ls");
	unlink(".tmp_ls");
	return (1);
}

int		do_quit(int sd, char *command)
{
	send(sd, command, ft_strlen(command), 0);
	return (0);
}

int		get_pwd(int sd, char *command)
{
	ssize_t	rec_bytes;
	char	buffer[SIZE];

	if (ft_word_count(command, ' ') != 1)
		printf("usage: pwd\n");
	else
	{
		send(sd, command, ft_strlen(command), 0);
		rec_bytes = recv(sd, buffer, sizeof(buffer), 0);
		buffer[rec_bytes] = '\0';
		printf("%s%s%s\n", CYAN, buffer, RESET);
	}
	return (1);
}

int		do_cd_rm_mkdir(int sd, char *command)
{
	ssize_t		bytes_received;
	char		**args;

	args = ft_strsplit(command, ' ');
	if (ft_word_count(command, ' ') != 2)
	{
		if (ft_strequ(args[0], "cd"))
			printf("usage: cd [path]\n");
		else if (ft_strequ(args[0], "rm"))
			printf("usage: rm [file_name]\n");
		else if (ft_strequ(args[0], "mkdir"))
			printf("usage: mkdir [directory]\n");
	}
	else
	{
		send(sd, command, ft_strlen(command), 0);
		bytes_received = recv(sd, g_message, sizeof(g_message), 0);
		g_message[bytes_received] = '\0';
		printf("%s%s%s\n", CYAN, g_message, RESET);
	}
	free_list(args);
	return (1);
}
