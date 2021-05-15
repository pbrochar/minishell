/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_curs_pos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 19:32:58 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/15 20:13:34 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** The position of the cursors is defined in a structure s_curs_pos
** (see msh_structs.h).
**
** There are several possible positions: the main cursor position,
** the selection cursors (see select_mode), the save cursors (see save_curs).
**
** These functions are dedicated to the update of the cursor position.
** They will act on the main cursor or other position (alt).
*/

/*
** This function allows to increase the main cursor.
*/

void	inc_curs_pos(t_master *msh)
{
	msh->curs_pos->curs_pos_rel++;
	msh->curs_pos->curs_pos_abs++;
}

/*
** This function allows to decrement the main cursor.
*/

void	dec_curs_pos(t_master *msh)
{
	msh->curs_pos->curs_pos_rel--;
	msh->curs_pos->curs_pos_abs--;
}

/*
** This function allows to reset the cursor position.
** REL is then 0.
** ABS is then prompt_len.
*/

void	reset_curs_pos(t_master *msh)
{
	msh->curs_pos->curs_pos_rel = 0;
	msh->curs_pos->curs_pos_abs = msh->prompt_len;
}

/*
** This function sets the value of the main cursor to abs.
** REL is then calculated by ABS - prompt_len.
*/

void	set_curs_pos(t_master *msh, int abs)
{
	msh->curs_pos->curs_pos_abs = abs;
	msh->curs_pos->curs_pos_rel = msh->curs_pos->curs_pos_abs - msh->prompt_len;
}

/*
** This function allows to set the value of the cursor indicated
** by t_curs_pos *pos to the value abs.
*/

void	set_alt_curs_pos(t_master *msh, t_curs_pos *pos, int abs)
{
	pos->curs_pos_abs = abs;
	pos->curs_pos_rel = pos->curs_pos_abs - msh->prompt_len;
}
