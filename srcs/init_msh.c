/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_msh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 12:28:56 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/08 19:44:19 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	init_term(t_term **term_conf)
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
	(*msh_m)->prompt_len = (*msh_m)->prompt->dir_len \
							+ (*msh_m)->prompt->user_len \
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
	int	i;

	i = 0;
	(*msh_m)->buffer = malloc(sizeof(char *) * NB_BUFFER);
	if ((*msh_m)->buffer == NULL)
		return ;
	while (i < NB_BUFFER)
	{
		(*msh_m)->buffer[i] = NULL;
		i++;
	}
}

static void	init_envp(t_master **msh, char **env)
{
	int	i;
	int	size;

	i = 0;
	while (env[i])
		i++;
	size = i + 1;
	(*msh)->envp = malloc(sizeof(char *) * size);
	if ((*msh)->envp == NULL)
		return ;
	i = 0;
	while (i < size - 1)
	{
		(*msh)->envp[i] = ft_strdup(env[i]);
		i++;
	}
	(*msh)->envp[size - 1] = NULL;
}

static void	init_path(t_master **msh)
{
	int		i;
	char	*temp;

	i = 0;
	while (ft_strncmp((*msh)->envp[i], "PATH=", 5) != 0)
		i++;
	temp = ft_strchr((*msh)->envp[i], '=');
	i = 1;
	(*msh)->path = ft_split(&temp[i], ':');
}

static void	init_built_in(t_master **msh)
{
	(*msh)->built_in = malloc(sizeof(t_built_in));
	if ((*msh)->built_in == NULL)
		return ;
	(*msh)->built_in->built_in_list[0] = BI_CD;
	(*msh)->built_in->built_in_list[1] = BI_ECHO;
	(*msh)->built_in->built_in_list[2] = BI_ENV;
	(*msh)->built_in->built_in_list[3] = BI_EXIT;
	(*msh)->built_in->built_in_list[4] = BI_EXPORT;
	(*msh)->built_in->built_in_list[5] = BI_PWD;
	(*msh)->built_in->built_in_list[6] = BI_UNSET;
	(*msh)->built_in->built_in_list[7] = NULL;
	(*msh)->built_in->built_in_fct[0] = &built_in_cd;
	(*msh)->built_in->built_in_fct[1] = &built_in_echo;
	(*msh)->built_in->built_in_fct[2] = &built_in_env;
	(*msh)->built_in->built_in_fct[3] = &built_in_exit;
	(*msh)->built_in->built_in_fct[4] = &built_in_export;
	(*msh)->built_in->built_in_fct[5] = &built_in_pwd;
	(*msh)->built_in->built_in_fct[6] = &built_in_unset;
	(*msh)->built_in->built_in_fct[7] = NULL;
}

static void	init_operands(t_master **msh)
{
	(*msh)->operands[0] = SEMICOLON;
	(*msh)->operands[1] = PIPE;
	(*msh)->operands[2] = CHEVRON_RIGHT;
	(*msh)->operands[3] = DB_CHEVRON_RIGHT;
	(*msh)->operands[4] = CHEVRON_LEFT;
	(*msh)->operands[5] = DB_CHEVRON_LEFT;
	(*msh)->operands[6] = NULL;
}

static void	init_operands_fct(t_master **msh)
{
	(*msh)->ops_fct[0] = &semicolon_fct;
	(*msh)->ops_fct[1] = &pipe_fct;
	(*msh)->ops_fct[2] = &chevron_right_fct;
	(*msh)->ops_fct[3] = &db_chevron_right_fct;
	(*msh)->ops_fct[4] = &chevron_left_fct;
	(*msh)->ops_fct[5] = &db_chevron_left_fct;
	(*msh)->ops_fct[6] = NULL;
}

static void	init_main_struct(t_master **msh_m, char **envp, t_term *term_c)
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
	(*msh_m)->history = NULL;
	(*msh_m)->clipboard = NULL;
	(*msh_m)->return_value = 0;
	(*msh_m)->return_value_char = NULL;
	(*msh_m)->res_x = tgetnum("co");
	(*msh_m)->res_y = tgetnum("li");
}

static int	init_struct(t_master **msh_m)
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

int	init_msh_master_struct(t_master **msh_m, char **envp, t_term *term_c)
{
	if (init_struct(msh_m) == -1)
		return (-1);
	if (init_select_struct(msh_m) == -1)
		return (-1);
	init_prompt(msh_m);
	init_main_struct(msh_m, envp, term_c);
	init_envp(msh_m, envp);
	init_buffer(msh_m);
	init_path(msh_m);
	init_built_in(msh_m);
	init_operands(msh_m);
	init_operands_fct(msh_m);
	return (0);
}
