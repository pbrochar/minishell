/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 15:02:34 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/02 15:37:03 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void manage_n_opt(t_master *msh, char **arg, int i)
{
	msh->prompt_len += ft_strlen(arg[i]);
	if (arg[i + 1])
		msh->prompt_len++;
}

int built_in_echo(t_master *msh, char **arg)
{
	int i;
	int print_newline;

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
		if (print_newline == 0)
			manage_n_opt(msh, arg, i);
		i++;
	}
	if (print_newline == 1)
		ft_printf("\n");
	return (0);
}