/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 11:39:18 by pbrochar          #+#    #+#             */
/*   Updated: 2021/09/11 15:59:20 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_format(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
		return (-1);
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '=' && var[i] != '_')
			return (-1);
		i++;
	}
	if (!var[i])
		return (-2);
	return (0);
}

static int	realloc_env(t_master *msh, char *new_var)
{
	int		i;
	int		size;
	char	**new_env;

	i = 0;
	while (msh->envp[i])
		i++;
	size = i + 2;
	new_env = malloc(sizeof(char *) * size);
	if (new_env == NULL)
		return (-1);
	i = 0;
	while (i < size - 2)
	{
		new_env[i] = ft_strdup(msh->envp[i]);
		free(msh->envp[i]);
		i++;
	}
	free(msh->envp);
	new_env[size - 2] = ft_strdup(new_var);
	new_env[size - 1] = NULL;
	msh->envp = new_env;
	return (0);
}

int	var_already_exist(t_master *msh, char *arg)
{
	int	var_name_size;
	int	i;

	i = 0;
	while (arg[i] != '=')
		i++;
	var_name_size = i;
	i = 0;
	while (msh->envp[i])
	{
		if (ft_strncmp(msh->envp[i], arg, var_name_size + 1) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	change_env_value(t_master *msh, char *arg, int index)
{
	free(msh->envp[index]);
	msh->envp[index] = ft_strdup(arg);
}

int	built_in_export(t_master *msh, char **arg)
{
	int	i;
	int	ret;

	i = 0;
	while (arg[++i])
	{
		ret = check_format(arg[i]);
		if (ret == -1)
		{
			print_err_bad_identifier(arg[i]);
			ret_value(msh, 1);
			continue ;
		}
		else if (ret == -2)
			continue ;
		ret = var_already_exist(msh, arg[i]);
		if (ret != -1)
			change_env_value(msh, arg[i], ret);
		else
			realloc_env(msh, arg[i]);
	}
	ret_value(msh, 0);
	return (0);
}
