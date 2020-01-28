/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 19:24:09 by tcho              #+#    #+#             */
/*   Updated: 2019/03/14 20:48:23 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "libft.h"
#include "common.h"
#include "client.h"

extern char	g_message[4096];
extern char	g_cwd[4096];

void	prompt(void)
{
	printf("%s------------------------------------------------\n", YELLOW);
	printf("-                                              -\n");
	printf("-                FTP SERVER                    -\n");
	printf("-                                              -\n");
	printf("------------------------------------------------\n\n");
	printf("Server Commands: ls cd pwd get put rm mkdir quit\n\n");
	printf("Local Commands: lrm lcd lls lpwd lmkdir%s\n\n", RESET);
}

int		error(char *message, int code)
{
	printf("%s\n", message);
	return (code);
}

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

int		create_and_connect(char *ip_address, char *port)
{
	int					sd;
	struct sockaddr_in	address;

	error_check((sd = socket(AF_INET, SOCK_STREAM, 0)), "socket");
	ft_memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = ft_strequ(ip_address, "localhost") ?
		inet_addr("127.0.0.1") : inet_addr(ip_address);
	address.sin_port = htons(ft_atoi(port));
	error_check(connect(sd, (struct sockaddr *)&address, \
				sizeof(address)), "connect");
	return (sd);
}

int		main(int argc, char *argv[])
{
	int sd;

	if (argc != 3)
	{
		printf("usage: ./c [ip] [port]\n");
		exit(-1);
	}
	sd = create_and_connect(argv[1], argv[2]);
	handle_requests(sd);
	close(sd);
}
