/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_env_var_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 18:58:35 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/08 18:59:32 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_env_var(char *arg, int i)
{
	if ((arg[i] == '$' && i == 0) || \
			(i > 0 && arg[i] == '$' && arg[i - 1] != '\\'))
		return (1);
	return (0);
}

void	pass_backspace(char *arg, char *new_line, int *i, int *j)
{
	if (arg[*i] == '\\')
		(*i)++;
	new_line[*j] = arg[*i];
	(*i)++;
	(*j)++;
}
