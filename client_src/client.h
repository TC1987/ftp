/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:51:54 by tcho              #+#    #+#             */
/*   Updated: 2019/03/14 20:50:33 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <sys/types.h>
# include <sys/socket.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <arpa/inet.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include "libft.h"
# include "common.h"

# define SIZE 256

char	g_message[4096];
char	g_cwd[4096];

void	free_list(char **list);
void	prompt(void);
int		error(char *message, int code);
int		create_and_connect(char *ip_address, char *port);

int		put_file(int sd, char *command);
void	read_file(char *file);
void	write_file_contents(int sd, int file_size, char *file_name);
int		write_file(int sd, char *file_name);
int		get_file(int sd, char *command);

int		do_ls(int sd, char *command);
int		do_quit(int sd, char *command);
int		get_pwd(int sd, char *command);
int		do_cd_rm_mkdir(int sd, char *command);

int		do_lrm(char *command);
int		do_lcd(char *command);
int		do_lls(char *command);
int		do_lpwd(char *command);
int		do_lmkdir(char *command);

int		check_command(char *command);
int		do_local(char *command);
int		do_op(int socket, char *command);
void	get_input(char *command);
void	handle_requests(int sd);

#endif
