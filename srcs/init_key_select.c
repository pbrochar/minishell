/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_key_select.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 19:54:17 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/08 19:55:10 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_key_term_select(t_term **key_terms)
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
