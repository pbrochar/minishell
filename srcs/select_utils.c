/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:33:19 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/17 19:37:04 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** This function allows to reverse the beginning and the end of the selection.
**
** When entering the selection mode, begin is set to the current
** cursor position.
**
** Then end is incremented or decremented depending on the direction of
** the selection in relation to begin.
**
** To normalize the functions, if end is smaller than begin then they are
** exchanged before processing.
*/

void	swap_select_curs(t_master *msh)
{
	t_curs_pos *temp;

	temp = msh->select->begin;
	msh->select->begin = msh->select->end;
	msh->select->end = temp;
}
