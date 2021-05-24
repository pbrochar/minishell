/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv_curs_home_end.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 19:15:17 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/24 14:27:32 by pbrochar         ###   ########.fr       */
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
	msh->pos_in_line = msh->prompt_len;
}

/*
** Function to move the cursor to the end of the line.
*/

void	mv_curs_end(t_master *msh)
{
	mv_curs_abs(msh, msh->line_size[msh->nb_line - 1], msh->nb_line - 1);
	set_curs_pos(msh, msh->line_len + msh->prompt_len);
	msh->curr_line = msh->nb_line - 1;
	msh->pos_in_line = msh->line_size[msh->curr_line];
}
