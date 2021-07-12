/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 18:26:19 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/12 15:47:20 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	str_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (-1);
		i++;
	}
	return (1);
}

int	built_in_exit(t_master *msh, char **arg)
{
	int	ret;

	ret = msh->return_value;
	if (arg && arg[0] && ft_strcmp(arg[0], "exit") == 0)
		write(STDERR_FILENO, "exit\n", 5);
	if (arg && arg[0] && arg[1] && str_is_digit(arg[1]) == -1)
	{
		ft_putstr_fd("msh: exit: ", STDERR_FILENO);
		ft_putstr_fd(arg[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		ret = 2;
	}
	else if (arg && arg[0] && arg[1] && arg[2])
	{
		ft_putstr_fd("msh: exit: too many arguments\n", STDERR_FILENO);
		ret = 1;
	}
	else if (arg && arg[0] && arg[1])
		ret = ft_atoi(arg[1]);
	tcsetattr(0, TCSANOW, &(msh->term->backup));
	free_main(msh);
	exit(ret);
}
