/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_browse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 10:38:55 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/02 18:08:31 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/*
** These functions allow you to navigate in the history towards
** the old (back) or more recent (front) lines.
**
** A pointer on the list allows to know during the navigation at which
** link you are located.
*/

static void	history_update_line_graphic(t_master *msh)
{
	write(1, msh->line, msh->line_len);
	set_curs_pos(msh, msh->line_len + msh->prompt_len);
	msh->nb_line = msh->curs_pos->curs_pos_abs / msh->res_x;
}

void	browse_history_back(t_master *msh)
{
	if (!msh->history)
		return ;
	clear_line_display(msh);
	free(msh->line);
	msh->line = ft_strdup(msh->pos_in_history->content);
	msh->line_len = ft_strlen(msh->line);
	if (msh->pos_in_history->next)
		msh->pos_in_history = msh->pos_in_history->next;
	history_update_line_graphic(msh);
}

void	browse_history_front(t_master *msh)
{
	if (!msh->history)
		return ;
	clear_line_display(msh);
	free(msh->line);
	if (msh->pos_in_history->prev)
		msh->pos_in_history = msh->pos_in_history->prev;
	else
	{
		msh->line = malloc(sizeof(char));
		if (msh->line == NULL)
			return ;
		msh->line_len = 1;
		return ;
	}
	msh->line = ft_strdup(msh->pos_in_history->content);
	msh->line_len = ft_strlen(msh->line);
	history_update_line_graphic(msh);
}
