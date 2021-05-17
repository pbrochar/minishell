/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_remove.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 10:35:51 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/17 18:03:53 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** These functions allow to delete the selection of the graphic line 
** and the line in memory.
**
*/

void	remove_select(t_master *msh)
{
	save_curs_pos(msh);
	if (msh->select->begin->curs_pos_abs > msh->select->end->curs_pos_abs)
	{
		swap_select_curs(msh);
		mv_curs_abs(msh, msh->select->end->curs_pos_abs % msh->res_x,\
					msh->select->end->curs_pos_abs / msh->res_x);
		set_curs_pos(msh, msh->select->end->curs_pos_abs);
	}
	delete_multi_display(msh);
}

void	delete_multi_display(t_master *msh)
{
	char	*temp;
	
	temp = remove_multi_char(msh);
	if (temp == NULL)
		return ;
	mv_curs_end(msh);
	while (msh->curs_pos->curs_pos_abs > msh->select->begin->curs_pos_abs)
	{
		mv_curs_left(msh);
		tputs(msh->term->delete_char, 1, ft_putchar);
	}
	msh->line_len = ft_strlen(temp);
	msh->nb_line = (msh->line_len + msh->prompt_len) / msh->res_x;
	free(msh->line);
	msh->line = temp;
	if (temp[0])
	{
		/*write(1, &msh->line[msh->select->begin->curs_pos_rel],\
			msh->line_len - msh->select->end->curs_pos_rel);*/
		ft_putstr_fd(&msh->line[msh->select->begin->curs_pos_rel], 1);
		sleep(1);
		set_curs_pos(msh, msh->curs_pos->curs_pos_abs + msh->line_len\
							- msh->select->end->curs_pos_rel);
		mv_curs_abs(msh, msh->save_curs_pos->curs_pos_abs % msh->res_x,\
		msh->save_curs_pos->curs_pos_abs / msh->res_x);
		rest_curs_pos(msh);
	}
	
}

char *remove_multi_char(t_master *msh)
{
	char 	*new;
	int		size;
	int 	len;
	int		i;

	i = 0;
	len = (msh->select->end->curs_pos_abs - msh->select->begin->curs_pos_abs);
	size = msh->line_len - len;
	new = malloc(sizeof(char) * (size + 1));
	if (new == NULL)
		return (NULL);
	new[size] = '\0';
	if (len == msh->line_len)
		return (new);
	while (i < msh->select->begin->curs_pos_rel)
	{
		new[i] = msh->line[i];
		i++;
	}
	i += len;
	while (msh->line[i])
	{
		new[i - len] = msh->line[i];
		i++;
	}
	return (new);
}
