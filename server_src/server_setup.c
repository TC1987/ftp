/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:09:56 by tcho              #+#    #+#             */
/*   Updated: 2019/03/14 20:04:40 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include "libft.h"
#include "common.h"
#include "server.h"

void	create_directory(void)
{
	getcwd(g_path, sizeof(g_path));
	ft_strcat(g_path, "/root");
	mkdir(g_path, 0777);
	chdir(g_path);
	ft_memcpy(g_jail, g_path, sizeof(g_path));
}

int		create_socket(char *port)
{
	int					sd;
	int					enable;
	struct sockaddr_in	address;

	error_check((sd = socket(AF_INET, SOCK_STREAM, 0)), "socket");
	enable = 1;
	ft_memset(&address, 0, SOCK_SIZE);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(ft_atoi(port));
	error_check(setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &enable,
				sizeof(enable)), "setsockopt");
	error_check(bind(sd, (struct sockaddr *)&address,
				sizeof(address)), "bind");
	error_check(listen(sd, 5), "listen");
	printf("Listening on port %s\n", port);
	return (sd);
}

void	handle_client(int client, struct sockaddr_in client_info)
{
	char command[256];

	printf("%s:%d connected\n", inet_ntoa(client_info.sin_addr),
			ntohs(client_info.sin_port));
	ft_memset(command, 0, sizeof(command));
	while (recv(client, command, 256, 0))
	{
		if (!do_op(client, command))
		{
			printf("%s:%d disconnected\n", inet_ntoa(client_info.sin_addr),
					ntohs(client_info.sin_port));
			break ;
		}
		ft_memset(command, 0, sizeof(command));
	}
	close(client);
}

void	serve_clients(int sd)
{
	int					client;
	socklen_t			size;
	struct sockaddr_in	client_info;

	size = sizeof(client_info);
	ft_memset(&client_info, 0, size);
	while ((client =
				error_check(accept(sd, (struct sockaddr *)&client_info, &size),
					"client")))
	{
		if (fork() == 0)
		{
			handle_client(client, client_info);
			return ;
		}
		else
			close(client);
	}
}
