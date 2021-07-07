/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 10:58:21 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/07 13:29:21 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	manage_command(t_master *msh, char **arg, char **command)
{
	int	i;

	i = search_command(msh, arg);
	if (i == -1)
	{
		ft_printf("msh: command not found: %s\n", arg[0]);
		return (-1);
	}
	*command = add_path_in_command(msh, arg[0], i);
	return (0);
}

static void	parent_wait_pid(t_master *msh)
{
	int	return_value;

	waitpid(msh->pid, &return_value, 0);
	if (WIFEXITED(return_value))
		msh->return_value = WEXITSTATUS(return_value);
}

int	exec_command(t_master *msh, char **arg)
{
	int		ret;
	char	*command;

	if (arg[0] == NULL || arg[0][0] == 32)
		return (-1);
	if (arg[0][0] == '.' || arg[0][0] == '/')
		command = ft_strdup(arg[0]);
	else
	{
		ret = manage_command(msh, arg, &command);
		if (ret == -1)
			return (-1);
	}
	tcsetattr(0, TCSANOW, &(msh->term->backup));
	msh->pid = fork();
	if (!msh->pid)
		execve(command, arg, msh->envp);
	else
	{
		parent_wait_pid(msh);
		free(command);
	}
	if (tcsetattr(0, TCSANOW, &msh->term->term) == -1)
		return (-1);
	return (0);
}
