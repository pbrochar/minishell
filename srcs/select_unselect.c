/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_unselect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:40:13 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/02 18:22:07 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unselect_for_leave(t_master *msh)
{
	if (msh->select->begin->curs_pos_abs == -1 || \
		msh->select->end->curs_pos_abs == -1)
		return ;
	if (msh->select->begin->curs_pos_abs > msh->select->end->curs_pos_abs)
		swap_select_curs(msh);
	save_curs_pos(msh);
	mv_curs_abs(msh, msh->select->begin->curs_pos_abs % msh->res_x, \
		msh->select->begin->curs_pos_abs / msh->res_x);
	write(1, &msh->line[msh->select->begin->curs_pos_rel], \
		msh->select->end->curs_pos_abs - msh->select->begin->curs_pos_abs);
	set_curs_pos(msh, msh->select->end->curs_pos_abs);
	mv_curs_abs(msh, msh->save_curs_pos->curs_pos_abs % msh->res_x, \
			msh->save_curs_pos->curs_pos_abs / msh->res_x);
	rest_curs_pos(msh);
}
