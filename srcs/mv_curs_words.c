/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv_curs_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 19:13:27 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/02 17:53:43 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** A word is defined by the function isalnum.
*/

/*
** Function to move cursor from word to word on the right.
*/

void	mv_curs_right_word(t_master *msh)
{
	int	i;

	if (msh->line_len == 0)
		return ;
	i = msh->curs_pos->curs_pos_rel;
	if (ft_isalnum(msh->line[i]) == 0)
	{
		while (msh->line[i] && ft_isalnum(msh->line[i]) == 0)
			i++;
	}
	else
	{
		while (msh->line[i] && ft_isalnum(msh->line[i]) != 0)
			i++;
		while (msh->line[i] && ft_isalnum(msh->line[i]) == 0)
			i++;
	}
	mv_curs_abs(msh, (i + msh->prompt_len) % msh->res_x, \
						(i + msh->prompt_len) / msh->res_x);
	set_curs_pos(msh, i + msh->prompt_len);
}

/*
** Function to move cursor from word to word on the left.
**
** The static function was created because otherwise the
** size of the function would exceed 25 lines (42 standard)
*/

static int	char_is_not_on_word(t_master *msh, int i)
{
	if (i > 0 && ft_isalnum(msh->line[i - 1]) == 0)
	{
		while (i > 0 && ft_isalnum(msh->line[i - 1]) == 0)
			i--;
		while (i > 0 && ft_isalnum(msh->line[i]) != 0)
			i--;
	}
	while (i > 0 && ft_isalnum(msh->line[i - 1]) != 0)
		i--;
	return (i);
}

void	mv_curs_left_word(t_master *msh)
{
	int	i;

	if (msh->line_len == 0)
		return ;
	i = msh->curs_pos->curs_pos_rel;
	if (ft_isalnum(msh->line[i]) == 0)
	{
		while (i > 0 && ft_isalnum(msh->line[i]) == 0)
			i--;
		while (i > 0 && ft_isalnum(msh->line[i - 1]) != 0)
			i--;
	}
	else
		i = char_is_not_on_word(msh, i);
	mv_curs_abs(msh, (i + msh->prompt_len) % msh->res_x, \
						(i + msh->prompt_len) / msh->res_x);
	set_curs_pos(msh, i + msh->prompt_len);
}
