/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_front.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 20:27:42 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/08 20:58:23 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	manage_res_and_line(t_master *msh)
{
	if (msh->curs_pos->curs_pos_abs % (msh->res_x) == 0)
		write(1, "\n", 1);
	msh->nb_line = (msh->line_len + msh->prompt_len) / msh->res_x;
}

int	print_char_management(t_master *msh, char *buf)
{
	if (msh->curs_pos->curs_pos_rel < msh->line_len)
	{
		tputs(msh->term->ipt_mode, 1, ft_putchar);
		msh->line = ft_mem_exp(msh->line, sizeof(char) * msh->line_len, \
			sizeof(char) * msh->line_len + 2);
		add_in_line(msh, buf[0]);
		msh->line_len++;
		update_line_front(msh);
		write(1, buf, 1);
		tputs(msh->term->lve_ipt_mode, 1, ft_putchar);
		inc_curs_pos(msh);
	}
	else
	{
		write(1, buf, 1);
		msh->line = ft_mem_exp(msh->line, sizeof(char) * msh->line_len, \
			sizeof(char) * msh->line_len + 2);
		msh->line_len++;
		msh->line[msh->line_len - 1] = buf[0];
		msh->line[msh->line_len] = '\0';
		inc_curs_pos(msh);
	}
	manage_res_and_line(msh);
	return (0);
}

static void	update_line(t_master *msh)
{
	mv_curs_abs(msh, 0, msh->curs_pos->curs_pos_abs / msh->res_x);
	set_curs_pos(msh, msh->curs_pos->curs_pos_abs - \
				(msh->curs_pos->curs_pos_abs % msh->res_x));
	write(1, &msh->line[msh->curs_pos->curs_pos_rel], 1);
	tputs(msh->term->up_curs, 1, ft_putchar);
	set_curs_pos(msh, (msh->curs_pos->curs_pos_abs - msh->res_x) + 1);
}

void	update_line_front(t_master *msh)
{
	int	n;

	n = msh->nb_line - (msh->curs_pos->curs_pos_abs / msh->res_x);
	if (n == 0)
		return ;
	save_curs_pos(msh);
	mv_curs_end(msh);
	if (msh->curs_pos->curs_pos_abs % msh->res_x == 0)
	{
		tputs(msh->term->scroll_line_up, 1, ft_putchar);
		msh->nb_line++;
		n++;
	}
	while (n > 0)
	{
		update_line(msh);
		n--;
	}
	mv_curs_abs(msh, msh->save_curs_pos->curs_pos_abs % msh->res_x, \
				msh->save_curs_pos->curs_pos_abs / msh->res_x);
	rest_curs_pos(msh);
}

void	add_in_line(t_master *msh, char c)
{
	int	i;

	i = msh->line_len;
	while (i > msh->curs_pos->curs_pos_rel)
	{
		msh->line[i] = msh->line[i - 1];
		i--;
	}
	msh->line[msh->curs_pos->curs_pos_rel] = c;
	msh->line[msh->line_len + 1] = '\0';
}
