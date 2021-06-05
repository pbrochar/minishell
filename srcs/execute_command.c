/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 10:58:21 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/05 12:06:44 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

int search_command(t_master *msh, char **arg)
{
	DIR *directory;
	struct dirent *files;
	int	i;

	i = 0;
	while (msh->path[i])
	{
		directory = opendir(msh->path[i]);
		if (directory == NULL)
			i++;
		files = readdir(directory);
		while (files != NULL)
		{
			if (ft_strcmp(arg[0], files->d_name) == 0)
			{
				closedir(directory);
				return (i);
			}
			files = readdir(directory);
		}
		closedir(directory);
		i++;
	}
	return (-1);
}

int	add_path_exec_command(t_master *msh, char **arg)
{
	int	i;
	char *command;
	size_t command_len;
	int pid;
	
	if (arg[0][0] == '.' || arg[0][0] == '/')
		command = arg[0];
	else
	{
		i = search_command(msh, arg);
		if (i == -1)
		{
			ft_printf("msh: command not found: %s\n", arg[0]);
			return (0);
		}
		command_len = ft_strlen(msh->path[i]) + ft_strlen(arg[0]) + 2;
		command = malloc(sizeof(char) * command_len);
		ft_strlcpy(command, msh->path[i], command_len);
		ft_strlcat(command, "/", command_len);
		ft_strlcat(command, arg[0], command_len);
	}
	if (!(pid = fork()))
		execve(command, arg, msh->envp);
	else
	{
		waitpid(pid, NULL, 0);
		free(command);
	}
	return (0);
}