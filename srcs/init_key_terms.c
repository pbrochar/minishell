/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_key_terms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 19:12:14 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/08 19:54:47 by pbrochar         ###   ########.fr       */
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
