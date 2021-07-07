/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_fct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:26:19 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/07 19:34:41 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_fct(t_master *msh, char **arg)
{
	int built_in_i;
	int old_stdout;
	int	old_stdin;

	if (!arg)
		return ;
	arg = manage_arg(msh, arg);
	built_in_i = is_built_in(msh, arg[0]);
	setup_fd(msh, &old_stdout, &old_stdin);
	if (built_in_i != -1)
		msh->built_in->built_in_fct[built_in_i](msh, arg);
	else
		exec_command(msh, arg);
	restore_fd(msh, old_stdout, old_stdin);
}

void semicolon_fct(t_master *msh)
{
	if (msh->commands->prev->prev == NULL)
		execute_fct(msh, ((t_command *)msh->commands->prev->content)->command_arg);
	else if (msh->commands->prev->prev && ((t_command *)msh->commands->prev->prev->content)->op[0] == ';')
		execute_fct(msh, ((t_command *)msh->commands->prev->content)->command_arg);
}

void chevron_right_fct(t_master *msh)
{
	int	fd;
//	int	save_out;

	if (((t_command *)msh->commands->next->content)->command_arg == NULL)
	{
		printf("Error, need a file name\n");
		return ;
	}
	else
		fd = open(((t_command *)msh->commands->next->content)->command_arg[0], O_RDWR | O_CREAT | O_TRUNC, 0644);
	((t_command *)msh->commands->prev->content)->std_out = fd;
	msh->commands = msh->commands->prev;
	lst_del_one(msh->commands->next);
	lst_del_one(msh->commands->next);
}

void db_chevron_right_fct(t_master *msh)
{
	int	fd;

	if (((t_command *)msh->commands->next->content)->command_arg == NULL)
	{
		printf("Error, need a file name\n");
		return ;
	}
	else
		fd = open(((t_command *)msh->commands->next->content)->command_arg[0], O_RDWR | O_CREAT | O_APPEND, 0644);
	((t_command *)msh->commands->prev->content)->std_out = fd;
	msh->commands = msh->commands->prev;
	lst_del_one(msh->commands->next);
	lst_del_one(msh->commands->next);
}

void chevron_left_fct(t_master *msh)
{
	int	fd;

	if (((t_command *)msh->commands->next->content)->command_arg == NULL)
	{
		printf("Error, need a file name\n");
		return ;
	}
	else
		fd = open(((t_command *)msh->commands->next->content)->command_arg[0], O_RDONLY);
	((t_command *)msh->commands->prev->content)->std_in = fd;
	msh->commands = msh->commands->prev;
	lst_del_one(msh->commands->next);
	lst_del_one(msh->commands->next);
}

void db_chevron_left_fct(t_master *msh)
{
	(void)msh;
	printf("db chevron left fct\n");
}

void end_of_list(t_master *msh)
{
	if (msh->commands->prev->prev == NULL)
		execute_fct(msh, ((t_command *)msh->commands->prev->content)->command_arg);
	else if (msh->commands->prev->prev && ((t_command *)msh->commands->prev->prev->content)->op[0] == ';')
		execute_fct(msh, ((t_command *)msh->commands->prev->content)->command_arg);
}