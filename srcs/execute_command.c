/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 10:58:21 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/11 16:43:47 by pbrochar         ###   ########.fr       */
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

void	setup_fd(t_master *msh, int *old_stdout, int *old_stdin)
{
	if (((t_command *)msh->commands->prev->content)->std_out != STDOUT_FILENO)
	{
		*old_stdout = dup(STDOUT_FILENO);
		dup2(((t_command *)msh->commands->prev->content)->std_out, \
							STDOUT_FILENO);
	}
	if (((t_command *)msh->commands->prev->content)->std_in != STDIN_FILENO)
	{
		*old_stdin = dup(STDIN_FILENO);
		dup2(((t_command *)msh->commands->prev->content)->std_in, STDIN_FILENO);
	}
}

void	restore_fd(t_master *msh, int old_stdout, int old_stdin)
{
	if (((t_command *)msh->commands->prev->content)->std_out != STDOUT_FILENO)
	{
		dup2(old_stdout, STDOUT_FILENO);
		close(old_stdout);
		close(((t_command *)msh->commands->prev->content)->std_out);
	}
	if (((t_command *)msh->commands->prev->content)->std_in != STDIN_FILENO)
	{
		dup2(old_stdin, STDIN_FILENO);
		close(old_stdin);
		close(((t_command *)msh->commands->prev->content)->std_in);
	}
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
	{
		if (((t_command *)msh->commands->prev->content)->std_in_data != NULL)
		{
			dup2(fd_pipe[0], STDIN_FILENO);
			close(fd_pipe[1]);
		}
		execve(command, arg, msh->envp);
	}
	else
	{
		if (((t_command *)msh->commands->prev->content)->std_in_data != NULL)
		{
			write(fd_pipe[1], ((t_command *)msh->commands->prev->content)->std_in_data, ft_strlen(((t_command *)msh->commands->prev->content)->std_in_data));
			close(fd_pipe[0]);
			close(fd_pipe[1]);
		}
		parent_wait_pid(msh);
		msh->commmand_running = false;
		free(command);
	}
	if (tcsetattr(0, TCSANOW, &msh->term->term) == -1)
		return (-1);
	return (0);
}
