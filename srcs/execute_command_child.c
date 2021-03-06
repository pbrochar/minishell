/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_child.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 19:20:22 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/11 22:27:34 by pbrochar         ###   ########.fr       */
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
	int	errno;
	int	ret;

	errno = 0;
	manage_heredoc_child(msh, fd_pipe);
	change_shlvl(msh);
	ret = execve(command, arg, msh->envp);
	if (ret == -1)
	{
		ft_putstr_fd("msh: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		ret_value(msh, 126);
	}
}
