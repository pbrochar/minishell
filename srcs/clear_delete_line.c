/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_delete_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 10:51:49 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/05 14:03:50 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*remove_elem(char *line, int pos)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * ((int)ft_strlen(line) - 1));
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

void		clear_line_display(t_master *msh)
{
	mv_curs_home(msh);
	tputs(msh->term->clean_line, 1, ft_putchar);
}

void		delete_key_display(t_master *msh)
{
	if (msh->curs_pos <= 0)
		return ;
	msh->line = remove_elem(msh->line, msh->curs_pos - 1);
	if (msh->line == NULL)
		return ;
	msh->line_len--;
	msh->curs_pos--;
	tputs(msh->term->mv_left, 1, ft_putchar);
	tputs(msh->term->delete_char, 1, ft_putchar);
}
