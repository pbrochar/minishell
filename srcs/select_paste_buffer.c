/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_paste_buffer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 18:50:16 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/17 19:06:21 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "colors.h"

/*
** These functions allow to paste the content of a buffer in the graphic line
** and to update the line in memory.
**
** The paste_buffer_select function is a loop that waits for a number from
** 0 to 9 to know which buffer should be pasted.
**
** insert_buffer_in_line is a function to add the buffer in the line if
** the insertion is done in another place than the end of the line.
** Otherwise ft_strcat is used.
**
** If all or part of the line is selected before pasting, the content
** of the selection is removed.
*/

void	paste_buff_select(t_master *msh)
{
	int		ret;
	char	buf[51];
	int		rang;

	print_mode(msh, 'p', TEXT_YELLOW);
	while ((ret = read(0, buf, 50)) > 0)
	{
		buf[ret] = '\0';
		if (ft_isdigit(buf[0]))
		{
			rang = buf[0] - '0';
			paste_buffer(msh, rang);
			break ;
		}
		else
			break ;
	}
	print_mode(msh, 's', TEXT_RED);
}

void	paste_buffer(t_master *msh, int rang)
{
	if (msh->buffer[rang] == NULL)
		return ;
	if (msh->select->begin->curs_pos_abs != msh->select->end->curs_pos_abs)
		remove_select(msh);
	paste_buffer_management(msh, rang);
}

char	*insert_buffer_in_line(t_master *msh, int rang)
{
	int		i;
	char	*temp;

	i = 0;
	temp = malloc(sizeof(char) * (msh->line_len + 1));
	if (temp == NULL)
		return (NULL);
	ft_bzero(temp, msh->line_len);
	ft_memcpy(temp, msh->line, msh->curs_pos->curs_pos_rel);
	i += msh->curs_pos->curs_pos_rel;
	ft_memcpy(&temp[i], msh->buffer[rang], ft_strlen(msh->buffer[rang]));
	i += ft_strlen(msh->buffer[rang]);
	ft_memcpy(&temp[i], &msh->line[msh->curs_pos->curs_pos_rel],\
				ft_strlen(&msh->line[msh->curs_pos->curs_pos_rel]));
	temp[msh->line_len] = '\0';
	free(msh->line);
	return (temp);
}

int		paste_buffer_management(t_master *msh, int rang)
{
	int len;

	len = ft_strlen(msh->buffer[rang]);
	if (msh->curs_pos->curs_pos_rel < msh->line_len)
	{
		tputs(msh->term->ipt_mode, 1, ft_putchar);
		msh->line_len += len + 1;
		msh->line = insert_buffer_in_line(msh, rang);
		write(1, msh->buffer[rang], len);
		tputs(msh->term->lve_ipt_mode, 1, ft_putchar);
		set_curs_pos(msh, msh->curs_pos->curs_pos_abs + len);
	}
	else
	{
		write(1, msh->buffer[rang], len);
		msh->line = ft_mem_exp(msh->line, msh->line_len,\
								msh->line_len + len + 1);
		ft_strcat(msh->line, msh->buffer[rang]);
		msh->line[msh->line_len + len] = '\0';
		msh->line_len += len;
		set_curs_pos(msh, msh->curs_pos->curs_pos_abs + len);
	}
	msh->nb_line = (msh->line_len + msh->prompt_len) / msh->res_x;
	return (0);
}
