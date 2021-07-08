/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 20:24:05 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/08 20:24:26 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_built_in(t_master *msh, char *name)
{
	int	i;

	i = 0;
	if (!name)
		return (-1);
	while (msh->built_in->built_in_list[i])
	{
		if (ft_strcmp(name, msh->built_in->built_in_list[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}
