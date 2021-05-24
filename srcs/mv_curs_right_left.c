/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv_curs_right_left.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 19:09:13 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/24 13:54:49 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** These functions allow to move the cursor of a char to the right
** or to the left.
**
** If the cursor is at the end of the graphic line (defined by res_x),
** then it is moved to the beginning of the next line.
**
** If the cursor is at the beginning of the graphic line
** (defined by abs % res_x), then it is moved to the end of the previous line.
*/

/*
** Function to move the cursor one char to the left.
*/

void	mv_curs_left(t_master *msh)
{
	if (msh->pos_in_line == 0)
		go_to_end_term_line(msh);
	else if (msh->curs_pos->curs_pos_rel > 0)
	{
		tputs(msh->term->mv_left, 1, ft_putchar);
		dec_curs_pos(msh);
		msh->pos_in_line--;
	}
}

/*
** Function to move the cursor one char to the right.
*/

void	mv_curs_right(t_master *msh)
{
	if ((msh->pos_in_line == msh->res_x - 1) ||
		(msh->line[msh->curs_pos->curs_pos_rel] == '\n'))
		go_to_start_term_line(msh);
	else if (msh->curs_pos->curs_pos_rel < msh->line_len)
	{
		tputs(msh->term->mv_right, 1, ft_putchar);
		inc_curs_pos(msh);
		msh->pos_in_line++;
	}
}

/*
** Function that moves the cursor to the last char of the previous line.
*/

void	go_to_end_term_line(t_master *msh)
{
	int i;

	i = msh->line_size[msh->curr_line - 1] - 1;
	mv_curs_abs(msh, i, msh->curr_line - 1);
	dec_curs_pos(msh);
	msh->curr_line--;
	msh->pos_in_line = msh->line_size[msh->curr_line] - 1;
}

/*
** Function that moves the cursor to the first char of the next line.
*/

void	go_to_start_term_line(t_master *msh)
{
	mv_curs_abs(msh, 0, msh->curr_line + 1);
	inc_curs_pos(msh);
	msh->curr_line++;
	msh->pos_in_line = 0;
}
