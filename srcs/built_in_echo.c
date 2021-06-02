/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 15:02:34 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/02 15:12:39 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int built_in_echo(t_master *msh, char **arg)
{
	int i;
	int print_newline;

	(void)msh;
	i = 1;
	print_newline = 1;
	if (arg[1] && ft_strncmp(arg[1], "-n", 2) == 0)
	{
		print_newline = 0;
		i++;
	}
	while (arg[i])
	{
		ft_printf("%s", arg[i]);
		if (arg[i + 1])
			ft_printf(" ");
		i++;
	}
	if (print_newline == 1)
		ft_printf("\n");
	return (0);
}