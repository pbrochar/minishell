/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_fct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:26:19 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/20 15:24:40 by pbrochar         ###   ########.fr       */
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
	int	fd;
	int	save_out;

	if (((t_command *)msh->commands->next->content)->command_arg == NULL)
	{
		printf("error\n");
		return ;
	}
	else
		fd = open(((t_command *)msh->commands->next->content)->command_arg[0], O_RDWR | O_CREAT, 0777);
	save_out = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	execute_fct(msh, ((t_command *)msh->commands->prev->content)->command_arg);
	dup2(save_out, STDOUT_FILENO);
	close(fd);
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