/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_split_ops_fill.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:31:34 by pbrochar          #+#    #+#             */
/*   Updated: 2021/09/11 15:43:27 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_list_command(t_master *msh, int a, int i)
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

int	fill_list_op(t_master *msh, int ret)
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

int	fill_end_list(t_master *msh)
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

int	fill_list(t_master *msh, int a, int ret, int *i)
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
