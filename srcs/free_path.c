/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 17:32:14 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/05 17:32:35 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_path(t_master *msh)
{
	int	i;

	i = 0;
	while (msh->path[i])
	{
		free(msh->path[i]);
		i++;
	}
	free(msh->path);
}
