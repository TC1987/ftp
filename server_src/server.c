/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 19:31:26 by tcho              #+#    #+#             */
/*   Updated: 2019/03/14 20:49:40 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "common.h"
#include "server.h"

#define SIZE 256

char	g_path[SIZE];
char	g_jail[SIZE];
char	g_message[4096];

void	free_list(char **list)
{
	char **head;

	if (!list || !(*list))
		return ;
	head = list;
	while (*head)
	{
		free(*head);
		head++;
	}
	free(list);
}

int		do_op(int sd, char *command)
{
	if (ft_strnequ(command, "ls", 2))
		return (send_ls(sd, command));
	else if (ft_strnequ(command, "cd", 2))
		return (change_dir(sd, command));
	else if (ft_strnequ(command, "pwd", 3))
		return (send_pwd(sd));
	else if (ft_strnequ(command, "get", 3))
		return (send_file(sd, command));
	else if (ft_strnequ(command, "put", 3))
		return (get_file(sd, command));
	else if (ft_strnequ(command, "rm", 2))
		return (do_rm(sd, command));
	else if (ft_strnequ(command, "mkdir", 5))
		return (do_mkdir(sd, command));
	else if (ft_strnequ(command, "quit", 4))
		return (0);
	return (0);
}

int		main(int argc, char *argv[])
{
	int sd;

	if (argc != 2)
	{
		printf("usage: ./s [port]\n");
		exit(-1);
	}
	create_directory();
	sd = create_socket(argv[1]);
	serve_clients(sd);
}
