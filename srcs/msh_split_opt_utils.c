/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_split_opt_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 18:56:31 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/08 18:57:49 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operand(char *op)
{
	int	i;

	i = 0;
	if (op[0] == ';')
		return (0);
	else if (op[0] == '|')
		return (1);
	else if (op[0] == '>')
	{
		if (op[1] && op[1] == '>')
			return (3);
		else
			return (2);
	}
	else if (op[0] == '<')
	{
		if (op[1] && op[1] == '<')
			return (5);
		else
			return (4);
	}
	return (-1);
}

void	pass_quote(t_master *msh, int *i)
{
	if (msh->line[*i] == 39)
	{
		(*i)++;
		while (msh->line[*i] && msh->line[*i] != 39)
			(*i)++;
		return ;
	}
	else if (msh->line[*i] == 34)
	{
		(*i)++;
		while (msh->line[*i] && msh->line[*i] != 34)
			(*i)++;
		return ;
	}
}
