/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_pipe_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 13:59:11 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/11 19:03:13 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_parent_process(t_master *msh, int i, int pipe_count)
{
	manage_parent_fd(msh->old_fd, msh->new_fd, i, pipe_count);
	heredoc_pipe_parent(msh, msh->heredoc_fd);
	parent_wait_pid(msh);
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
