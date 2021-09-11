/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_split_ops.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:10:23 by pbrochar          #+#    #+#             */
/*   Updated: 2021/09/11 16:13:11 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_space(t_master *msh, int a, int i)
{
	while (a < i && msh->line[a])
	{
		if (ft_isspace(msh->line[a]) == 0)
			return (1);
		a++;
	}
	return (0);
}

static int	check_spec_char(t_master *msh, int *i, int *is_quote)
{
	if (msh->line[*i] == '\'')
	{
		change_quote('\'', is_quote);
		return (1);
	}
	else if (!is_quote && msh->line[*i] == '\\')
	{
		(*i)++;
		return (1);
	}
	else if (msh->line[*i] == '\"')
	{
		change_quote('\"', is_quote);
		return (1);
	}
	return (0);
}

static void	split_and_fill(t_split_ops *var, t_master *msh, int *i)
{
	var->ret = is_operand(msh->line, *i);
	if (var->ret != -1)
	{
		fill_list(msh, var->a, var->ret, i);
		var->a = *i;
	}
	var->ret = is_operand(msh->line, *i);
	while (*i < msh->line_len && var->ret != -1)
	{
		fill_list_op(msh, is_operand(msh->line, *i));
		(*i) += ft_strlen(msh->operands[var->ret]);
		var->ret = is_operand(msh->line, *i);
		var->a = *i;
	}
}

void	msh_split_ops(t_master *msh)
{
	t_split_ops	var;
	int			i;

	i = -1;
	var.a = 0;
	var.is_quote = 0;
	var.ret = -1;
	fill_begin_list(msh);
	while (++i < msh->line_len)
	{
		if (check_spec_char(msh, &i, &var.is_quote) == 1)
			continue ;
		if (!var.is_quote)
			split_and_fill(&var, msh, &i);
	}
	fill_list(msh, var.a, var.ret, &i);
	msh->save_commands_list = msh->commands;
	fill_end_list(msh);
}
