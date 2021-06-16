/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_split_ops.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:10:23 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/16 19:34:06 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_operand(char *op)
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

static int fill_list_command(t_master *msh, int a, int i)
{
	t_command *new_command;

	new_command = malloc(sizeof(t_command));
	if (new_command == NULL)
		return (-1);
	new_command->command_arg = msh_split_command(&msh->line[a], i - a);
	new_command->command_arg = manage_arg(msh, new_command->command_arg);
	new_command->op_fct = NULL;
	new_command->op = NULL;
	ft_lstadd_back(&msh->commands, ft_lstnew(new_command));
	return (0);
}

static int fill_list_op(t_master *msh, int ret)
{
	t_command *new_op;

	new_op = malloc(sizeof(t_command));
	if (new_op == NULL)
		return (-1);
	new_op->op_fct = msh->ops_fct[ret];
	new_op->command_arg = NULL;
	new_op->op = ft_strdup(msh->operands[ret]);
	ft_lstadd_back(&msh->commands, ft_lstnew(new_op));
	return (0);
}

static int fill_end_list(t_master *msh)
{
	t_command *end_op;
	
	end_op = malloc(sizeof(t_command));
	if (end_op == NULL)
		return (-1);
	end_op->op_fct = &end_of_list;
	end_op->command_arg = NULL;
	end_op->op = ft_strdup("\0");
	ft_lstadd_back(&msh->commands, ft_lstnew(end_op));
	return (0);
}

static void pass_quote(t_master *msh, int *i, int c)
{
	(*i)++;
	while (msh->line[*i] && msh->line[*i] != c)
		(*i)++;
}

void msh_split_ops(t_master *msh)
{
	int	i;
	int a;
	int ret;

	i = 0;
	a = 0;
	while (msh->line[i])
	{
		a = i;
		while (msh->line[i])
		{
			ret = is_operand(&msh->line[i]);
			if (ret != -1)
				break ;
			if (msh->line[i] == 34)
				pass_quote(msh, &i, 34);
			if (msh->line[i] == 39)
				pass_quote(msh, &i, 39);
			i++;
		}
		if (ret != -1 || !msh->line[i])
		{
			fill_list_command(msh, a, i);
			if (ret != -1)
				fill_list_op(msh, ret);
			i += ft_strlen(msh->operands[ret]);
			if (i > msh->line_len)
				break ;
		}
	}
	msh->save_commands_list = msh->commands;
	fill_end_list(msh);
}