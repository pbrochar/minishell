/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_parent.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 19:21:00 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/11 19:29:46 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_heredoc_parent(t_master *msh, int fd_pipe[2])
{
	if (((t_command *)msh->commands->prev->content)->std_in_data != NULL)
	{
		write(fd_pipe[1], \
			((t_command *)msh->commands->prev->content)->std_in_data, \
			ft_strlen(((t_command *)msh->commands->prev->content) \
							->std_in_data));
		close(fd_pipe[0]);
		close(fd_pipe[1]);
	}
}

void	exec_manage_parent_process(t_master *msh, int fd_pipe[2], char *command)
{
	manage_heredoc_parent(msh, fd_pipe);
	parent_wait_pid(msh);
	msh->commmand_running = false;
	free(command);
}
