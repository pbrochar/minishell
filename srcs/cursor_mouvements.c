/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_mouvements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 21:12:22 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/15 14:15:39 by pbrochar         ###   ########.fr       */
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

void	go_to_end_term_line(t_master *msh)
{
	mv_curs_abs(msh, msh->res_x - 1, (msh->curs_pos->curs_pos_abs / msh->res_x) - 1);
	dec_curs_pos(msh);
}

void go_to_start_term_line(t_master *msh)
{
	mv_curs_abs(msh, 0, (msh->curs_pos->curs_pos_abs / msh->res_x) + 1);
	inc_curs_pos(msh);
}

/*
** Function to move the cursor one char to the left.
*/
void	mv_curs_left(t_master *msh)
{
	if ((msh->curs_pos->curs_pos_abs) % (msh->res_x) == 0
		&& msh->nb_line > 0)
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
	if ((msh->curs_pos->curs_pos_abs + 1) % (msh->res_x) == 0)
		go_to_start_term_line(msh);
	else if (msh->curs_pos->curs_pos_rel < msh->line_len)
	{
		tputs(msh->term->mv_right, 1, ft_putchar);
		inc_curs_pos(msh);
	}
}

/*
** Function to move the cursor to the beginning of the line.
*/

void	mv_curs_home(t_master *msh)
{
	mv_curs_abs(msh, msh->prompt_len, 0);
	reset_curs_pos(msh);
}

/*
** Function to move the cursor to the end of the line.
*/

void	mv_curs_end(t_master *msh)
{
	mv_curs_abs(msh, ((msh->line_len + msh->prompt_len) % msh->res_x), msh->nb_line);
	set_curs_pos(msh, msh->line_len + msh->prompt_len);
}

/*
** Function to move cursor from word to word on the right.
*/

void	mv_curs_right_word(t_master *msh)
{
	int	i;

	if (msh->line_len == 0)
		return ;
	i = msh->curs_pos->curs_pos_rel;
	if (ft_isalnum(msh->line[i]) == 0)
	{
		while (msh->line[i] && ft_isalnum(msh->line[i]) == 0)
			i++;
	}
	else
	{
		while (msh->line[i] && ft_isalnum(msh->line[i]) != 0)
			i++;
		while (msh->line[i] && ft_isalnum(msh->line[i]) == 0)
			i++;
	}
	mv_curs_abs(msh, (i + msh->prompt_len) % msh->res_x,\
						(i + msh->prompt_len) / msh->res_x);
	set_curs_pos(msh, i + msh->prompt_len);
}

/*
** Function to move cursor from word to word on the left.
*/

void	mv_curs_left_word(t_master *msh)
{
	int i;

	if (msh->line_len == 0)
		return ;
	i = msh->curs_pos->curs_pos_rel;
	if (ft_isalnum(msh->line[i]) == 0)
	{
		while (i > 0 && ft_isalnum(msh->line[i]) == 0)
			i--;
		while (i > 0 && ft_isalnum(msh->line[i - 1]) != 0)
			i--;
	}
	else
	{
		if (i > 0 && ft_isalnum(msh->line[i - 1]) == 0)
		{
			while (i > 0 && ft_isalnum(msh->line[i - 1]) == 0)
				i--;
			while (i > 0 && ft_isalnum(msh->line[i]) != 0)
				i--;
		}
		while (i > 0 && ft_isalnum(msh->line[i - 1]) != 0)
			i--;
	}
	mv_curs_abs(msh, (i + msh->prompt_len) % msh->res_x,\
						(i + msh->prompt_len) / msh->res_x);
	set_curs_pos(msh, i + msh->prompt_len);
}

void	mv_curs_up_multiline(t_master *msh)
{
	if (msh->nb_line == 0 ||\
		msh->curs_pos->curs_pos_abs / msh->res_x == 0)
		return ; 
	if (msh->curs_pos->curs_pos_abs - msh->res_x > msh->prompt_len)
	{
		mv_curs_abs(msh, msh->curs_pos->curs_pos_abs % msh->res_x,\
			(msh->curs_pos->curs_pos_abs / msh->res_x) - 1);
		set_curs_pos(msh, msh->curs_pos->curs_pos_abs - msh->res_x);
	}
	else
	{
		mv_curs_abs(msh, msh->prompt_len,\
			(msh->curs_pos->curs_pos_abs / msh->res_x) - 1);
		set_curs_pos(msh, msh->prompt_len);
	}
		
}

void	mv_curs_down_multiline(t_master *msh)
{
	if (msh->nb_line == 0 ||\
		msh->curs_pos->curs_pos_abs / msh->res_x == msh->nb_line)
		return ;
	if (msh->curs_pos->curs_pos_abs + msh->res_x < msh->line_len + msh->prompt_len)
	{
		mv_curs_abs(msh, msh->curs_pos->curs_pos_abs % msh->res_x,\
			(msh->curs_pos->curs_pos_abs / msh->res_x) + 1);
		set_curs_pos(msh, msh->curs_pos->curs_pos_abs + msh->res_x);
	}
	else
	{
		mv_curs_abs(msh, (msh->prompt_len + msh->line_len) % msh->res_x,\
			(msh->curs_pos->curs_pos_abs / msh->res_x) + 1);
		set_curs_pos(msh, msh->prompt_len + msh->line_len);
	}
}

