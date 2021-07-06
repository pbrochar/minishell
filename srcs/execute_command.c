/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 10:58:21 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/06 19:01:11 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

int search_command(t_master *msh, char **arg)
{
	DIR				*directory;
	struct dirent	*files;
	int				i;

	i = 0;
	while (msh->path[i])
	{
		directory = opendir(msh->path[i]);
		while (msh->path[i] && directory == NULL)
		{
			i++;
			directory = opendir(msh->path[i]);
		}
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

char	*add_path_in_command(t_master *msh, char *name, int path_index)
{
	char	*command;
	size_t	command_len;
	
	command_len = ft_strlen(msh->path[path_index]) + ft_strlen(name) + 2;
	command = malloc(sizeof(char) * command_len);
	if (command == NULL)
		return (NULL);
	ft_strlcpy(command, msh->path[path_index], command_len);
	ft_strlcat(command, "/", command_len);
	ft_strlcat(command, name, command_len);
	return (command);
}

int	exec_command(t_master *msh, char **arg)
{
	int		i;
	int		pid;
	char	*command;
	int		return_value;

	if (arg[0] == NULL || arg[0][0] == 32)
		return (-1);
	if (arg[0][0] == '.' || arg[0][0] == '/')
		command = ft_strdup(arg[0]);
	else
	{
		i = search_command(msh, arg);
		if (i == -1)
		{
			ft_printf("msh: command not found: %s\n", arg[0]);
			return (-1);
		}
		command = add_path_in_command(msh, arg[0], i);
	}
	tcsetattr(0, TCSANOW, &(msh->term->backup));
	if (!(pid = fork()))
		execve(command, arg, msh->envp);
	else
	{
		waitpid(pid, &return_value, 0);
		if (WIFEXITED(return_value))
            msh->return_value = WEXITSTATUS(return_value);
		free(command);
	}
	if (tcsetattr(0, TCSANOW, &msh->term->term) == -1)
		return (-1);
	return (0);
}