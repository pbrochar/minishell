/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_delete_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 10:51:49 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/24 14:01:04 by pbrochar         ###   ########.fr       */
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

void		manage_delete_multiline(t_master *msh)
{
	int n;

	n = (msh->nb_line - 1) - msh->curr_line;
	save_curs_pos(msh);
	while (n > 0)
	{
		mv_curs_abs(msh, msh->line_size[msh->curr_line], msh->curr_line);
		set_curs_pos(msh, msh->curs_pos->curs_pos_abs\
							+ (msh->line_size[msh->curr_line]\
							- msh->pos_in_line));
		msh->pos_in_line = msh->line_size[msh->curr_line];
		if (msh->line[msh->curs_pos->curs_pos_rel] == '\n')
			break ;
		write(1, &msh->line[msh->curs_pos->curs_pos_rel], 1);
		msh->line_size[msh->curr_line]++;
		mv_curs_right(msh);
		tputs(msh->term->delete_char, 1, ft_putchar);
		msh->line_size[msh->curr_line]--;
		n--;
	}
	mv_curs_rel_pos(msh, msh->save_curs_pos->curs_pos_rel);
	rest_curs_pos(msh);
}

void		update_size_array(t_master *msh)
{
	int	*new;
	int i;

	new = malloc(sizeof(int) * msh->nb_line - 1);
	if (new == NULL)
		return ;
	i = 0;
	while (i <= msh->curr_line)
	{
		new[i] = msh->line_size[i];
		i++;
	}
	while (i < msh->nb_line - 1)
	{
		new[i] = msh->line_size[i + 1];
		i++;
	}
	free(msh->line_size);
	msh->line_size = new;
}

void		delete_key_display(t_master *msh)
{
	if (msh->curs_pos->curs_pos_rel <= 0)
		return ;
	mv_curs_left(msh);
	if (msh->line[msh->curs_pos->curs_pos_rel] == '\n')
	{
		save_curs_pos(msh);
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
		ft_putstr_fd(&msh->line[msh->curs_pos->curs_pos_rel + 1], 1);
		set_curs_pos(msh, msh->curs_pos->curs_pos_abs\
			+ ft_strlen(&msh->line[msh->curs_pos->curs_pos_rel + 1]));
		msh->line_size[msh->curr_line] += msh->line_size[msh->curr_line + 1];
		update_size_array(msh);
		msh->nb_line--;
		msh->curr_line = msh->nb_line - 1;
		mv_curs_rel_pos(msh, msh->save_curs_pos->curs_pos_rel);
		rest_curs_pos(msh);	
	}
	else
	{
		tputs(msh->term->delete_char, 1, ft_putchar);
		msh->line_size[msh->curr_line]--;
	}
	msh->line = remove_elem(msh->line, msh->curs_pos->curs_pos_rel + 1);
	if (msh->line == NULL)
		return ;
	msh->line_len--;
	if (msh->nb_line != 1 & msh->curr_line != msh->nb_line - 1 &&\
		msh->line_size[msh->curr_line] == msh->res_x - 1)
	{
		//tputs(msh->term->inv_curs, 1, ft_putchar);
		manage_delete_multiline(msh);
		//tputs(msh->term->vis_curs, 1, ft_putchar);
	}
	
}
