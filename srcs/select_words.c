/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 20:47:13 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/02 18:22:55 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** These functions allow to select by word (see mv_curs_words).
*/

static void	unselect_for_word_right(t_master *msh)
{
	mv_curs_right_word(msh);
	set_alt_curs_pos(msh, msh->select->end, msh->curs_pos->curs_pos_abs);
	mv_curs_left_word(msh);
	write(1, &msh->line[msh->curs_pos->curs_pos_rel], \
		msh->select->end->curs_pos_abs - msh->curs_pos->curs_pos_abs);
	set_curs_pos(msh, msh->select->end->curs_pos_abs);
}

void	select_word_right(t_master *msh)
{
	if (msh->select->end->curs_pos_rel == msh->line_len)
		return ;
	if (msh->select->end->curs_pos_abs < msh->select->begin->curs_pos_abs)
	{
		unselect_for_word_right(msh);
		return ;
	}
	tputs(tgetstr("so", NULL), 1, ft_putchar);
	mv_curs_right_word(msh);
	set_alt_curs_pos(msh, msh->select->end, msh->curs_pos->curs_pos_abs);
	mv_curs_abs(msh, msh->select->begin->curs_pos_abs % msh->res_x, \
				msh->select->begin->curs_pos_abs / msh->res_x);
	write(1, &msh->line[msh->select->begin->curs_pos_rel], \
		msh->select->end->curs_pos_rel - msh->select->begin->curs_pos_rel);
	set_curs_pos(msh, msh->select->end->curs_pos_abs);
	tputs(tgetstr("se", NULL), 1, ft_putchar);
}

static void	unselect_for_word_left(t_master *msh)
{
	mv_curs_left_word(msh);
	write(1, &msh->line[msh->curs_pos->curs_pos_rel], \
		msh->select->end->curs_pos_abs - msh->curs_pos->curs_pos_abs);
	set_curs_pos(msh, msh->select->end->curs_pos_abs);
	mv_curs_left_word(msh);
	set_alt_curs_pos(msh, msh->select->end, msh->curs_pos->curs_pos_abs);
}

void	select_word_left(t_master *msh)
{
	if (msh->select->end->curs_pos_rel == 0)
		return ;
	if (msh->select->end->curs_pos_abs > msh->select->begin->curs_pos_abs)
	{
		unselect_for_word_left(msh);
		return ;
	}
	tputs(tgetstr("so", NULL), 1, ft_putchar);
	mv_curs_left_word(msh);
	set_alt_curs_pos(msh, msh->select->end, msh->curs_pos->curs_pos_abs);
	write(1, &msh->line[msh->select->end->curs_pos_rel], \
		msh->select->begin->curs_pos_rel - msh->select->end->curs_pos_rel);
	set_curs_pos(msh, msh->curs_pos->curs_pos_abs + \
	(msh->select->begin->curs_pos_rel - msh->select->end->curs_pos_rel));
	mv_curs_abs(msh, msh->select->end->curs_pos_abs % msh->res_x, \
				msh->select->end->curs_pos_abs / msh->res_x);
	set_curs_pos(msh, msh->select->end->curs_pos_abs);
	tputs(tgetstr("se", NULL), 1, ft_putchar);
}
