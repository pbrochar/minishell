/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_delete_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 10:51:49 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/09 14:36:41 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** These functions are used to manage the 'backspace' event to remove a
** character from the graphic line and from the line in memory.
*/

static char	*remove_elem(char *line, int pos)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * ft_strlen(line));
	if (new == NULL)
		return (NULL);
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

void	clear_line_display(t_master *msh)
{
	mv_curs_home(msh);
	tputs(msh->term->clean_line, 1, ft_putchar);
}

void	manage_delete_multiline(t_master *msh)
{
	int	n;

	n = msh->nb_line - (msh->curs_pos->curs_pos_abs / msh->res_x);
	save_curs_pos(msh);
	while (n > 0)
	{
		mv_curs_abs(msh, msh->res_x - 1, \
					msh->curs_pos->curs_pos_abs / msh->res_x);
		set_curs_pos(msh, msh->curs_pos->curs_pos_abs
			- (msh->curs_pos->curs_pos_abs % msh->res_x)
			+ (msh->res_x - 1));
		write(1, &msh->line[msh->curs_pos->curs_pos_rel], 1);
		mv_curs_right(msh);
		tputs(msh->term->delete_char, 1, ft_putchar);
		n--;
	}
	mv_curs_abs(msh, msh->save_curs_pos->curs_pos_abs % msh->res_x,
		msh->save_curs_pos->curs_pos_abs / msh->res_x);
	rest_curs_pos(msh);
	msh->nb_line = (msh->line_len + msh->prompt_len) / msh->res_x;
}

void	delete_key_display(t_master *msh)
{
	if (msh->curs_pos->curs_pos_rel <= 0)
		return ;
	msh->line = remove_elem(msh->line, msh->curs_pos->curs_pos_rel - 1);
	if (msh->line == NULL)
		return ;
	msh->line_len--;
	mv_curs_left(msh);
	tputs(msh->term->delete_char, 1, ft_putchar);
	if (msh->nb_line != 0 && \
		msh->curs_pos->curs_pos_abs / msh->res_x != msh->nb_line)
	{
		tputs(msh->term->inv_curs, 1, ft_putchar);
		manage_delete_multiline(msh);
		tputs(msh->term->vis_curs, 1, ft_putchar);
	}
}
