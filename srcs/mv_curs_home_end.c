/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv_curs_home_end.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 19:15:17 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/17 22:37:36 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Function to move the cursor to the beginning of the line.
*/

void	mv_curs_home(t_master *msh)
{
	mv_curs_abs(msh, msh->prompt_len, 0);
	reset_curs_pos(msh);
	msh->curr_line = 0;
}

/*
** Function to move the cursor to the end of the line.
*/

void	mv_curs_end(t_master *msh)
{
	int i;

	i = msh->line_len;
	if (msh->is_multiline == 1)
	{
		while (msh->line[i] != '\n')
			i--;
		if (i != 0)
			i = msh->line_len - i - 1;
	}
	else
		i = (msh->line_len + msh->prompt_len) % msh->res_x;
	mv_curs_abs(msh, i, msh->nb_line);
	set_curs_pos(msh, msh->line_len + msh->prompt_len);
	if (msh->is_multiline == 1)
		msh->curr_line = msh->nb_line;
}
