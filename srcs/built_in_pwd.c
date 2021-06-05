/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 20:27:11 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/05 13:40:30 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_in_pwd(t_master *msh, char **arg)
{
	int	i;
	int	j;

	(void)arg;
	i = 0;
	j = 0;
	while (msh->envp[i] && ft_strncmp(msh->envp[i], "PWD", 3))
		i++;
	while (msh->envp[i][j] != '=')
		j++;
	ft_printf("%s\n", &msh->envp[i][++j]);
	return (0);
}
