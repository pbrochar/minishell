/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 10:58:21 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/11 19:27:54 by pbrochar         ###   ########.fr       */
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

int	exec_command(t_master *msh, char **arg)
{
	int		ret;
	char	*command;
	int		fd_pipe[2];

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
	msh->commmand_running = true;
	if (((t_command *)msh->commands->prev->content)->std_in_data != NULL)
		pipe(fd_pipe);
	msh->pid = fork();
	if (!msh->pid)
		exec_manage_child_process(msh, fd_pipe, command, arg);
	else
		exec_manage_parent_process(msh, fd_pipe, command);
	return (tcsetattr(0, TCSANOW, &msh->term->term));
}
