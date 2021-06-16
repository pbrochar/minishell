/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command_arg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 17:32:48 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/16 17:06:42 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command_arg(t_master *msh)
{
	int	i;
	char **arg;
	t_list *temp;

	msh->commands = msh->save_commands_list;
	while (msh->commands)
	{
		temp = msh->commands;
		i = 0;
		arg = ((t_command *)msh->commands->content)->command_arg;
		if (arg)
		{
			while (arg[i])
			{
				free(arg[i]);
				i++;
			}
			free(arg);
		}
		if (((t_command *)msh->commands->content)->op != NULL)
			free(((t_command *)msh->commands->content)->op);
		free(msh->commands->content);
		msh->commands = msh->commands->next;
		free(temp);
	}
	free(msh->commands);
}
