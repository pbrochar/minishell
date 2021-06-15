/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 17:31:14 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/09 16:18:35 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_history(t_master *msh)
{
	t_list	*temp;

	while (msh->history)
	{
		temp = msh->history;
		free(msh->history->content);
		msh->history = msh->history->next;
		free(temp);
	}
}
