/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_in_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 15:05:34 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/06 22:09:17 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_value(char *env_var)
{
	int	i;

	i = 0;
	while (env_var[i] && env_var[i] != '=')
		i++;
	i++;
	if (!env_var[i])
		return (NULL);
	return (&env_var[i]);
}

char	*find_in_env(t_master *msh, char *var)
{
	int		i;
	int		size;
	char	buf[4096];

	i = 1;
	while (var[i] && ft_isalnum(var[i]))
		i++;
	ft_strlcpy(buf, &var[1], i);
	size = ft_strlen(buf);
	if (ft_strncmp(buf, "?", size) == 0)
		return (ft_itoa(msh->return_value)); //LEAKS
	i = 0;
	while (msh->envp[i])
	{
		if (ft_strncmp(buf, msh->envp[i], size) == 0 && \
			msh->envp[i][size] == '=')
			return (env_value(msh->envp[i]));
		i++;
	}
	return (NULL);
}
