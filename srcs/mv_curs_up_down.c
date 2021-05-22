/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv_curs_up_down.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 19:16:19 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/22 12:05:32 by pbrochar         ###   ########.fr       */
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

static int	add_curs_pos(t_master *msh)
{
	int pos;
	int i;
	
	i = 0;
	pos = 0;
	while (i < msh->curr_line)
	{
	
		pos += msh->line_size[i];
		i++;
	}
	return (pos);
}

void	mv_curs_up_multiline(t_master *msh)
{
	int coef;
	
	if (msh->curr_line == 0)
		return ;
	coef = 0;
	if (msh->curr_line == 1)
		coef = msh->prompt_len;
	if (msh->pos_in_line >= msh->line_size[msh->curr_line - 1] - coef)
	{
		mv_curs_abs(msh, msh->line_size[msh->curr_line - 1] - 1,\
			msh->curr_line - 1);
		set_curs_pos(msh, add_curs_pos(msh) - 1);
		msh->pos_in_line = msh->line_size[msh->curr_line - 1];
	}
	else
	{
		mv_curs_abs(msh, msh->pos_in_line + coef, msh->curr_line - 1);
		set_curs_pos(msh, msh->curs_pos->curs_pos_abs - msh->pos_in_line\
					- (msh->line_size[msh->curr_line - 1] - msh->pos_in_line) + coef);
		msh->pos_in_line += coef;
	}
	msh->curr_line--;
}

void	mv_curs_down_multiline(t_master *msh)
{
	int coef;
	
	if (msh->curr_line == msh->nb_line - 1)
		return ;
	coef = 0;
	if (msh->curr_line == 0)
		coef = msh->prompt_len;
	if (msh->pos_in_line - coef >= msh->line_size[msh->curr_line + 1])
	{
		mv_curs_abs(msh, msh->line_size[msh->curr_line + 1],\
			msh->curr_line + 1);
		set_curs_pos(msh, add_curs_pos(msh) + msh->line_size[msh->curr_line]\
											+ msh->line_size[msh->curr_line + 1]);
		msh->pos_in_line = msh->line_size[msh->curr_line + 1];
	}
	else
	{
		mv_curs_abs(msh, msh->pos_in_line - coef, msh->curr_line + 1);
		set_curs_pos(msh, add_curs_pos(msh) + msh->line_size[msh->curr_line]\
											+ msh->pos_in_line);
		msh->pos_in_line += coef;
	}
	msh->curr_line++;
}
