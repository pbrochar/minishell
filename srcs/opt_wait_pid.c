/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_wait_pid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 14:05:18 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/07 14:52:03 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_wait_pid(t_master *msh)
{
	int	return_value;

	waitpid(msh->pid, &return_value, 0);
	if (WIFEXITED(return_value))
		ret_value(msh, WEXITSTATUS(return_value));
}