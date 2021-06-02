/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_right_left.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 20:37:47 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/02 18:21:35 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** These functions are used in the selection mode.
**
** These functions allow to select character by character from the right
** or from the left.
**
** If a character is already selected then it is unselected.
*/

static void	select_right_multiline_management(t_master *msh)
{
	write(1, &msh->line[msh->curs_pos->curs_pos_rel], 1);
	go_to_start_term_line(msh);
	set_alt_curs_pos(msh, msh->select->end, msh->curs_pos->curs_pos_abs);
}

void	select_right(t_master *msh)
{
	if (msh->select->end->curs_pos_abs >= msh->select->begin->curs_pos_abs)
		tputs(tgetstr("so", NULL), 1, ft_putchar);
	if ((msh->curs_pos->curs_pos_abs + 1) % (msh->res_x) == 0)
		select_right_multiline_management(msh);
	else if (msh->curs_pos->curs_pos_rel < msh->line_len)
	{
		write(1, &msh->line[msh->curs_pos->curs_pos_rel], 1);
		inc_curs_pos(msh);
		set_alt_curs_pos(msh, msh->select->end, msh->curs_pos->curs_pos_abs);
	}
	if (msh->select->end->curs_pos_abs >= msh->select->begin->curs_pos_abs)
		tputs(tgetstr("se", NULL), 1, ft_putchar);
}

static void	select_left_multiline_management(t_master *msh)
{
	go_to_end_term_line(msh);
	write(1, &msh->line[msh->curs_pos->curs_pos_rel], 1);
	set_alt_curs_pos(msh, msh->select->end, msh->curs_pos->curs_pos_abs);
}

void	select_left(t_master *msh)
{
	if (msh->select->end->curs_pos_abs <= msh->select->begin->curs_pos_abs)
		tputs(tgetstr("so", NULL), 1, ft_putchar);
	if ((msh->curs_pos->curs_pos_abs) % (msh->res_x) == 0
		&& msh->nb_line > 0)
		select_left_multiline_management(msh);
	else if (msh->curs_pos->curs_pos_rel > 0)
	{
		tputs(msh->term->mv_left, 1, ft_putchar);
		dec_curs_pos(msh);
		write(1, &msh->line[msh->curs_pos->curs_pos_rel], 1);
		tputs(msh->term->mv_left, 1, ft_putchar);
		set_alt_curs_pos(msh, msh->select->end, msh->curs_pos->curs_pos_abs);
	}
	if (msh->select->end->curs_pos_abs <= msh->select->begin->curs_pos_abs)
		tputs(tgetstr("se", NULL), 1, ft_putchar);
}
