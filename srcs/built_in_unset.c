/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 11:50:42 by pbrochar          #+#    #+#             */
/*   Updated: 2021/09/18 16:35:54 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**fill_new_env(t_master *msh, int index, char **new_env)
{
	int	i;

	i = 0;
	while (i < index)
	{
		new_env[i] = ft_strdup(msh->envp[i]);
		i++;
	}
	while (msh->envp[i + 1])
	{
		new_env[i] = ft_strdup(msh->envp[i + 1]);
		i++;
	}
	i = 0;
	while (msh->envp[i])
	{
		free(msh->envp[i]);
		i++;
	}
	free(msh->envp);
	return (new_env);
}

static int	realloc_env(t_master *msh, int index)
{
	char	**new_env;
	int		i;
	int		size;

	i = 0;
	while (msh->envp[i])
		i++;
	size = i;
	new_env = malloc(sizeof(char *) * size);
	if (new_env == NULL)
		return (-1);
	new_env[size - 1] = NULL;
	new_env = fill_new_env(msh, index, new_env);
	msh->envp = new_env;
	return (0);
}

static int	check_format(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
		return (-1);
	while (var[i])
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (-1);
		i++;
	}
	return (0);
}

static int	check_error(int ret, char *str, t_master *msh, int *final_ret)
{
	if (ret == -1)
	{
		print_err_bad_identifier(str);
		ret_value(msh, 1);
		(*final_ret) = 1;
		return (0);
	}
	return (1);
}

int	built_in_unset(t_master *msh, char **arg)
{
	t_unset	var;

	var.i = 0;
	var.ret = 0;
	var.final_ret = 0;
	while (arg[++var.i])
	{
		var.ret = check_format(arg[var.i]);
		if (check_error(var.ret, arg[var.i], msh, &var.final_ret) == 0)
			continue ;
		var.env_index = -1;
		var.size = ft_strlen(arg[var.i]);
		while (msh->envp[++var.env_index])
		{
			if (ft_strncmp(msh->envp[var.env_index], arg[var.i], \
				var.size) == 0 && msh->envp[var.env_index][var.size] == '=')
			{
				realloc_env(msh, var.env_index);
				break ;
			}
		}
	}
	if (var.ret != -1 && var.final_ret == 0)
		ret_value(msh, 0);
	return (0);
}
