/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 17:13:04 by tcho              #+#    #+#             */
/*   Updated: 2019/03/14 20:50:02 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <sys/socket.h>
# include <netinet/in.h>

# define SIZE 256

char	g_path[SIZE];
char	g_jail[SIZE];
char	g_message[4096];

void	free_list(char **list);
int		do_op(int sd, char *command);

int		send_ls(int sd, char *command);
int		change_dir(int sd, char *command);
int		send_pwd(int sd);
int		do_rm(int sd, char *command);
int		do_mkdir(int sd, char *command);

int		get_file(int sd, char *command);
int		send_file(int sd, char *command);

void	create_directory(void);
int		create_socket(char *port);
void	handle_client(int client, struct sockaddr_in client_info);
void	serve_clients(int sd);

#endif
