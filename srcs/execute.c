/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 20:23:03 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/11 16:50:02 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_parser(t_master *msh)
{
	t_list *temp;

	temp = msh->commands;
	while (msh->commands)
	{
		while (((t_command *)msh->commands->content)->op == NULL)
			msh->commands = msh->commands->next;
		if (((t_command *)msh->commands->content)->op != NULL && \
			ft_strcmp(((t_command *)msh->commands->content)->op, "<<") == 0)
			((t_command *)msh->commands->content)->op_fct(msh);
		if (msh->sigint_signal == true)
			break ;
		msh->commands = msh->commands->next;
	}
	msh->commands = temp;
}

void	execute_list(t_master *msh)
{
	msh->commands = msh->commands->next;
	while (msh->commands)
	{
		((t_command *)msh->commands->content)->op_fct(msh);
		if (((t_command *)msh->commands->content)->op != NULL && \
			((t_command *)msh->commands->content)->op[0] == '\0')
			return ;
		msh->commands = msh->commands->next;
		while (((t_command *)msh->commands->content)->op == NULL)
			msh->commands = msh->commands->next;
	}
}

void	rest_struct_after_exec(t_master *msh)
{
	if (msh->line)
		free(msh->line);
	free_command_arg(msh);
	msh->line = NULL;
	msh->line_len = 0;
	msh->nb_line = 0;
	msh->commands = NULL;
	msh->save_commands_list = NULL;
	reset_curs_pos(msh);
}

static int	str_is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	execute_line(t_master *msh)
{
	update_prompt_values(msh);
	write(1, "\n", 1);
	if (msh->line_len != 0 && !str_is_space(msh->line))
	{
		msh_split_ops(msh);
		history_management(msh);
		heredoc_parser(msh);
		if (msh->sigint_signal == false)
			execute_list(msh);
	}
	print_prompt(msh);
	rest_struct_after_exec(msh);
	msh->sigint_signal = false;
	return (0);
}
