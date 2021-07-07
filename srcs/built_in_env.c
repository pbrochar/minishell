/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 19:30:03 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/07 14:50:17 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_in_env(t_master *msh, char **arg)
{
	int	i;

	(void)arg;
	i = 0;
	while (msh->envp[i])
	{
		ft_printf("%s\n", msh->envp[i]);
		i++;
	}
	ret_value(msh, 0);
	return (0);
}
