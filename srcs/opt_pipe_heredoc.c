/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_pipe_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 19:02:49 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/11 19:03:36 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_pipe_parent(t_master *msh, int heredoc_fd[2])
{
	if (((t_command *)msh->commands->prev->content)->std_in_data != NULL)
	{
		write(heredoc_fd[1], ((t_command *)msh->commands->prev->content) \
			->std_in_data, \
			ft_strlen(((t_command *)msh->commands->prev->content) \
			->std_in_data));
		close(heredoc_fd[0]);
		close(heredoc_fd[1]);
	}
}

void 	heredoc_pipe_child(t_master *msh, int heredoc_fd[2])
{
	if (((t_command *)msh->commands->prev->content)->std_in_data != NULL)
	{
		dup2(heredoc_fd[0], STDIN_FILENO);
		close(heredoc_fd[1]);
	}
}

void	pipe_heredoc(t_master *msh)
{
	if (((t_command *)msh->commands->prev->content)->std_in_data != NULL)
		pipe(msh->heredoc_fd);
}
