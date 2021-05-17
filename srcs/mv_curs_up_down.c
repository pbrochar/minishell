/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv_curs_up_down.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 19:16:19 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/17 23:28:09 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** These functions are used to move the cursor up or down in the case
** of multilines.
** The cursor cannot go beyond the first and last line.
**
** In case of moving to the first line, if the top character belongs to the
** prompt then the cursor is put at the beginning of the line (rel = 0).
**
** In case of moving to the last line, if the bottom character is outside
** the line, then the cursor is put at the end of the line (rel = line_len).
*/

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
	if (msh->curs_pos->curs_pos_abs + msh->res_x < \
		msh->line_len + msh->prompt_len)
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
