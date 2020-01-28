/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 03:37:59 by tcho              #+#    #+#             */
/*   Updated: 2019/03/14 20:51:27 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <sys/stat.h>
# define SOCK_SIZE	sizeof(struct sockaddr_in)
# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define RESET		"\x1b[0m"

int		display(char *message, int code);
int		error_check(int return_value, char *subject);
int		error_check_return(int return_value, char *subject);
int		check_file(int sd, int fd, struct stat fd_info);
int		send_file_contents(int sd, int fd);

#endif
