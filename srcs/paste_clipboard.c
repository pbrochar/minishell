/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paste_clipboard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:02:19 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/02 18:12:02 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** These functions allow to paste the clipboard content on the graphic line
** and to update the line in memory.
**
** insert_clipboard_in_line is a function to add the clipboard in the line if
** the insertion is done in another place than the end of the line.
** Otherwise ft_strcat is used.
*/

void	paste_clipboard(t_master *msh)
{
	int	clip_len;

	if (msh->clipboard == NULL)
		return ;
	clip_len = ft_strlen(msh->clipboard);
	paste_clipboard_management(msh, clip_len);
}

char	*insert_clipboard_in_line(t_master *msh)
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
	ft_memcpy(&temp[i], msh->clipboard, ft_strlen(msh->clipboard));
	i += ft_strlen(msh->clipboard);
	ft_memcpy(&temp[i], &msh->line[msh->curs_pos->curs_pos_rel], \
				ft_strlen(&msh->line[msh->curs_pos->curs_pos_rel]));
	temp[msh->line_len] = '\0';
	free(msh->line);
	return (temp);
}

int	paste_clipboard_management(t_master *msh, int clip_len)
{
	if (msh->curs_pos->curs_pos_rel < msh->line_len)
	{
		tputs(msh->term->ipt_mode, 1, ft_putchar);
		msh->line_len += clip_len + 1;
		msh->line = insert_clipboard_in_line(msh);
		tputs(tgetstr("cd", NULL), 1, ft_putchar);
		ft_putstr_fd(&msh->line[msh->curs_pos->curs_pos_rel], 1);
		set_curs_pos(msh, msh->line_len + msh->prompt_len);
		tputs(msh->term->lve_ipt_mode, 1, ft_putchar);
	}
	else
	{
		write(1, msh->clipboard, clip_len);
		msh->line = ft_mem_exp(msh->line, msh->line_len, \
								msh->line_len + clip_len + 1);
		ft_strcat(msh->line, msh->clipboard);
		msh->line[msh->line_len + clip_len] = '\0';
		msh->line_len += clip_len;
		set_curs_pos(msh, msh->curs_pos->curs_pos_abs + clip_len);
	}
	msh->nb_line = (msh->line_len + msh->prompt_len) / msh->res_x;
	return (0);
}
