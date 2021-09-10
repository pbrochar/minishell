/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_fct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:26:19 by pbrochar          #+#    #+#             */
/*   Updated: 2021/09/10 14:51:24 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_path(t_master **msh)
{
	int		i;
	char	*temp;

	i = 0;
	while ((*msh)->envp[i] && ft_strncmp((*msh)->envp[i], "PATH=", 5) != 0)
		i++;
	if (!(*msh)->envp[i])
	{
		(*msh)->path = malloc(sizeof(char *));
		(*msh)->path[0] = NULL;
		return ;
	}
	temp = ft_strchr((*msh)->envp[i], '=');
	i = 1;
	(*msh)->path = ft_split(&temp[i], ':');
}

void	execute_fct(t_master *msh, char **arg)
{
	int	built_in_i;
	int	old_stdout;
	int	old_stdin;

	if (!arg)
		return ;
	arg = manage_arg(msh, arg);
	built_in_i = is_built_in(msh, arg[0]);
	setup_fd(msh, &old_stdout, &old_stdin);
	if (built_in_i != -1)
		msh->built_in->built_in_fct[built_in_i](msh, arg);
	else
	{
		init_path(&msh);
		exec_command(msh, arg);
		free_path(msh);
	}
	restore_fd(msh, old_stdout, old_stdin);
}

void	semicolon_fct(t_master *msh)
{
	if (((t_command *)msh->commands->prev->prev->content)->op[0] == 'B' || \
		(msh->commands->prev->prev && ((t_command *)msh->commands->prev-> \
						prev->content)->op[0] == ';'))
		execute_fct(msh, ((t_command *)msh->commands->prev->content) \
						->command_arg);
}

void	end_of_list(t_master *msh)
{
	if (msh->commands->prev->prev == NULL)
		execute_fct(msh, ((t_command *)msh->commands->prev->content) \
						->command_arg);
	else if (msh->commands->prev->prev && \
		 (((t_command *)msh->commands->prev->prev->content)->op[0] == ';' || \
		 	((t_command *)msh->commands->prev->prev->content)->op[0] == 'B'))
		execute_fct(msh, ((t_command *)msh->commands->prev->content) \
						->command_arg);
}
