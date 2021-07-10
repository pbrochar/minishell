/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 20:01:28 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/10 18:43:17 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_struct(t_master **msh_m)
{
	*msh_m = malloc(sizeof(t_master));
	if (*msh_m == NULL)
		return (-1);
	(*msh_m)->prompt = malloc(sizeof(t_prompt));
	if ((*msh_m)->prompt == NULL)
		return (-1);
	(*msh_m)->curs_pos = malloc(sizeof(t_curs_pos));
	if ((*msh_m)->curs_pos == NULL)
		return (-1);
	(*msh_m)->save_curs_pos = malloc(sizeof(t_curs_pos));
	if ((*msh_m)->save_curs_pos == NULL)
		return (-1);
	(*msh_m)->select = malloc(sizeof(t_select));
	if ((*msh_m)->select == NULL)
		return (-1);
	return (0);
}

int	init_main_struct(t_master **msh_m, char **envp, t_term *term_c)
{
	(*msh_m)->line = NULL;
	(*msh_m)->line_len = 0;
	(*msh_m)->curs_pos->curs_pos_rel = 0;
	(*msh_m)->nb_line = 0;
	(*msh_m)->curs_pos->curs_pos_abs = (*msh_m)->prompt_len;
	(*msh_m)->envp = envp;
	(*msh_m)->term = term_c;
	(*msh_m)->save_curs_pos->curs_pos_abs = -1;
	(*msh_m)->save_curs_pos->curs_pos_rel = -1;
	(*msh_m)->commands = NULL;
	(*msh_m)->save_commands_list = NULL;
	(*msh_m)->history = NULL;
	(*msh_m)->clipboard = NULL;
	(*msh_m)->return_value = 0;
	(*msh_m)->pid = -1;
	(*msh_m)->commmand_running = false;
	(*msh_m)->heredoc_running = false;
	(*msh_m)->sigint_signal = false;
	(*msh_m)->return_value_char = NULL;
	(*msh_m)->res_x = tgetnum("co");
	(*msh_m)->res_y = tgetnum("li");
	if ((*msh_m)->res_x == -1 || (*msh_m)->res_y == -1)
		return (-1);
	return (0);
}

int	init_select_struct(t_master **msh)
{
	(*msh)->select->begin = malloc(sizeof(t_curs_pos));
	(*msh)->select->end = malloc(sizeof(t_curs_pos));
	if ((*msh)->select->begin == NULL || (*msh)->select->end == NULL)
		return (-1);
	(*msh)->select->is_select = 0;
	return (0);
}
