/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 11:50:42 by pbrochar          #+#    #+#             */
/*   Updated: 2021/09/11 19:00:29 by pbrochar         ###   ########.fr       */
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

int	built_in_unset(t_master *msh, char **arg)
{
	int	i;
	int	env_index;
	int	size;
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
		env_index = 0;
		size = ft_strlen(arg[i]);
		while (msh->envp[env_index])
		{
			if (ft_strncmp(msh->envp[env_index], arg[i], \
				size) == 0 && msh->envp[env_index][size] == '=')
			{
				realloc_env(msh, env_index);
				break ;
			}
			env_index++;
		}
	}
	ret_value(msh, 0);
	return (0);
}
