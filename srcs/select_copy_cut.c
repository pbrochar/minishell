/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_copy_cut.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 18:23:57 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/02 17:56:58 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** These functions allow to copy or cut the selection on the line
** in the clipboard (internal to msh).
**
** The cut function is only a call to the copy function and
** the remove function (see select_remove).
**
** The function insert_clipboard_in_line is a function to
** add the content of the clipboard to the memory line.
*/

void	copy_select(t_master *msh)
{
	int	size;

	if (msh->clipboard)
		free(msh->clipboard);
	if (msh->select->begin->curs_pos_abs == -1 || \
		msh->select->end->curs_pos_abs == -1)
		return ;
	if (msh->select->begin->curs_pos_abs > msh->select->end->curs_pos_abs)
		swap_select_curs(msh);
	size = msh->select->end->curs_pos_rel - \
			msh->select->begin->curs_pos_rel + 1;
	msh->clipboard = malloc(sizeof(char) * (size + 1));
	if (msh->clipboard == NULL)
		return ;
	ft_strlcpy(msh->clipboard, &msh->line[msh->select->begin->curs_pos_rel], \
				(size_t)size);
}

void	cut_select(t_master *msh)
{
	copy_select(msh);
	remove_select(msh);
}
