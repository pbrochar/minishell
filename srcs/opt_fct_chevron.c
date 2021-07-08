/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_fct_chevron.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 18:53:46 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/08 18:54:18 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	chevron_right_fct(t_master *msh)
{
	int	fd;

	if (((t_command *)msh->commands->next->content)->command_arg == NULL)
	{
		printf("Error, need a file name\n");
		return ;
	}
	else
		fd = open(((t_command *)msh->commands->next->content)->command_arg[0], \
					 O_RDWR | O_CREAT | O_TRUNC, 0644);
	((t_command *)msh->commands->prev->content)->std_out = fd;
	msh->commands = msh->commands->prev;
	lst_del_one(msh->commands->next);
	lst_del_one(msh->commands->next);
}

void	db_chevron_right_fct(t_master *msh)
{
	int	fd;

	if (((t_command *)msh->commands->next->content)->command_arg == NULL)
	{
		printf("Error, need a file name\n");
		return ;
	}
	else
		fd = open(((t_command *)msh->commands->next->content)->command_arg[0], \
								O_RDWR | O_CREAT | O_APPEND, 0644);
	((t_command *)msh->commands->prev->content)->std_out = fd;
	msh->commands = msh->commands->prev;
	lst_del_one(msh->commands->next);
	lst_del_one(msh->commands->next);
}

void	chevron_left_fct(t_master *msh)
{
	int	fd;

	if (((t_command *)msh->commands->next->content)->command_arg == NULL)
	{
		printf("Error, need a file name\n");
		return ;
	}
	else
		fd = open(((t_command *)msh->commands->next->content)->command_arg[0], \
								 O_RDONLY);
	((t_command *)msh->commands->prev->content)->std_in = fd;
	msh->commands = msh->commands->prev;
	lst_del_one(msh->commands->next);
	lst_del_one(msh->commands->next);
}

void	db_chevron_left_fct(t_master *msh)
{
	(void)msh;
	printf("db chevron left fct\n");
}
