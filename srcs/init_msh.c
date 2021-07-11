/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_msh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 12:28:56 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/11 20:42:20 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_shlvl(t_master *msh)
{
	int	i;
	int n;
	char	*new_shlvl;
	char	*sh_level;

	i = 0;
	while (msh->envp[i])
	{
		if (ft_strncmp(msh->envp[i], "SHLVL=", 6) == 0)
		{
			n = ft_atoi(&msh->envp[i][6]);
			new_shlvl = ft_strdup("SHLVL=");
			sh_level = ft_itoa(++n);
			new_shlvl = ft_mem_exp(new_shlvl, 6, 6 + ft_strlen(sh_level));
			ft_strcat(new_shlvl, sh_level);
			change_env_value(msh, new_shlvl, i);
			break ;
		}
		i++;
	}
}

void	init_prompt(t_master **msh_m)
{
	char	*dir;
	int		i;

	(*msh_m)->prompt->user = getenv("LOGNAME");
	if ((*msh_m)->prompt->user == NULL)
		(*msh_m)->prompt->user = ft_strdup(USER);
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

int	init_msh_master_struct(t_master **msh_m, char **envp, t_term *term_c)
{
	if (init_struct(msh_m) == -1)
		return (-1);
	if (init_select_struct(msh_m) == -1)
		return (-1);
	init_prompt(msh_m);
	if (init_main_struct(msh_m, envp, term_c) == -1)
		return (-1);
	init_envp(msh_m, envp);
	init_buffer(msh_m);
	(*msh_m)->path = NULL;
	init_built_in(msh_m);
	init_operands(msh_m);
	init_operands_fct(msh_m);
	return (0);
}
