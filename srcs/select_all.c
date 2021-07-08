/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 20:56:08 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/08 19:32:37 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** This function allows you to select and unselect the entire input line.
*/

static void	unselect_all(t_master *msh)
{
	mv_curs_home(msh);
	write(1, msh->line, msh->line_len);
	set_curs_pos(msh, msh->line_len + msh->prompt_len);
	set_alt_curs_pos(msh, msh->select->end, msh->curs_pos->curs_pos_abs);
	set_alt_curs_pos(msh, msh->select->begin, msh->curs_pos->curs_pos_abs);
}

void	select_all(t_master *msh)
{
	if (msh->select->end->curs_pos_abs == msh->line_len + msh->prompt_len && \
		msh->select->begin->curs_pos_rel == 0)
	{
		unselect_all(msh);
		return ;
	}
	mv_curs_home(msh);
	set_alt_curs_pos(msh, msh->select->begin, msh->curs_pos->curs_pos_abs);
	tputs(msh->term->standout_enter, 1, ft_putchar);
	write(1, msh->line, msh->line_len);
	tputs(msh->term->standout_leave, 1, ft_putchar);
	set_curs_pos(msh, msh->line_len + msh->prompt_len);
	set_alt_curs_pos(msh, msh->select->end, msh->curs_pos->curs_pos_abs);
}
