/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 15:48:33 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/06 19:03:42 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quote(char **arg, int i)
{
	int j;
	char *temp;

	j = ft_strlen(&arg[i][1]);
	temp = malloc(sizeof(char) * j);
	if (temp == NULL)
		return ;
	ft_strlcpy(temp, &arg[i][1], j);
	free(arg[i]);
	arg[i] = temp;
}

char **manage_arg(t_master *msh, char **arg)
{
	int	i;
	
	i = 0;
	if (!arg)
		return (arg);
	while (arg[i])
	{
		if (arg[i] && arg[i][0] == 34)
		{
			arg[i] = manage_env_variable(msh, arg[i]);
			remove_quote(arg, i);
		}
		else if (arg[i] && arg[i][0] == 39)
			remove_quote(arg, i);
		else
			arg[i] = manage_env_variable(msh, arg[i]);
		i++;
	}
	return (arg);
}