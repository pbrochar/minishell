/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_pipe_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 13:58:22 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/11 19:04:17 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_child_process(t_master *msh, int i, int pipe_count)
{
	manage_child_fd(msh, i, pipe_count);
	heredoc_pipe_child(msh, msh->heredoc_fd);
	execute_fct_pipe(msh);
	exit(0);
}

void	manage_child_fd(t_master *msh, int i, int pipe_count)
{	
	if (i > 0 && ((t_command *)msh->commands->prev->content) \
					->std_in_data == NULL)
	{
		dup2(msh->old_fd[0], STDIN_FILENO);
		close(msh->old_fd[0]);
		close(msh->old_fd[1]);
	}
	if (i < (pipe_count - 1))
	{
		close(msh->new_fd[0]);
		dup2(msh->new_fd[1], STDOUT_FILENO);
		close(msh->new_fd[1]);
	}
}
