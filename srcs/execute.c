/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 20:23:03 by pbrochar          #+#    #+#             */
/*   Updated: 2021/09/11 19:43:22 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_master *msh)
{
	t_list	*temp;
	int		i = 0;

	temp = msh->commands;
	while (temp)
	{
		if ((((t_command *)temp->content)->op != NULL))
			printf("[%s]\n", ((t_command *)temp->content)->op);
		if (((t_command *)temp->content)->command_arg != NULL)
		{
			i = 0;
			while(((t_command *)temp->content)->command_arg[i])
			{
				printf("|%s|\n", ((t_command *)temp->content)->command_arg[i]);
				i++;
			}
		}
		temp = temp->next;
	}
}

void	execute_list(t_master *msh)
{
	while (msh->commands)
	{
		if (((t_command *)msh->commands->content)->op != NULL && \
			((t_command *)msh->commands->content)->op[0] == 'B')
			msh->commands = msh->commands->next;
		if (((t_command *)msh->commands->content)->op_fct != NULL)
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
	if (msh->abort == true)
		msh->abort = false;
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
		final_parser(msh);
	//	print_list(msh);
		if (msh->sigint_signal == false && msh->abort == false)
			execute_list(msh);
	}
	print_prompt(msh);
	rest_struct_after_exec(msh);
	msh->sigint_signal = false;
	return (0);
}
