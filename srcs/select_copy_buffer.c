/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_copy_buffer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 18:36:22 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/04 18:28:36 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "colors.h"

/*
** The buffer function allows to copy the content of the selection into
** a buffer.
**
** There are 10 buffers (0 to 9).
** Buffers allow to save all or part of a line in order to be able to
** reuse them later.
**
** In this loop, the program waits for a number between 0 and 9 to know
** in which buffer to save the selection.
**
** If the selected buffer is already full, it will be updated and therefore
** the old record is LOST.
*/

void	buffer_select(t_master *msh)
{
	int		ret;
	char	buf[51];
	int		rang;

	print_mode(msh, 'b', TEXT_BLUE);
	ret = read(0, buf, 50);
	while (ret > 0)
	{
		buf[ret] = '\0';
		if (ft_isdigit(buf[0]))
		{
			rang = buf[0] - '0';
			copy_in_buffer(msh, rang);
			break ;
		}
		else
			break ;
		ret = read(0, buf, 50);
	}
	print_mode(msh, 's', TEXT_RED);
}

void	copy_in_buffer(t_master *msh, int rang)
{
	int	size;

	free(msh->buffer[rang]);
	if (msh->select->begin->curs_pos_abs == -1 || \
		msh->select->end->curs_pos_abs == -1)
		return ;
	if (msh->select->begin->curs_pos_abs > msh->select->end->curs_pos_abs)
		swap_select_curs(msh);
	size = msh->select->end->curs_pos_rel - \
			msh->select->begin->curs_pos_rel + 1;
	msh->buffer[rang] = malloc(sizeof(char) * (size + 1));
	if (msh->buffer[rang] == NULL)
		return ;
	ft_strlcpy(msh->buffer[rang], &msh->line[msh->select->begin->curs_pos_rel], \
				(size_t)size);
}
