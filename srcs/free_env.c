/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 17:30:39 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/05 17:30:58 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_master *msh)
{
	int	i;

	i = 0;
	while (msh->envp[i])
	{
		free(msh->envp[i]);
		i++;
	}
	free(msh->envp);
}
