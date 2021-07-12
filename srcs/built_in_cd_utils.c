/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 14:59:24 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/12 15:45:18 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cd_home_not_set(t_master *msh)
{
	ft_putstr_fd("msh: cd: HOME not set\n", STDERR_FILENO);
	ret_value(msh, 1);
	return (NULL);
}

char	*cd_return_oldpwd(t_master *msh, char *arg)
{
	int	i;

	i = 0;
	while (msh->envp[i])
	{
		if (ft_strncmp(msh->envp[i], "OLDPWD", 6) == 0)
		{
			ft_printf("%s\n", &msh->envp[i][7]);
			return (&msh->envp[i][7]);
		}
		i++;
	}
	return (arg);
}

char	*cd_return_home(t_master *msh)
{
	int	i;

	i = 0;
	while (msh->envp[i])
	{
		if (ft_strncmp(msh->envp[i], "HOME=", 5) == 0)
			return (&msh->envp[i][5]);
		i++;
	}
	return (cd_home_not_set(msh));
}
