/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_split_ops.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:10:23 by pbrochar          #+#    #+#             */
/*   Updated: 2021/09/10 15:19:22 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	fill_list_command(t_master *msh, int a, int i)
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command));
	if (new_command == NULL)
		return (-1);
	if (i == 0)
		new_command->command_arg = NULL;
	else
		new_command->command_arg = msh_split_command(&msh->line[a], i - a);
	new_command->op_fct = NULL;
	new_command->op = NULL;
	new_command->std_in_data = NULL;
	new_command->std_in = STDIN_FILENO;
	new_command->std_out = STDOUT_FILENO;
	ft_lstadd_back(&msh->commands, ft_lstnew(new_command));
	return (0);
}

static int	fill_list_op(t_master *msh, int ret)
{
	t_command	*new_op;

	new_op = malloc(sizeof(t_command));
	if (new_op == NULL)
		return (-1);
	new_op->op_fct = msh->ops_fct[ret];
	new_op->command_arg = NULL;
	new_op->std_in_data = NULL;
	new_op->op = ft_strdup(msh->operands[ret]);
	new_op->std_in = STDIN_FILENO;
	new_op->std_out = STDOUT_FILENO;
	ft_lstadd_back(&msh->commands, ft_lstnew(new_op));
	return (0);
}

static int	fill_end_list(t_master *msh)
{
	t_command	*end_op;

	end_op = malloc(sizeof(t_command));
	if (end_op == NULL)
		return (-1);
	end_op->op_fct = &end_of_list;
	end_op->command_arg = NULL;
	end_op->op = ft_strdup("\0");
	end_op->std_in_data = NULL;
	end_op->std_in = STDIN_FILENO;
	end_op->std_out = STDOUT_FILENO;
	ft_lstadd_back(&msh->commands, ft_lstnew(end_op));
	return (0);
}

int	fill_begin_list(t_master *msh)
{
	t_command	*begin_op;

	begin_op = malloc(sizeof(t_command));
	if (begin_op == NULL)
		return (-1);
	begin_op->op_fct = NULL;
	begin_op->command_arg = NULL;
	begin_op->op = ft_strdup("B");
	begin_op->std_in_data = NULL;
	begin_op->std_in = STDIN_FILENO;
	begin_op->std_out = STDOUT_FILENO;
	ft_lstadd_back(&msh->commands, ft_lstnew(begin_op));
	return (0);
}

static int	check_space(t_master *msh, int a, int i)
{
	while (a < i && msh->line[a])
	{
		if (ft_isspace(msh->line[a]) == 0)
			return (1);
		a++;
	}
	return (0);
}

static int	fill_list(t_master *msh, int a, int ret, int *i)
{
	if (check_space(msh, a, *i))
		fill_list_command(msh, a, *i);
	if (ret != -1)
	{
		fill_list_op(msh, ret);
		(*i) += ft_strlen(msh->operands[ret]);
	}
	if (*i > msh->line_len)
		return (0);
	return (1);
}

static void	change_quote(int quote_type, int *is_quote)
{
	if (*is_quote == quote_type)
		*is_quote = 0;
	else
		*is_quote = quote_type;
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

void	msh_split_ops(t_master *msh)
{
	int	i;
	int	a;
	int	ret;
	int	is_quote;

	i = -1;
	a = 0;
	is_quote = 0;
	fill_begin_list(msh);
	while (++i < msh->line_len)
	{
		if (check_spec_char(msh, &i, &is_quote) == 1)
			continue ;
		if (!is_quote)
		{	
			ret = is_operand(msh->line, i);
			if (ret != -1)
			{
				fill_list(msh, a, ret, &i);
				a = i;
			}
			ret = is_operand(msh->line, i);
			while (i < msh->line_len && ret != -1)
			{
				fill_list_op(msh, is_operand(msh->line, i));
				i += ft_strlen(msh->operands[ret]);
				ret = is_operand(msh->line, i);
				a = i;
			}
		}
	}
	fill_list(msh, a, ret, &i);
	msh->save_commands_list = msh->commands;
	fill_end_list(msh);
}
