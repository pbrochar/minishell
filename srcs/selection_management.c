/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_management.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 14:45:01 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/17 18:29:45 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "colors.h"


void swap_select_curs(t_master *msh)
{
	t_curs_pos *temp;

	temp = msh->select->begin;
	msh->select->begin = msh->select->end;
	msh->select->end = temp;
}

void	copy_in_buffer(t_master *msh, int rang)
{
	int size;
	
	if (msh->buffer[rang] != NULL)
		free(msh->buffer[rang]);
	if (msh->select->begin->curs_pos_abs == -1 ||
		msh->select->end->curs_pos_abs == -1)
		return ;
	if (msh->select->begin->curs_pos_abs > msh->select->end->curs_pos_abs)
		swap_select_curs(msh);
	size = msh->select->end->curs_pos_rel - msh->select->begin->curs_pos_rel + 1;
	msh->buffer[rang] = malloc(sizeof(char) * (size + 1));
	if (msh->buffer[rang] == NULL)
		return ;
	ft_strlcpy(msh->buffer[rang], &msh->line[msh->select->begin->curs_pos_rel], (size_t)size);
}

char *insert_buffer_in_line(t_master *msh, int rang)
{
	int i;
	char *temp;

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
		msh->line = ft_mem_exp(msh->line, msh->line_len, msh->line_len + len + 1);
		ft_strcat(msh->line, msh->buffer[rang]);
		msh->line[msh->line_len + len] = '\0';
		msh->line_len += len;
		set_curs_pos(msh, msh->curs_pos->curs_pos_abs + len);
	}
	msh->nb_line = (msh->line_len + msh->prompt_len) / msh->res_x;
	return (0);
}



int		paste_char_management(t_master *msh, int clip_len)
{
	int i;

	if (msh->curs_pos->curs_pos_rel < msh->line_len)
	{
		i = 0;
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
		msh->line = ft_mem_exp(msh->line, msh->line_len, msh->line_len + clip_len + 1);
		ft_strcat(msh->line, msh->clipboard);
		msh->line[msh->line_len + clip_len] = '\0';
		msh->line_len += clip_len;
		set_curs_pos(msh, msh->curs_pos->curs_pos_abs + clip_len);
	}
	msh->nb_line = (msh->line_len + msh->prompt_len) / msh->res_x;
	return (0);
}

void	paste_selection(t_master *msh)
{
	int	clip_len;
	
	if (msh->clipboard == NULL)
		return ;
	clip_len = ft_strlen(msh->clipboard);
	paste_char_management(msh, clip_len);
}

int		key_is_term_select(t_master *msh, char *buf)
{
	int	i;

	i = 0;
	while (msh->term->key_term_select_mode[i])
	{
		if (ft_strncmp(buf, msh->term->key_term_select_mode[i], ft_strlen(buf)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	unselect_for_leave(t_master *msh)
{
	if (msh->select->begin->curs_pos_abs == -1 ||
		msh->select->end->curs_pos_abs == -1)
		return ;
	if (msh->select->begin->curs_pos_abs > msh->select->end->curs_pos_abs)
		swap_select_curs(msh);
	save_curs_pos(msh);
	mv_curs_abs(msh, msh->select->begin->curs_pos_abs % msh->res_x,\
		msh->select->begin->curs_pos_abs / msh->res_x);
	write(1, &msh->line[msh->select->begin->curs_pos_rel],\
		msh->select->end->curs_pos_abs - msh->select->begin->curs_pos_abs);
	set_curs_pos(msh, msh->select->end->curs_pos_abs);
	mv_curs_abs(msh, msh->save_curs_pos->curs_pos_abs % msh->res_x, \
			msh->save_curs_pos->curs_pos_abs / msh->res_x);
	rest_curs_pos(msh);
}

void	loop_selection(t_master *msh)
{
	int ret;
	int	key_term;
	char buf[51];
	
	set_alt_curs_pos(msh, msh->select->begin, msh->curs_pos->curs_pos_abs);
	set_alt_curs_pos(msh, msh->select->end, msh->curs_pos->curs_pos_abs);
	while ((ret = read(0, buf, 50)) > 0)
	{
		buf[ret] = '\0';
		if ((key_term = key_is_term_select(msh, buf)) != -1)
		{
			msh->term->key_fct_select_mode[key_term](msh);
			if (key_term == S_KEY_C || key_term == S_KEY_BACK || key_term == S_KEY_X ||\
				key_term == S_KEY_P || key_term == S_CTRL_H_A)
				break;
		}
		else
			return ;
		ft_bzero(buf, 50);
	}
}

void	print_mode(t_master *msh, char c, char *color)
{
	save_curs_pos(msh);
	mv_curs_abs(msh, msh->prompt_len - 3, 0);
	set_curs_pos(msh, msh->prompt_len - 3);
	write(1, color, ft_strlen(color));
	write(1, &c, 1);
	write(1, TEXT_NORMAL, 4);
	mv_curs_abs(msh, msh->save_curs_pos->curs_pos_abs % msh->res_x,\
				msh->save_curs_pos->curs_pos_abs / msh->res_x);
	rest_curs_pos(msh);
}

void	select_mode(t_master *msh)
{
	tputs(msh->term->inv_curs, 1, ft_putchar);
	msh->select->is_select = 1;
	print_mode(msh, 's', TEXT_RED);
	loop_selection(msh);
	leave_select_mode(msh);
}

void	leave_select_mode(t_master *msh)
{
	if (msh->line_len != 0)
		unselect_for_leave(msh);
	set_alt_curs_pos(msh, msh->select->begin, -1);
	set_alt_curs_pos(msh, msh->select->end, -1);
	msh->select->is_select = 0;
	print_mode(msh, 'n', TEXT_NORMAL);
	tputs(msh->term->vis_curs, 1, ft_putchar);
}



void	buffer_select(t_master *msh)
{
	int ret;
	char buf[51];
	int rang;

	print_mode(msh, 'b', TEXT_BLUE);
	while ((ret = read(0, buf, 50)) > 0)
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
	}
	print_mode(msh, 'i', TEXT_RED);
}

void	paste_buffer(t_master *msh, int rang)
{
	if (msh->buffer[rang] == NULL)
		return ;
	if (msh->select->begin->curs_pos_abs != msh->select->end->curs_pos_abs)
		remove_select(msh);
	paste_buffer_management(msh, rang);
}

void	paste_buff_select(t_master *msh)
{
	int ret;
	char buf[51]; 
	int rang;

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
		else if (buf[0] == 'c')
		{
			paste_selection(msh);
			break ;
		}
		else
			break ;
	}
	print_mode(msh, 'i', TEXT_RED);
}

void	manage_page_up(t_master *msh)
{
	(void)msh;
	printf("pg up\n");
}

void	manage_page_dw(t_master *msh)
{
	(void)msh;
	printf("pg dw\n");
}