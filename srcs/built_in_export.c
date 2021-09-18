/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 11:39:18 by pbrochar          #+#    #+#             */
/*   Updated: 2021/09/18 16:12:24 by pbrochar         ###   ########.fr       */
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

static int	check_arg_value(char **arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (arg[i][0] != '\0')
			return (1);
		i++;
	}
	return (0);
}

static int	print_export_values(t_master *msh)
{
	int	i;

	i = -1;
	while (msh->envp[++i])
		ft_printf("declare -x %s\n", msh->envp[i]);
	ret_value(msh, 0);
	return (0);
}

int	built_in_export(t_master *msh, char **arg)
{
	int	i;
	int	ret;

	i = 0;
	if (check_arg_value(arg) == 0)
		return (print_export_values(msh));
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
