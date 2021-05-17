/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_msh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 12:28:56 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/17 21:55:13 by pbrochar         ###   ########.fr       */
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
	(*key_terms)->key_term[A_CTRL_U_A] = ft_strdup(CTRL_UP_ARROW);
	(*key_terms)->key_term[A_CTRL_D_A] = ft_strdup(CTRL_DOWN_ARROW);
	(*key_terms)->key_term[A_CTRL_H_A] = ft_strdup(CTRL_HOME);
	(*key_terms)->key_term[A_INSERT_A] = ft_strdup(INSERT);
	(*key_terms)->key_term[A_KEY_PG_UP] = ft_strdup(PG_UP);
	(*key_terms)->key_term[A_KEY_PG_DW] = ft_strdup(PG_DOWN);
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
	(*key_terms)->key_fct[A_CTRL_U_A] = &mv_curs_up_multiline;
	(*key_terms)->key_fct[A_CTRL_D_A] = &mv_curs_down_multiline;
	(*key_terms)->key_fct[A_CTRL_H_A] = &select_mode;
	(*key_terms)->key_fct[A_INSERT_A] = &paste_clipboard;
	(*key_terms)->key_fct[A_KEY_PG_UP] = &manage_page_up;
	(*key_terms)->key_fct[A_KEY_PG_DW] = &manage_page_dw;
	(*key_terms)->key_fct[NB_KEY - 1] =	NULL;
	(*key_terms)->key_term_select_mode[S_KEY_LEFT] = tgetstr("kl", NULL);
	(*key_terms)->key_term_select_mode[S_KEY_RIGHT] = tgetstr("kr", NULL);
	(*key_terms)->key_term_select_mode[S_KEY_HOME] = tgetstr("kh", NULL);
	(*key_terms)->key_term_select_mode[S_KEY_END] = tgetstr("@7", NULL);
	(*key_terms)->key_term_select_mode[S_KEY_BACK] = tgetstr("kb", NULL);
	(*key_terms)->key_term_select_mode[S_CTRL_L_A] = ft_strdup(CTRL_LEFT_ARROW);
	(*key_terms)->key_term_select_mode[S_CTRL_R_A] = ft_strdup(CTRL_RIGHT_ARROW);
	(*key_terms)->key_term_select_mode[S_CTRL_H_A] = ft_strdup(CTRL_HOME);
	(*key_terms)->key_term_select_mode[S_KEY_C] = ft_strdup(KEY_C);
	(*key_terms)->key_term_select_mode[S_KEY_A] = ft_strdup(KEY_A);
	(*key_terms)->key_term_select_mode[S_KEY_X] = ft_strdup(KEY_X);
	(*key_terms)->key_term_select_mode[S_KEY_B] = ft_strdup(KEY_B);
	(*key_terms)->key_term_select_mode[S_KEY_P] = ft_strdup(KEY_P);
	(*key_terms)->key_term_select_mode[NB_KEY_SELECT - 1] = NULL;
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
	(*key_terms)->key_fct_select_mode[NB_KEY_SELECT - 1] =	NULL;
	(*key_terms)->delete_char = tgetstr("dc", NULL);
	(*key_terms)->clean_line = tgetstr("cd", NULL);
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
	(*term_conf)->term.c_lflag &= ~(ISIG);
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
							+ 5;
}

static	int	init_select_struct(t_master **msh)
{
	(*msh)->select->begin = malloc(sizeof(t_curs_pos));
	(*msh)->select->end = malloc(sizeof(t_curs_pos));
	if ((*msh)->select->begin == NULL || (*msh)->select->end == NULL)
		return (-1);
	(*msh)->select->is_select = 0;
	return (0);
}

void	init_buffer(t_master **msh_m)
{
	int i;

	i = 0;
	(*msh_m)->buffer = malloc(sizeof(char *) * NB_BUFFER);
	while (i < NB_BUFFER)
	{
		(*msh_m)->buffer[i] = malloc(sizeof(char *));
		if ((*msh_m)->buffer[i] == NULL)
			return ;
		(*msh_m)->buffer[i] = NULL;
		i++;
	}
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
	(*msh_m)->save_curs_pos = malloc(sizeof(t_curs_pos));
	if ((*msh_m)->save_curs_pos == NULL)
		return (-1);
	(*msh_m)->select = malloc(sizeof(t_select));
	if ((*msh_m)->select == NULL)
		return (-1);
	if (init_select_struct(msh_m) == -1)
		return (-1);
	(*msh_m)->curs_pos->curs_pos_rel = 0;
	(*msh_m)->nb_line = 0;
	(*msh_m)->curs_pos->curs_pos_abs = (*msh_m)->prompt_len;
	(*msh_m)->res_x = tgetnum("co");
	(*msh_m)->res_y = tgetnum("li");
	(*msh_m)->envp = envp;
	(*msh_m)->term = term_c;
	(*msh_m)->save_curs_pos->curs_pos_abs = -1;
	(*msh_m)->save_curs_pos->curs_pos_rel = -1;
	(*msh_m)->is_multiline = 0;
	(*msh_m)->curr_line = 0;
	(*msh_m)->commands = NULL;
	(*msh_m)->history = NULL;
	(*msh_m)->clipboard = NULL;
	(*msh_m)->buffer = malloc(sizeof(char *) * NB_BUFFER);
	init_buffer(msh_m);
	return (0);
}
