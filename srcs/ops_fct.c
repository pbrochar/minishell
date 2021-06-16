/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_fct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:26:19 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/16 15:38:33 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_fct(t_master *msh, char **arg)
{
	int built_in_i;

	built_in_i = is_built_in(msh, arg[0]);
	if (built_in_i != -1)
		msh->built_in->built_in_fct[built_in_i](msh, arg);
	else
		exec_command(msh, arg);
}

void semicolon_fct(t_master *msh)
{
	if (msh->commands->prev->prev == NULL)
		execute_fct(msh, ((t_command *)msh->commands->prev->content)->command_arg);
	else if (msh->commands->prev->prev && ((t_command *)msh->commands->prev->prev->content)->op[0] == ';')
		execute_fct(msh, ((t_command *)msh->commands->prev->content)->command_arg);
}

void pipe_fct(t_master *msh)
{
	(void)msh;
	printf("pipe fct\n");
}

void chevron_right_fct(t_master *msh)
{
	(void)msh;
	printf("chevron right fct\n");
}

void db_chevron_right_fct(t_master *msh)
{
	(void)msh;
	printf("db chevron right fct\n");
}

void chevron_left_fct(t_master *msh)
{
	(void)msh;
	printf("chevron left fct\n");
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