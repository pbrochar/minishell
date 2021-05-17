/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_mode_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 14:45:01 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/17 19:51:39 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "colors.h"

void	select_mode(t_master *msh)
{
	tputs(msh->term->inv_curs, 1, ft_putchar);
	msh->select->is_select = 1;
	set_alt_curs_pos(msh, msh->select->begin, msh->curs_pos->curs_pos_abs);
	set_alt_curs_pos(msh, msh->select->end, msh->curs_pos->curs_pos_abs);
	print_mode(msh, 's', TEXT_RED);
	select_loop(msh);
	leave_select_mode(msh);
}

void	select_loop(t_master *msh)
{
	int		ret;
	int		key_term;
	char	buf[51];

	while ((ret = read(0, buf, 50)) > 0)
	{
		buf[ret] = '\0';
		if ((key_term = key_is_term_select(msh, buf)) != -1)
		{
			msh->term->key_fct_select_mode[key_term](msh);
			if (key_term == S_KEY_C || key_term == S_KEY_BACK ||
				key_term == S_KEY_X || key_term == S_KEY_P ||
				key_term == S_CTRL_H_A)
				return ;
		}
		else
			return ;
		ft_bzero(buf, 50);
	}
}

int		key_is_term_select(t_master *msh, char *buf)
{
	int	i;

	i = 0;
	while (msh->term->key_term_select_mode[i])
	{
		if (ft_strncmp(buf, msh->term->key_term_select_mode[i],\
			ft_strlen(buf)) == 0)
			return (i);
		i++;
	}
	return (-1);
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
