/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_delete_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 10:51:49 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/11 18:27:58 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*remove_elem(char *line, int pos)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * ((int)ft_strlen(line)));
	if (new == NULL)
		return (NULL);
	ft_bzero(new, ft_strlen(line) - 1);
	while (i < pos)
	{
		new[i] = line[i];
		i++;
	}
	i++;
	while (line[i])
	{
		new[i - 1] = line[i];
		i++;
	}
	new[i - 1] = '\0';
	free(line);
	return (new);
}

void		clear_line_display(t_master *msh)
{
	mv_curs_home(msh);
	tputs(msh->term->clean_line, 1, ft_putchar);
}

void		mv_curs_abs(t_master *msh, int x, int y)
{
	int curr_line;
	
	curr_line = msh->curs_pos->curs_pos_abs / msh->res_x;
	if (x < 0)
		return ;
	if (y < 0 || y > msh->nb_line)
		return ;
	if (y < curr_line)
	{
		while (y < curr_line)
		{
			tputs(tgetstr("up", NULL), 1, ft_putchar);
			y++;
		}
	}
	if (y > curr_line)
	{
		while (y > curr_line)
		{
			tputs(tgetstr("do", NULL), 1, ft_putchar);
			y--;
		}
	}
	tputs(tgoto(tgetstr("ch", NULL), 0, x), 1, ft_putchar);
}

void		rest_curs_pos(t_master *msh)
{
	msh->curs_pos->curs_pos_abs = msh->save_curs_pos->curs_pos_abs;
	msh->curs_pos->curs_pos_rel = msh->save_curs_pos->curs_pos_rel;
}

void		save_curs_pos(t_master *msh)
{
	msh->save_curs_pos->curs_pos_abs = msh->curs_pos->curs_pos_abs;
	msh->save_curs_pos->curs_pos_rel = msh->curs_pos->curs_pos_rel;
}

void		delete_key_display(t_master *msh)
{
	int n;
	//printf("\n\n\nabs = %d\n, rel = %d\n", msh->curs_pos->curs_pos_abs, msh->curs_pos->curs_pos_rel);
	//printf("\n\n char = %c\n", msh->line[msh->curs_pos->curs_pos_rel]);
	if (msh->curs_pos->curs_pos_rel <= 0)
		return ;
	msh->line = remove_elem(msh->line, msh->curs_pos->curs_pos_rel - 1);
	if (msh->line == NULL)
		return ;
	msh->line_len--;
	mv_curs_left(msh);
	tputs(msh->term->delete_char, 1, ft_putchar);
	if (msh->nb_line != 0 && msh->curs_pos->curs_pos_abs / msh->res_x != msh->nb_line)
	{
		save_curs_pos(msh);
		n = msh->nb_line - (msh->curs_pos->curs_pos_abs / msh->res_x);
		tputs(msh->term->inv_curs, 1, ft_putchar);
		while (n > 0)
		{
			mv_curs_abs(msh, msh->res_x - 1, msh->curs_pos->curs_pos_abs / msh->res_x);
			set_curs_pos(msh, msh->curs_pos->curs_pos_abs - (msh->curs_pos->curs_pos_abs % msh->res_x)
						+ (msh->res_x - 1));
			//if (msh->line_len)
			write(1, &msh->line[msh->curs_pos->curs_pos_rel], 1);
			mv_curs_right(msh);
			tputs(msh->term->delete_char, 1, ft_putchar);
			n--;
		}
		mv_curs_abs(msh, msh->save_curs_pos->curs_pos_abs % msh->res_x, msh->save_curs_pos->curs_pos_abs / msh->res_x);
		rest_curs_pos(msh);
		msh->nb_line = (msh->line_len + msh->prompt_len) / msh->res_x;
	}
	tputs(msh->term->vis_curs, 1, ft_putchar);
}
