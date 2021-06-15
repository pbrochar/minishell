/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 17:29:58 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/09 16:08:11 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_buffer(t_master *msh)
{
	int	i;

	i = 0;
	while (i < NB_BUFFER)
	{
		if (msh->buffer[i])
			free(msh->buffer[i]);
		i++;
	}
	if (msh->buffer)
		free(msh->buffer);
}
