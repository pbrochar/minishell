/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 17:29:58 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/05 17:30:20 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_buffer(t_master *msh)
{
	int	i;

	i = 0;
	while (i < NB_BUFFER)
	{
		free(msh->buffer[i]);
		i++;
	}
	free(msh->buffer);
}
