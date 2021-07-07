/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_opt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 17:02:50 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/07 14:00:47 by pbrochar         ###   ########.fr       */
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

void	pipe_fct(t_master *msh)
{
	int	old_fd[2];
	int	new_fd[2];
	int	i;
	int	pipe_count;

	init_pipe_fct(msh, &pipe_count, &i);
	while (i < pipe_count)
	{
		if (i < (pipe_count - 1))
			pipe(new_fd);
		msh->pid = fork();
		if (!msh->pid)
		{
			manage_child_fd(i, old_fd, new_fd, pipe_count);
			execute_fct_pipe(msh);
		}
		else
		{
			manage_parent_fd(old_fd, new_fd, i, pipe_count);
			parent_wait_pid(msh);
			if (++i < pipe_count)
				msh->commands = msh->commands->next->next;
		}
	}
	rest_pipe_fct(msh, old_fd);
}
