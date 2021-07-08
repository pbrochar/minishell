/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_opt_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 13:59:11 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/07 14:05:34 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
