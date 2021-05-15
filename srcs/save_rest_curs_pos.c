/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_rest_curs_pos.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 19:44:43 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/15 20:14:06 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** These functions allow to save the value of the main cursor and to
** restore it.
**
** They are useful in cases where the cursor has to be moved to change the
** appearance of the terminal.
**
** The position is saved in a structure s_curs_pos.
**
** It is possible to save only one position.
**
** Restore position acts only on the VALUE of the main cursor and
** not its actual graphic position on the screen.
** To change its graphic position on the screen see mv_curs_abs and
** other mv functions.
*/

void		save_curs_pos(t_master *msh)
{
	msh->save_curs_pos->curs_pos_abs = msh->curs_pos->curs_pos_abs;
	msh->save_curs_pos->curs_pos_rel = msh->curs_pos->curs_pos_rel;
}

void		rest_curs_pos(t_master *msh)
{
	msh->curs_pos->curs_pos_abs = msh->save_curs_pos->curs_pos_abs;
	msh->curs_pos->curs_pos_rel = msh->save_curs_pos->curs_pos_rel;
}
