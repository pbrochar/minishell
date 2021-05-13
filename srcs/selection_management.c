/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_management.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 14:45:01 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/13 11:14:27 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// a = select all
// c = copy
// x = cut
// p = paste
// arrow = select one 
// ctrl arrow = select word
// + ctrl_p = paste in general loop;

static void reset_selection(t_master *msh)
{
	int size;

	size = msh->select->end->curs_pos_rel - msh->select->begin->curs_pos_rel + 1;
	mv_curs_abs(msh, msh->select->begin->curs_pos_abs % msh->res_x,\
				msh->select->begin->curs_pos_abs / msh->res_x);
	write(1, &msh->line[msh->select->begin->curs_pos_rel], size);
	set_curs_pos(msh, msh->select->end->curs_pos_abs);
}

static	void swap_select_curs(t_master *msh)
{
	t_curs_pos *temp;

	temp = msh->select->begin;
	msh->select->begin = msh->select->end;
	msh->select->end = temp;
}
void	copy_select(t_master *msh)
{
	int size;
	
	if (msh->clipboard)
		free(msh->clipboard);
	if (msh->select->begin->curs_pos_abs == -1 ||
		msh->select->end->curs_pos_abs == -1)
		return ;
	if (msh->select->begin->curs_pos_abs > msh->select->end->curs_pos_abs)
		swap_select_curs(msh);
	size = msh->select->end->curs_pos_rel - msh->select->begin->curs_pos_rel + 1;
	msh->clipboard = malloc(sizeof(char) * (size + 1));
	if (msh->clipboard == NULL)
		return ;
	ft_strlcpy(msh->clipboard, &msh->line[msh->select->begin->curs_pos_rel], (size_t)size);
	reset_selection(msh);
}

void	select_all(t_master *msh)
{
	mv_curs_home(msh);
	set_alt_curs_pos(msh, msh->select->begin, msh->curs_pos->curs_pos_abs);
	tputs(tgetstr("so", NULL), 1, ft_putchar);
	write(1, msh->line, msh->line_len);
	tputs(tgetstr("se", NULL), 1, ft_putchar);
	set_curs_pos(msh, msh->line_len + msh->prompt_len);
	set_alt_curs_pos(msh, msh->select->end, msh->curs_pos->curs_pos_abs);
}

char *insert_clipboard_in_line(t_master *msh)
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
	ft_memcpy(&temp[i], msh->clipboard, ft_strlen(msh->clipboard));
	i += ft_strlen(msh->clipboard);
	ft_memcpy(&temp[i], &msh->line[msh->curs_pos->curs_pos_rel],\
				ft_strlen(&msh->line[msh->curs_pos->curs_pos_rel]));
	temp[msh->line_len] = '\0';
	free(msh->line);
	return (temp);
}

int		paste_char_management(t_master *msh, int clip_len)
{
	if (msh->curs_pos->curs_pos_rel < msh->line_len)
	{
		tputs(msh->term->ipt_mode, 1, ft_putchar);
		msh->line_len += clip_len + 1;
		msh->line = insert_clipboard_in_line(msh);
		write(1, msh->clipboard, clip_len);
		tputs(msh->term->lve_ipt_mode, 1, ft_putchar);
		set_curs_pos(msh, msh->curs_pos->curs_pos_abs + clip_len);
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
			if (key_term == S_KEY_C)
				break;
		}
		else
		{
			msh->select->is_select = 0;
			return ;
		}
		ft_bzero(buf, 50);
	}
}

void	select_mode(t_master *msh)
{
	tputs(msh->term->inv_curs, 1, ft_putchar);
	msh->select->is_select = 1;
	loop_selection(msh);
	tputs(msh->term->vis_curs, 1, ft_putchar);
}

void	select_left(t_master *msh)
{
	if (msh->select->end->curs_pos_abs <= msh->select->begin->curs_pos_abs)
		tputs(tgetstr("so", NULL), 1, ft_putchar);
	if ((msh->curs_pos->curs_pos_abs) % (msh->res_x) == 0
		&& msh->nb_line > 0)
	{
		write(1, &msh->line[msh->curs_pos->curs_pos_rel], 1);
		go_to_end_term_line(msh);
		set_alt_curs_pos(msh, msh->select->end, msh->curs_pos->curs_pos_abs);
	}
	else if (msh->curs_pos->curs_pos_rel > 0)
	{
		tputs(msh->term->mv_left, 1, ft_putchar);
		dec_curs_pos(msh);
		write(1, &msh->line[msh->curs_pos->curs_pos_rel], 1);
		tputs(msh->term->mv_left, 1, ft_putchar);
		set_alt_curs_pos(msh, msh->select->end, msh->curs_pos->curs_pos_abs);
	}
	if (msh->select->end->curs_pos_abs <= msh->select->begin->curs_pos_abs)
		tputs(tgetstr("se", NULL), 1, ft_putchar);
}

void	select_right(t_master *msh)
{
	if (msh->select->end->curs_pos_abs >= msh->select->begin->curs_pos_abs)
		tputs(tgetstr("so", NULL), 1, ft_putchar);
	if ((msh->curs_pos->curs_pos_abs + 1) % (msh->res_x) == 0)
	{
		write(1, &msh->line[msh->curs_pos->curs_pos_rel], 1);
		go_to_start_term_line(msh);
		set_alt_curs_pos(msh, msh->select->end, msh->curs_pos->curs_pos_abs);
	}
	else if (msh->curs_pos->curs_pos_rel < msh->line_len)
	{
		write(1, &msh->line[msh->curs_pos->curs_pos_rel], 1);
		inc_curs_pos(msh);
		set_alt_curs_pos(msh, msh->select->end, msh->curs_pos->curs_pos_abs);
	}
	if (msh->select->end->curs_pos_abs >= msh->select->begin->curs_pos_abs)
		tputs(tgetstr("se", NULL), 1, ft_putchar);
}

