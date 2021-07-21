/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 15:47:47 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/21 14:28:04 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_shlvl(t_master *msh)
{
	int		i;
	int		n;
	char	*new_shlvl;
	char	*sh_level;

	i = 0;
	while (msh->envp[i])
	{
		if (ft_strncmp(msh->envp[i], "SHLVL=", 6) == 0)
		{
			n = ft_atoi(&msh->envp[i][6]);
			new_shlvl = ft_strdup("SHLVL=");
			sh_level = ft_itoa(++n);
			new_shlvl = ft_mem_exp(new_shlvl, sizeof(char) * 6, \
						sizeof(char) * (7 + ft_strlen(sh_level)));
			ft_strcat(new_shlvl, sh_level);
			change_env_value(msh, new_shlvl, i);
			break ;
		}
		i++;
	}
}
