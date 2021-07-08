/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command_arg.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 17:32:48 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/08 19:41:10 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_arg(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i])
			free(arg[i]);
		i++;
	}
	free(arg);
}

void	free_command_arg(t_master *msh)
{
	int		i;
	char	**arg;
	t_list	*temp;

	msh->commands = msh->save_commands_list;
	while (msh->commands)
	{
		temp = msh->commands;
		i = 0;
		arg = ((t_command *)msh->commands->content)->command_arg;
		if (arg != NULL)
			free_arg(arg);
		if (((t_command *)msh->commands->content)->op != NULL)
			free(((t_command *)msh->commands->content)->op);
		if (msh->commands->content)
			free(msh->commands->content);
		msh->commands = msh->commands->next;
		if (temp)
			free(temp);
	}
	free(msh->commands);
}