void	select_home(t_master *msh)
{
	if (msh->select->end->curs_pos_abs >= msh->select->begin->curs_pos_abs)
	{
		mv_curs_abs(msh, msh->select->begin->curs_pos_abs % msh->res_x,\
						msh->select->begin->curs_pos_abs / msh->res_x);
		write(1, &msh->line[msh->select->begin->curs_pos_rel],\
				msh->select->end->curs_pos_abs - msh->select->begin->curs_pos_abs);
		mv_curs_abs(msh, msh->select->begin->curs_pos_abs % msh->res_x,\
						msh->select->begin->curs_pos_abs / msh->res_x);
		set_alt_curs_pos(msh, msh->select->end, msh->curs_pos->curs_pos_abs);
	}
	tputs(tgetstr("so", NULL), 1, ft_putchar);
	mv_curs_home(msh);
	write(1, msh->line, msh->select->begin->curs_pos_rel);
	mv_curs_home(msh);
	set_alt_curs_pos(msh, msh->select->end, msh->curs_pos->curs_pos_abs);
	tputs(tgetstr("se", NULL), 1, ft_putchar);
}

void	select_end(t_master *msh)
{
	if (msh->select->end->curs_pos_abs <= msh->select->begin->curs_pos_abs)
	{
		write(1, &msh->line[msh->select->end->curs_pos_rel],\
				msh->select->begin->curs_pos_abs - msh->select->end->curs_pos_abs);
		set_curs_pos(msh, msh->select->begin->curs_pos_abs);
		set_alt_curs_pos(msh, msh->select->end, msh->curs_pos->curs_pos_abs);
	}
	tputs(tgetstr("so", NULL), 1, ft_putchar);
	write(1, &msh->line[msh->curs_pos->curs_pos_rel], msh->line_len - msh->curs_pos->curs_pos_rel);
	set_curs_pos(msh, msh->line_len + msh->prompt_len);
	set_alt_curs_pos(msh, msh->select->end, msh->curs_pos->curs_pos_abs);
	tputs(tgetstr("se", NULL), 1, ft_putchar);
}

void	remove_select(t_master *msh)
{
	(void)msh;
	printf("coucou remove\n");
}

void	select_word_left(t_master *msh)
{
	if (msh->select->end->curs_pos_rel == 0)
		return ;
	if (msh->select->end->curs_pos_abs > msh->select->begin->curs_pos_abs)
	{
		mv_curs_left_word(msh);
		write(1, &msh->line[msh->curs_pos->curs_pos_rel],\
			msh->select->end->curs_pos_abs - msh->curs_pos->curs_pos_abs);
		set_curs_pos(msh, msh->select->end->curs_pos_abs);
		mv_curs_left_word(msh);
		set_alt_curs_pos(msh, msh->select->end, msh->curs_pos->curs_pos_abs);
	}
	tputs(tgetstr("so", NULL), 1, ft_putchar);
	mv_curs_left_word(msh);
	set_alt_curs_pos(msh, msh->select->end, msh->curs_pos->curs_pos_abs);
	write(1, &msh->line[msh->select->end->curs_pos_rel], \
		msh->select->begin->curs_pos_rel - msh->select->end->curs_pos_rel);
	mv_curs_abs(msh, msh->select->end->curs_pos_abs % msh->res_x,\
				msh->select->end->curs_pos_abs / msh->res_x);
	set_curs_pos(msh, msh->select->end->curs_pos_abs);
	tputs(tgetstr("se", NULL), 1, ft_putchar);
}

void	select_word_right(t_master *msh)
{
	if (msh->select->end->curs_pos_rel == msh->line_len)
		return ;
	if (msh->select->end->curs_pos_abs < msh->select->begin->curs_pos_abs)
	{
		mv_curs_right_word(msh);
		set_alt_curs_pos(msh, msh->select->end, msh->curs_pos->curs_pos_abs);
		mv_curs_left_word(msh);
		write(1, &msh->line[msh->curs_pos->curs_pos_rel],\
			msh->select->end->curs_pos_abs - msh->curs_pos->curs_pos_abs);
		set_curs_pos(msh, msh->select->end->curs_pos_abs);
		return ;
	}
	tputs(tgetstr("so", NULL), 1, ft_putchar);
	mv_curs_right_word(msh);
	set_alt_curs_pos(msh, msh->select->end, msh->curs_pos->curs_pos_abs);
	mv_curs_abs(msh, msh->select->begin->curs_pos_abs % msh->res_x,\
				msh->select->begin->curs_pos_abs / msh->res_x);
	write(1, &msh->line[msh->select->begin->curs_pos_rel], \
		msh->select->end->curs_pos_rel - msh->select->begin->curs_pos_rel);
	set_curs_pos(msh, msh->select->end->curs_pos_abs);
	tputs(tgetstr("se", NULL), 1, ft_putchar);
}


void	cut_select(t_master *msh)
{
	(void)msh;
	printf("cut select\n");
}

void	buffer_select(t_master *msh)
{
	(void)msh;
	printf("buffer select\n");
}

void	paste_buff_select(t_master *msh)
{
	(void)msh;
	printf("paste buffer select\n");
}