/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_wait_pid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 14:05:18 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/07 14:38:12 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_wait_pid(t_master *msh)
{
	int	return_value;

	waitpid(msh->pid, &return_value, 0);
	if (WIFEXITED(return_value))
	{
		msh->return_value = WEXITSTATUS(return_value);
		if (msh->return_value_char != NULL)
			free(msh->return_value_char);
		msh->return_value_char = ft_itoa(msh->return_value);
	}
}