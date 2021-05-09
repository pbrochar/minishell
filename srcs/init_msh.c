/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_msh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 12:28:56 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/09 14:31:20 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		init_key_terms(t_term **key_terms)
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
	(*key_terms)->key_term[A_CTRL_L_A] = ft_strdup(CTRL_LEFT_ARROW);
	(*key_terms)->key_term[A_CTRL_R_A] = ft_strdup(CTRL_RIGHT_ARROW);
	(*key_terms)->key_term[NB_KEY - 1] = NULL;
	(*key_terms)->key_fct[A_KEY_LEFT] = &mv_curs_left;
	(*key_terms)->key_fct[A_KEY_RIGHT] = &mv_curs_right;
	(*key_terms)->key_fct[A_KEY_UP] = &browse_history_back;
	(*key_terms)->key_fct[A_KEY_DOWN] = &browse_history_front;
	(*key_terms)->key_fct[A_KEY_HOME] = &mv_curs_home;
	(*key_terms)->key_fct[A_KEY_END] = &mv_curs_end;
	(*key_terms)->key_fct[A_KEY_BACK] = &delete_key_display;
	(*key_terms)->key_fct[A_CTRL_L_A] = &mv_curs_left_word;
	(*key_terms)->key_fct[A_CTRL_R_A] = &mv_curs_right_word;
	(*key_terms)->key_fct[NB_KEY - 1] =	NULL;
	(*key_terms)->delete_char = tgetstr("dc", NULL);
	(*key_terms)->clean_line = tgetstr("ce", NULL);
	(*key_terms)->mv_left = tgetstr("le", NULL);
	(*key_terms)->mv_right = tgetstr("nd", NULL);
	(*key_terms)->ipt_mode = tgetstr("im", NULL);
	(*key_terms)->lve_ipt_mode = tgetstr("ei", NULL);
	(*key_terms)->inv_curs = tgetstr("vi", NULL);
	(*key_terms)->vis_curs = tgetstr("ve", NULL);
	return (0);
}

int		init_term(t_term **term_conf)
{
	*term_conf = malloc(sizeof(t_term));
	if (*term_conf == NULL)
		return (-1);
	if (tcgetattr(0, &((*term_conf)->term)) == -1)
		return (-1);
	if (tcgetattr(0, &((*term_conf)->backup)) == -1)
		return (-1);
	(*term_conf)->term.c_lflag &= ~(ECHO);
	(*term_conf)->term.c_lflag &= ~(ICANON);
	if (tcsetattr(0, TCSANOW, &((*term_conf)->term)) == -1)
		return (-1);
	if (tgetent(0, getenv("TERM")) == -1)
		return (-1);
	return (0);
}

void	init_prompt(t_master **msh_m)
{
	char	*dir;
	int		i;

	(*msh_m)->prompt->user = getenv("LOGNAME");
	dir = getenv("PWD");
	if (dir != NULL)
	{
		i = ft_strlen(dir) - 1;
		while (i != 0 && dir[i] != '/')
			i--;
		if (dir[i + 1] && dir[i] == '/')
			i++;
		(*msh_m)->prompt->dir = ft_strdup(&dir[i]);
	}
	else
		(*msh_m)->prompt->dir = NULL;
	(*msh_m)->prompt->user_len = ft_strlen((*msh_m)->prompt->user);
	(*msh_m)->prompt->dir_len = ft_strlen((*msh_m)->prompt->dir);
	(*msh_m)->prompt_len = (*msh_m)->prompt->dir_len
							+ (*msh_m)->prompt->user_len
							+ 2;
}

int		init_msh_master_struct(t_master **msh_m, char **envp, t_term *term_c)
{
	*msh_m = malloc(sizeof(t_master));
	if (*msh_m == NULL)
		return (-1);
	(*msh_m)->prompt = malloc(sizeof(t_prompt));
	if ((*msh_m)->prompt == NULL)
		return (-1);
	(*msh_m)->line_len = 0;
	init_prompt(msh_m);
	(*msh_m)->curs_pos = malloc(sizeof(t_curs_pos));
	if ((*msh_m)->curs_pos == NULL)
		return (-1);
	(*msh_m)->curs_pos->curs_pos_rel = 0;
	(*msh_m)->curs_pos->curs_pos_abs = (*msh_m)->prompt_len;
	(*msh_m)->res_x = tgetnum("co");
	(*msh_m)->envp = envp;
	(*msh_m)->term = term_c;
	(*msh_m)->commands = NULL;
	(*msh_m)->history = NULL;
	return (0);
}
