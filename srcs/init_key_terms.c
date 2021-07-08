/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_key_terms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 19:12:14 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/08 19:42:33 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_key_term(t_term **key_terms)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if ((*key_terms)->key_term[i] == NULL)
			return (-1);
		i++;
	}
	return (0);
}

static int	init_key(t_term **key_terms)
{
	if (tputs(tgetstr("ks", NULL), 1, ft_putchar) == -1)
		return (-1);
	(*key_terms)->key_term[A_KEY_LEFT] = tgetstr("kl", NULL);
	(*key_terms)->key_term[A_KEY_RIGHT] = tgetstr("kr", NULL);
	(*key_terms)->key_term[A_KEY_UP] = tgetstr("ku", NULL);
	(*key_terms)->key_term[A_KEY_DOWN] = tgetstr("kd", NULL);
	(*key_terms)->key_term[A_KEY_HOME] = tgetstr("kh", NULL);
	(*key_terms)->key_term[A_KEY_END] = tgetstr("@7", NULL);
	(*key_terms)->key_term[A_KEY_BACK] = tgetstr("kb", NULL);
	(*key_terms)->key_term[A_CTRL_L_A] = CTRL_LEFT_ARROW;
	(*key_terms)->key_term[A_CTRL_R_A] = CTRL_RIGHT_ARROW;
	(*key_terms)->key_term[A_CTRL_U_A] = CTRL_UP_ARROW;
	(*key_terms)->key_term[A_CTRL_D_A] = CTRL_DOWN_ARROW;
	(*key_terms)->key_term[A_CTRL_H_A] = CTRL_HOME;
	(*key_terms)->key_term[A_INSERT_A] = INSERT;
	(*key_terms)->key_term[NB_KEY - 1] = NULL;
	return (check_key_term(key_terms));
}

static void	init_key_fct(t_term **key_terms)
{
	(*key_terms)->key_fct[A_KEY_LEFT] = &mv_curs_left;
	(*key_terms)->key_fct[A_KEY_RIGHT] = &mv_curs_right;
	(*key_terms)->key_fct[A_KEY_UP] = &browse_history_back;
	(*key_terms)->key_fct[A_KEY_DOWN] = &browse_history_front;
	(*key_terms)->key_fct[A_KEY_HOME] = &mv_curs_home;
	(*key_terms)->key_fct[A_KEY_END] = &mv_curs_end;
	(*key_terms)->key_fct[A_KEY_BACK] = &delete_key_display;
	(*key_terms)->key_fct[A_CTRL_L_A] = &mv_curs_left_word;
	(*key_terms)->key_fct[A_CTRL_R_A] = &mv_curs_right_word;
	(*key_terms)->key_fct[A_CTRL_U_A] = &mv_curs_up_multiline;
	(*key_terms)->key_fct[A_CTRL_D_A] = &mv_curs_down_multiline;
	(*key_terms)->key_fct[A_CTRL_H_A] = &select_mode;
	(*key_terms)->key_fct[A_INSERT_A] = &paste_clipboard;
	(*key_terms)->key_fct[NB_KEY - 1] = NULL;
}

static int	init_key_term_select(t_term **key_terms)
{
	int	i;

	i = 0;
	(*key_terms)->key_term_select_mode[S_KEY_LEFT] = tgetstr("kl", NULL);
	(*key_terms)->key_term_select_mode[S_KEY_RIGHT] = tgetstr("kr", NULL);
	(*key_terms)->key_term_select_mode[S_KEY_HOME] = tgetstr("kh", NULL);
	(*key_terms)->key_term_select_mode[S_KEY_END] = tgetstr("@7", NULL);
	(*key_terms)->key_term_select_mode[S_KEY_BACK] = tgetstr("kb", NULL);
	(*key_terms)->key_term_select_mode[S_CTRL_L_A] = CTRL_LEFT_ARROW;
	(*key_terms)->key_term_select_mode[S_CTRL_R_A] = CTRL_RIGHT_ARROW;
	(*key_terms)->key_term_select_mode[S_CTRL_H_A] = CTRL_HOME;
	(*key_terms)->key_term_select_mode[S_KEY_C] = KEY_C;
	(*key_terms)->key_term_select_mode[S_KEY_A] = KEY_A;
	(*key_terms)->key_term_select_mode[S_KEY_X] = KEY_X;
	(*key_terms)->key_term_select_mode[S_KEY_B] = KEY_B;
	(*key_terms)->key_term_select_mode[S_KEY_P] = KEY_P;
	(*key_terms)->key_term_select_mode[NB_KEY_SELECT - 1] = NULL;
	while (i < 5)
	{
		if ((*key_terms)->key_term_select_mode[i] == NULL)
			return (-1);
		i++;
	}
	return (0);
}

