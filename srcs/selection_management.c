/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_management.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 14:45:01 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/17 19:02:39 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "colors.h"


void swap_select_curs(t_master *msh)
{
	t_curs_pos *temp;

	temp = msh->select->begin;
	msh->select->begin = msh->select->end;
	msh->select->end = temp;
}



int		key_is_term_select(t_master *msh, char *buf)
{
	int	i;

	i = 0;
	while (msh->term->key_term_select_mode[i])
	{
		if (ft_strncmp(buf, msh->term->key_term_select_mode[i], ft_strlen(buf)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	unselect_for_leave(t_master *msh)
{
	if (msh->select->begin->curs_pos_abs == -1 ||
		msh->select->end->curs_pos_abs == -1)
		return ;
	if (msh->select->begin->curs_pos_abs > msh->select->end->curs_pos_abs)
		swap_select_curs(msh);
	save_curs_pos(msh);
	mv_curs_abs(msh, msh->select->begin->curs_pos_abs % msh->res_x,\
		msh->select->begin->curs_pos_abs / msh->res_x);
	write(1, &msh->line[msh->select->begin->curs_pos_rel],\
		msh->select->end->curs_pos_abs - msh->select->begin->curs_pos_abs);
	set_curs_pos(msh, msh->select->end->curs_pos_abs);
	mv_curs_abs(msh, msh->save_curs_pos->curs_pos_abs % msh->res_x, \
			msh->save_curs_pos->curs_pos_abs / msh->res_x);
	rest_curs_pos(msh);
}

void	loop_selection(t_master *msh)
{
	int ret;
	int	key_term;
	char buf[51];
	
	set_alt_curs_pos(msh, msh->select->begin, msh->curs_pos->curs_pos_abs);
	set_alt_curs_pos(msh, msh->select->end, msh->curs_pos->curs_pos_abs);
	while ((ret = read(0, buf, 50)) > 0)
	{
		buf[ret] = '\0';
		if ((key_term = key_is_term_select(msh, buf)) != -1)
		{
			msh->term->key_fct_select_mode[key_term](msh);
			if (key_term == S_KEY_C || key_term == S_KEY_BACK || key_term == S_KEY_X ||\
				key_term == S_KEY_P || key_term == S_CTRL_H_A)
				break;
		}
		else
			return ;
		ft_bzero(buf, 50);
	}
}

void	print_mode(t_master *msh, char c, char *color)
{
	save_curs_pos(msh);
	mv_curs_abs(msh, msh->prompt_len - 3, 0);
	set_curs_pos(msh, msh->prompt_len - 3);
	write(1, color, ft_strlen(color));
	write(1, &c, 1);
	write(1, TEXT_NORMAL, 4);
	mv_curs_abs(msh, msh->save_curs_pos->curs_pos_abs % msh->res_x,\
				msh->save_curs_pos->curs_pos_abs / msh->res_x);
	rest_curs_pos(msh);
}

void	select_mode(t_master *msh)
{
	tputs(msh->term->inv_curs, 1, ft_putchar);
	msh->select->is_select = 1;
	print_mode(msh, 's', TEXT_RED);
	loop_selection(msh);
	leave_select_mode(msh);
}

void	leave_select_mode(t_master *msh)
{
	if (msh->line_len != 0)
		unselect_for_leave(msh);
	set_alt_curs_pos(msh, msh->select->begin, -1);
	set_alt_curs_pos(msh, msh->select->end, -1);
	msh->select->is_select = 0;
	print_mode(msh, 'n', TEXT_NORMAL);
	tputs(msh->term->vis_curs, 1, ft_putchar);
}

void	manage_page_up(t_master *msh)
{
	(void)msh;
	printf("pg up\n");
}

void	manage_page_dw(t_master *msh)
{
	(void)msh;
	printf("pg dw\n");
}