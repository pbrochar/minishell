/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_opt_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 14:00:26 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/07 14:01:34 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_command_pipe(t_master *msh, char **arg)
{
	int		i;
	char	*command;

	if (arg[0] == NULL || arg[0][0] == 32)
		return (-1);
	if (arg[0][0] == '.' || arg[0][0] == '/')
		command = ft_strdup(arg[0]);
	else
	{
		i = search_command(msh, arg);
		if (i == -1)
		{
			ft_printf("msh: command not found: %s\n", arg[0]);
			return (-1);
		}
		command = add_path_in_command(msh, arg[0], i);
	}
	execve(command, arg, msh->envp);
	return (0);
}

void	execute_fct_pipe(t_master *msh)
{
	int		built_in_i;
	char	**arg;

	arg = ((t_command *)msh->commands->prev->content)->command_arg;
	if (!arg)
		return ;
	built_in_i = is_built_in(msh, arg[0]);
	if (built_in_i != -1)
		msh->built_in->built_in_fct[built_in_i](msh, arg);
	else
		exec_command_pipe(msh, arg);
}
