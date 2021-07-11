/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:02:50 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/11 16:35:19 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_pipes(t_master *msh)
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

static void	init_pipe_fct(t_master *msh, int *pipe_count, int *i)
{
	*pipe_count = parse_pipes(msh);
	*i = 0;
	tcsetattr(0, TCSANOW, &(msh->term->backup));
}

static void	rest_pipe_fct(t_master *msh, int old_fd[2])
{
	close(old_fd[0]);
	close(old_fd[1]);
	tcsetattr(0, TCSANOW, &msh->term->term);
}

static void	pipe_new_fd(int i, int pipe_count, int new_fd[2])
{
	if (i < (pipe_count - 1))
		pipe(new_fd);
}

void	pipe_fct(t_master *msh)
{
	int	old_fd[2];
	int	new_fd[2];
	int	i;
	int	pipe_count;

	init_pipe_fct(msh, &pipe_count, &i);
	while (i < pipe_count)
	{
		pipe_new_fd(i, pipe_count, new_fd);
		msh->commmand_running = true;
		if (ft_strcmp("cd", ((t_command *)msh->commands->prev->content)->command_arg[0]) == 0)
			execute_fct(msh, ((t_command *)msh->commands->prev->content)->command_arg);
		else
			msh->pid = fork();
		if (!msh->pid)
		{
			if (((t_command *)msh->commands->prev->content)->std_in_data != NULL)
			{
				dup2(old_fd[0], STDIN_FILENO);
				close(old_fd[1]);
			}
			else
				manage_child_fd(i, old_fd, new_fd, pipe_count);
			execute_fct_pipe(msh);
			exit(0);
		}
		else
		{
			manage_parent_fd(old_fd, new_fd, i, pipe_count);
			parent_wait_pid(msh);
			msh->commmand_running = false;
			if (++i < pipe_count)
				msh->commands = msh->commands->next->next;
		}
	}
	rest_pipe_fct(msh, old_fd);
}
