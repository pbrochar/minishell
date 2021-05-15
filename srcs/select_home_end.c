/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_home_end.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 19:54:09 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/15 20:15:21 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	select_home(t_master *msh)
{
	if (msh->select->end->curs_pos_abs >= msh->select->begin->curs_pos_abs &&\
		(msh->select->end->curs_pos_abs != msh->curs_pos->curs_pos_abs))
	{
		mv_curs_abs(msh, msh->select->begin->curs_pos_abs % msh->res_x,\
						msh->select->begin->curs_pos_abs / msh->res_x);
		write(1, &msh->line[msh->select->begin->curs_pos_rel],\
				msh->select->end->curs_pos_abs -\
				msh->select->begin->curs_pos_abs);
		mv_curs_abs(msh, msh->select->begin->curs_pos_abs % msh->res_x,\
						msh->select->begin->curs_pos_abs / msh->res_x);
		set_alt_curs_pos(msh, msh->select->end, msh->curs_pos->curs_pos_abs);
	}
	tputs(tgetstr("so", NULL), 1, ft_putchar);
	mv_curs_home(msh);
	write(1, msh->line, msh->select->begin->curs_pos_rel);
	set_curs_pos(msh, msh->select->begin->curs_pos_abs);
	mv_curs_home(msh);
	set_alt_curs_pos(msh, msh->select->end, msh->curs_pos->curs_pos_abs);
	tputs(tgetstr("se", NULL), 1, ft_putchar);
}

void	select_end(t_master *msh)
{
	if (msh->select->end->curs_pos_abs <= msh->select->begin->curs_pos_abs)
	{
		write(1, &msh->line[msh->select->end->curs_pos_rel],\
				msh->select->begin->curs_pos_abs -\
				msh->select->end->curs_pos_abs);
		set_curs_pos(msh, msh->select->begin->curs_pos_abs);
		set_alt_curs_pos(msh, msh->select->end, msh->curs_pos->curs_pos_abs);
	}
	tputs(tgetstr("so", NULL), 1, ft_putchar);
	write(1, &msh->line[msh->curs_pos->curs_pos_rel],\
			msh->line_len - msh->curs_pos->curs_pos_rel);
	set_curs_pos(msh, msh->line_len + msh->prompt_len);
	set_alt_curs_pos(msh, msh->select->end, msh->curs_pos->curs_pos_abs);
	tputs(tgetstr("se", NULL), 1, ft_putchar);
}
