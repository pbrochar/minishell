/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 15:02:34 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/12 15:46:14 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	manage_n_opt(t_master *msh, char **arg, int i)
{
	msh->prompt_len += ft_strlen(arg[i]);
	if (arg[i + 1])
		msh->prompt_len++;
}

static int	check_arg_opt(char **arg)
{
	int	i;
	int	a;

	i = 1;
	a = 0;
	while (arg[i])
	{
		if (arg[i] && arg[1][0] == '-')
		{
			a = 1;
			while (arg[i][a] == 'n')
				a++;
			if (arg[i][a])
				return (i);
		}
		else
			return (-1);
		i++;
	}
	return (-1);
}

int	built_in_echo(t_master *msh, char **arg)
{
	int	i;
	int	print_newline;

	i = 1;
	print_newline = 1;
	i = check_arg_opt(arg);
	if (i == -1)
		i = 1;
	else
		print_newline = 0;
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
	ret_value(msh, 0);
	return (0);
}
