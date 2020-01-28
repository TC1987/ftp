/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:44:28 by tcho              #+#    #+#             */
/*   Updated: 2019/03/14 17:05:55 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "common.h"
#include "client.h"

extern char g_message[4096];
extern char g_cwd[4096];

int		do_lrm(char *command)
{
	char *file;

	if (ft_word_count(command, ' ') != 2)
		printf("usage: rm [file_name]\n");
	else
	{
		file = ft_strrchr(command, ' ') + 1;
		if (!error_check_return(unlink(file), "lrm"))
			return (1);
		printf("%sSuccess: %s has been removed%s\n", GREEN, file, RESET);
	}
	return (1);
}

int		do_lcd(char *command)
{
	char	*cwd;
	char	*path;

	if (ft_word_count(command, ' ') != 2)
		printf("usage: lcd [path]\n");
	else
	{
		path = ft_strrchr(command, ' ') + 1;
		if (!error_check_return(chdir(path), "lcd"))
			return (1);
		else
		{
			cwd = getcwd(NULL, 0);
			ft_strcpy(g_cwd, cwd);
			printf("%s%s%s\n", CYAN, g_cwd, RESET);
			free(cwd);
		}
	}
	return (1);
}

int		do_lls(char *command)
{
	pid_t	pid;
	char	**args;

	args = ft_strsplit(command, ' ');
	pid = fork();
	if (pid == 0)
		execv("/bin/ls", args);
	else
	{
		wait4(pid, NULL, 0, NULL);
		free_list(args);
	}
	return (1);
}

int		do_lpwd(char *command)
{
	char *cwd;

	if (ft_word_count(command, ' ') != 1)
		printf("usage: lpwd\n");
	else
	{
		cwd = getcwd(NULL, 0);
		printf("%s%s%s\n", CYAN, cwd, RESET);
		free(cwd);
	}
	return (1);
}

int		do_lmkdir(char *command)
{
	char *directory;

	if (ft_word_count(command, ' ') != 2)
		printf("usage: lmkdir [directory]\n");
	else
	{
		directory = ft_strrchr(command, ' ') + 1;
		error_check_return(mkdir(directory, 0777), "lmkdir");
	}
	return (1);
}
