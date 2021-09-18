/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_arg_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:10:38 by pbrochar          #+#    #+#             */
/*   Updated: 2021/09/18 16:11:00 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_special_char(char *line, int *i)
{
	if (line[(*i) + 1] && (line[(*i) + 1] == '\\' \
		|| line[(*i) + 1] == '\"' || line[(*i) + 1] == '$' \
		|| (is_operand(line, (*i) + 1) != -1) \
		|| line[(*i) + 1] == ' '))
		(*i)++;
}

int	manage_simple_quote_parser(t_parser *var, char *line, int i)
{
	if (!var->double_quote_flag && line[i] == '\'')
	{
		var->simple_quote_flag = !var->simple_quote_flag;
		return (0);
	}
	return (1);
}
