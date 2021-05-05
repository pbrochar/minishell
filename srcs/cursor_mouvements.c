/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_mouvements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 21:12:22 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/05 14:52:08 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** curs_pos is an int and represents the position of the cursor
** in the line.
**
** curs_pos is a RELATIVE position : 0 represents the first character
** after the prompt.
**
** We assume here that the char *line is the exact copy of the
** display on stdout.
*/

/*
** Function to move the cursor one char to the left.
*/

void	mv_curs_left(t_master *msh)
{
	if (msh->curs_pos > 0)
	{
		tputs(msh->term->mv_left, 1, ft_putchar);
		msh->curs_pos--;
	}
}

/*
** Function to move the cursor one char to the right.
*/

void	mv_curs_right(t_master *msh)
{
	if (msh->curs_pos < msh->line_len)
	{
		tputs(msh->term->mv_right, 1, ft_putchar);
		msh->curs_pos++;
	}
}

/*
** Function to move the cursor to the beginning of the line.
*/

void	mv_curs_home(t_master *msh)
{
	tputs(msh->term->inv_curs, 1, ft_putchar);
	while (msh->curs_pos != 0)
		mv_curs_left(msh);
	tputs(msh->term->vis_curs, 1, ft_putchar);
}

/*
** Function to move the cursor to the end of the line.
*/

void	mv_curs_end(t_master *msh)
{
	tputs(msh->term->inv_curs, 1, ft_putchar);
	while (msh->curs_pos < msh->line_len)
		mv_curs_right(msh);
	tputs(msh->term->vis_curs, 1, ft_putchar);
}

/*
** Function to move cursor from word to word on the right.
*/

void	mv_curs_right_word(t_master *msh)
{
	tputs(msh->term->inv_curs, 1, ft_putchar);
	if (ft_isalnum(msh->line[msh->curs_pos]) == 0)
	{
		while (msh->line[msh->curs_pos] && \
				ft_isalnum(msh->line[msh->curs_pos]) == 0)
			mv_curs_right(msh);
	}
	else
	{
		while (msh->line[msh->curs_pos] && \
				ft_isalnum(msh->line[msh->curs_pos]) != 0)
			mv_curs_right(msh);
		while (msh->line[msh->curs_pos] && \
				ft_isalnum(msh->line[msh->curs_pos]) == 0)
			mv_curs_right(msh);
	}
	tputs(msh->term->vis_curs, 1, ft_putchar);
}

/*
** Function to move cursor from word to word on the left.
*/

void	mv_curs_left_word(t_master *msh)
{
	tputs(msh->term->inv_curs, 1, ft_putchar);
	if (ft_isalnum(msh->line[msh->curs_pos]) == 0)
	{
		while (msh->curs_pos > 0 && ft_isalnum(msh->line[msh->curs_pos]) == 0)
			mv_curs_left(msh);
		while (msh->curs_pos > 0 && \
				ft_isalnum(msh->line[msh->curs_pos - 1]) != 0)
			mv_curs_left(msh);
	}
	else
	{
		if (msh->curs_pos > 0 && ft_isalnum(msh->line[msh->curs_pos - 1]) == 0)
		{
			while (msh->curs_pos > 0 && \
					ft_isalnum(msh->line[msh->curs_pos - 1]) == 0)
				mv_curs_left(msh);
			while (msh->curs_pos > 0 && \
					ft_isalnum(msh->line[msh->curs_pos]) != 0)
				mv_curs_left(msh);
		}
		while (msh->curs_pos > 0 && \
				ft_isalnum(msh->line[msh->curs_pos - 1]) != 0)
			mv_curs_left(msh);
	}
	tputs(msh->term->vis_curs, 1, ft_putchar);
}
