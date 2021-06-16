/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_split_ops.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:10:23 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/16 12:57:33 by pbrochar         ###   ########.fr       */
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

static void fill_list(t_master *msh, int a, int i)
{
	t_command *new_command;

	new_command = malloc(sizeof(t_command));
	new_command->command_arg = msh_split_command(&msh->line[a], i - a);
	new_command->op_fct = NULL;
	ft_lstadd_back(&msh->commands, ft_lstnew(new_command));
}

static void	fill_list_op(t_master *msh, int ret)
{
	t_command *new_op;

	new_op = malloc(sizeof(new_op));
	new_op->op_fct = msh->ops_fct[ret];
	new_op->command_arg = malloc(sizeof(char *));
	new_op->command_arg[0] = NULL;
	ft_lstadd_back(&msh->commands, ft_lstnew(new_op));
}

void msh_split_ops(t_master *msh)
{
	int	i;
	int a;
	int ret;
//	t_command command;
	

	i = 0;
	a = 0;
	while (msh->line[i])
	{
		ret = is_operand(&msh->line[i]);
		a = i;
		while (msh->line[i] && ret == -1)
		{
			i++;
			ret = is_operand(&msh->line[i]);
		}
		if (ret != -1 || !msh->line[i])
		{
			fill_list(msh, a, i);
			if (ret != -1)
				fill_list_op(msh, ret);
			i += ft_strlen(msh->operands[ret]);
		}
	}
	//printf("%s\n", msh->commands->content);
	while (msh->commands)
	{

		if (((t_command *)(msh->commands->content))->command_arg[0] != NULL)
		{
			int i = 0;
			while (((t_command *)(msh->commands->content))->command_arg[i])
			{
				printf("%s\n", ((t_command *)msh->commands->content)->command_arg[i]);
				i++;
			}
		}
		else
			((t_command *)(msh->commands->content))->op_fct(msh);
		printf("-----\n");
		msh->commands = msh->commands->next;
		
		//msh->commands = msh->commands->next;
	}
}