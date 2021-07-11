/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_child.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 19:20:22 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/11 20:43:03 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_heredoc_child(t_master *msh, int fd_pipe[2])
{
	if (((t_command *)msh->commands->prev->content)->std_in_data != NULL)
	{
		dup2(fd_pipe[0], STDIN_FILENO);
		close(fd_pipe[1]);
	}
}

void	exec_manage_child_process(t_master *msh, int fd_pipe[2], \
									char *command, char **arg)
{
	manage_heredoc_child(msh, fd_pipe);
	change_shlvl(msh);
	execve(command, arg, msh->envp);
}
