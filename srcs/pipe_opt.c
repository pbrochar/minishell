/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_opt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:02:50 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/06 17:51:16 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_command_pipe(t_master *msh, char **arg)
{
	int		i;
	char	*command;

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
	execve(command, arg, msh->envp);
	return (0);
}

void	execute_fct_pipe(t_master *msh, char **arg)
{
	int built_in_i;

	if (!arg)
		return ;
	built_in_i = is_built_in(msh, arg[0]);
	if (built_in_i != -1)
		msh->built_in->built_in_fct[built_in_i](msh, arg);
	else
		exec_command_pipe(msh, arg);
}

static int parse_pipes(t_master *msh)
{
	int		pipes;
	t_list	*temp;

	pipes = 1;
	temp = msh->commands;
	while (((t_command *)temp->content)->op[0] == '|')
	{
		temp = temp->next->next;
		pipes++;
	}
	return (pipes);
}

void	manage_child_fd(int i, int old_fd[2], int new_fd[2], int pipe_count)
{
	if (i > 0)
	{
		dup2(old_fd[0], STDIN_FILENO);
		close(old_fd[0]);
		close(old_fd[1]);
	}
	if (i < (pipe_count - 1))
	{
		close(new_fd[0]);
		dup2(new_fd[1], STDOUT_FILENO);
		close(new_fd[1]);
	}
}

void	manage_parent_fd(int old_fd[2], int new_fd[2], int i, int pipe_count)
{
	if (i > 0)
	{
		close(old_fd[0]);
		close(old_fd[1]);
	}
	if (i < (pipe_count - 1))
	{
		old_fd[0] = new_fd[0];
		old_fd[1] = new_fd[1];
	}
}

void	pipe_fct(t_master *msh)
{
	int	old_fd[2];
	int	new_fd[2];
	int	pid;
	int	i;
	int	pipe_count;
	
	pipe_count = parse_pipes(msh);
	i = 0;
	tcsetattr(0, TCSANOW, &(msh->term->backup));
	while (i < pipe_count)
	{
		if (i < (pipe_count - 1))
			pipe(new_fd);
		pid = fork();
		if (!pid)
		{
			manage_child_fd(i, old_fd, new_fd, pipe_count);
			execute_fct_pipe(msh, ((t_command *)msh->commands->prev->content)\
									->command_arg);
		}
		else
		{
			manage_parent_fd(old_fd, new_fd, i, pipe_count);
			waitpid(pid, NULL, 0);
			if (++i < pipe_count) 
				msh->commands = msh->commands->next->next;
		}
	}
	close(old_fd[0]);
	close(old_fd[1]);
	tcsetattr(0, TCSANOW, &msh->term->term);
}