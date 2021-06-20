/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_split_manage.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 14:04:59 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/20 14:12:41 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pass_char(char *command, int *i, int op_pos, int c)
{
	(*i)++;
	while (command[*i] && *i < op_pos && command[*i] != c)
		(*i)++;
	(*i)++;
}

void	manage_quote(char *command, int *i, int op_pos, int *nb_word)
{
	if (command[*i] == 34 && command[*i + 1])
	{
		pass_char(command, i, op_pos, 34);
		(*nb_word)++;
		return ;
	}
	if (command[*i] == 39 && command[*i + 1])
	{
		pass_char(command, i, op_pos, 39);
		(*nb_word)++;
		return ;
	}
}

void	manage_word(char *command, int *i, int op_pos, int *nb_word)
{
	(*nb_word)++;
	while (*i < op_pos && command[*i] && command[*i] != 32)
		(*i)++;
}
