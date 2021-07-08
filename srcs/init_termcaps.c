/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termcaps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 19:53:00 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/08 19:53:54 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
