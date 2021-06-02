/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 11:50:42 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/02 12:31:26 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int realloc_env(t_master *msh, int index)
{
	char **new_env;
	int i;
	int size;

	i = 0;
	while (msh->envp[i])
		i++;
	size = i;
	new_env = malloc(sizeof(char *) * size);
	i = 0;
	while (i < index)
	{
		new_env[i] = ft_strdup(msh->envp[i]);
		i++;
	}
	while (msh->envp[i])
	{
		new_env[i] = ft_strdup(msh->envp[i - 1]);
		i++;
	}
	new_env[size - 1] = NULL;
	return (0);
}
/*
int built_in_unset(t_master *msh, char **arg)
{
	int i;
	int env_index;

	i = 1;
	while (arg[i])
	{
		env_index = 0;
		while (msh->envp[env_index])
		{
			if (ft_strncmp(arg[i], msh->envp[env_index], ft_strlen(arg[i])) == 0)
			{
				
			}
		}
		
	}
}*/