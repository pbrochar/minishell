/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv_curs_right_left.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 19:09:13 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/17 23:07:11 by pbrochar         ###   ########.fr       */
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
	if ((msh->curs_pos->curs_pos_abs % msh->res_x == 0 && msh->nb_line > 0) || 
		(msh->line[msh->curs_pos->curs_pos_rel - 1] == '\n'))
		go_to_end_term_line(msh);
	else if (msh->curs_pos->curs_pos_rel > 0)
	{
		tputs(msh->term->mv_left, 1, ft_putchar);
		dec_curs_pos(msh);
	}
}

/*
** Function to move the cursor one char to the right.
*/

void	mv_curs_right(t_master *msh)
{
	if (((msh->curs_pos->curs_pos_abs + 1) % (msh->res_x) == 0 ) ||
		(msh->line[msh->curs_pos->curs_pos_rel] == '\n'))
		go_to_start_term_line(msh);
	else if (msh->curs_pos->curs_pos_rel < msh->line_len)
	{
		tputs(msh->term->mv_right, 1, ft_putchar);
		inc_curs_pos(msh);
	}
}

/*
** Function that moves the cursor to the last char of the previous line.
*/

void	go_to_end_term_line(t_master *msh)
{
	int i;
	
	if (msh->line[msh->curs_pos->curs_pos_rel - 1] == '\n')
	{
		i = 1;
		while (msh->line[msh->curs_pos->curs_pos_rel - 1 - i] &&\
				msh->line[msh->curs_pos->curs_pos_rel - 1 - i] != '\n')
			i++;
		if (msh->curr_line == 1)
			i += msh->prompt_len;
		tputs(tgetstr("up", NULL), 1, ft_putchar);
		tputs(tgoto(tgetstr("ch", NULL), 0, i - 1), 1, ft_putchar);
		msh->curr_line--;
	}
	else
		mv_curs_abs(msh, msh->res_x - 1,\
			(msh->curs_pos->curs_pos_abs / msh->res_x) - 1);
	dec_curs_pos(msh);
	
}

/*
** Function that moves the cursor to the first char of the next line.
*/

void	go_to_start_term_line(t_master *msh)
{
	if (msh->line[msh->curs_pos->curs_pos_rel] == '\n')
	{
		tputs(tgetstr("sf", NULL), 1, ft_putchar);
		tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_putchar);
		msh->curr_line++;
	}
	else
		mv_curs_abs(msh, 0, (msh->curs_pos->curs_pos_abs / msh->res_x) + 1);
	inc_curs_pos(msh);
}
