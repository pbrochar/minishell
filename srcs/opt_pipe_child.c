/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_opt_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 13:58:22 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/07 14:01:30 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