void	init_key_fct_select(t_term **key_terms)
{
	(*key_terms)->key_fct_select_mode[S_KEY_LEFT] = &select_left;
	(*key_terms)->key_fct_select_mode[S_KEY_RIGHT] = &select_right;
	(*key_terms)->key_fct_select_mode[S_KEY_HOME] = &select_home;
	(*key_terms)->key_fct_select_mode[S_KEY_END] = &select_end;
	(*key_terms)->key_fct_select_mode[S_KEY_BACK] = &remove_select;
	(*key_terms)->key_fct_select_mode[S_CTRL_L_A] = &select_word_left;
	(*key_terms)->key_fct_select_mode[S_CTRL_R_A] = &select_word_right;
	(*key_terms)->key_fct_select_mode[S_CTRL_H_A] = &leave_select_mode;
	(*key_terms)->key_fct_select_mode[S_KEY_C] = &copy_select;
	(*key_terms)->key_fct_select_mode[S_KEY_A] = &select_all;
	(*key_terms)->key_fct_select_mode[S_KEY_X] = &cut_select;
	(*key_terms)->key_fct_select_mode[S_KEY_B] = &buffer_select;
	(*key_terms)->key_fct_select_mode[S_KEY_P] = &paste_buff_select;
	(*key_terms)->key_fct_select_mode[NB_KEY_SELECT - 1] = NULL;
}

static int	check_termcaps_value(t_term **key_terms)
{
	if ((*key_terms)->delete_char == NULL || \
		(*key_terms)->clean_line == NULL || \
		(*key_terms)->mv_left == NULL || \
		(*key_terms)->mv_right == NULL || \
		(*key_terms)->ipt_mode == NULL || \
		(*key_terms)->lve_ipt_mode == NULL || \
		(*key_terms)->inv_curs == NULL || \
		(*key_terms)->vis_curs == NULL || \
		(*key_terms)->standout_enter == NULL || \
		(*key_terms)->standout_leave == NULL || \
		(*key_terms)->up_curs == NULL || \
		(*key_terms)->scroll_line_up == NULL || \
		(*key_terms)->set_curs_on_line == NULL)
	{
		return (-1);
	}
	return (0);
}

int	init_termcaps_values(t_term **key_terms)
{
	(*key_terms)->delete_char = tgetstr("dc", NULL);
	(*key_terms)->clean_line = tgetstr("cd", NULL);
	(*key_terms)->mv_left = tgetstr("le", NULL);
	(*key_terms)->mv_right = tgetstr("nd", NULL);
	(*key_terms)->ipt_mode = tgetstr("im", NULL);
	(*key_terms)->lve_ipt_mode = tgetstr("ei", NULL);
	(*key_terms)->inv_curs = tgetstr("vi", NULL);
	(*key_terms)->vis_curs = tgetstr("ve", NULL);
	(*key_terms)->standout_enter = tgetstr("so", NULL);
	(*key_terms)->standout_leave = tgetstr("se", NULL);
	(*key_terms)->up_curs = tgetstr("up", NULL);
	(*key_terms)->scroll_line_up = tgetstr("sf", NULL);
	(*key_terms)->set_curs_on_line = tgetstr("ch", NULL);
	return (check_termcaps_value(key_terms));
}

int	init_key_terms(t_term **key_terms)
{
	if (init_key(key_terms) == -1)
		return (-1);
	init_key_fct(key_terms);
	if (init_key_term_select(key_terms) == -1)
		return (-1);
	init_key_fct_select(key_terms);
	if (init_termcaps_values(key_terms) == -1)
		return (-1);
	return (0);
}
