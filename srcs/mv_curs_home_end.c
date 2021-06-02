/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv_curs_home_end.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 19:15:17 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/02 17:52:05 by pbrochar         ###   ########.fr       */
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
}

/*
** Function to move the cursor to the end of the line.
*/

void	mv_curs_end(t_master *msh)
{
	mv_curs_abs(msh, ((msh->line_len + msh->prompt_len) % msh->res_x), \
				msh->nb_line);
	set_curs_pos(msh, msh->line_len + msh->prompt_len);
}
