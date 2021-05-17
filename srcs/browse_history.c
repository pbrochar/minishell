/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   browse_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 10:38:55 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/17 17:50:15 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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
	write(1, msh->line, msh->line_len);
	set_curs_pos(msh, msh->line_len + msh->prompt_len);
	msh->nb_line = msh->curs_pos->curs_pos_abs / msh->res_x;
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
		if(msh->line == NULL)
			return ;
		msh->line_len = 1;
		return ;
	}
	msh->line = ft_strdup(msh->pos_in_history->content);
	msh->line_len = ft_strlen(msh->line);
	write(1, msh->line, msh->line_len);
	set_curs_pos(msh, msh->line_len + msh->prompt_len);
	msh->nb_line = msh->curs_pos->curs_pos_abs / msh->res_x;
}
