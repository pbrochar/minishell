/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:12:26 by pbrochar          #+#    #+#             */
/*   Updated: 2021/09/18 16:12:37 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
