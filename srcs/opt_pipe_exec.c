/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_pipe_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 14:00:26 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/11 20:43:31 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_fd(t_master *msh, int *old_stdout, int *old_stdin)
{
	if (((t_command *)msh->commands->prev->content)->std_out != STDOUT_FILENO)
	{
		*old_stdout = dup(STDOUT_FILENO);
		dup2(((t_command *)msh->commands->prev->content)->std_out, \
							STDOUT_FILENO);
	}
	if (((t_command *)msh->commands->prev->content)->std_in != STDIN_FILENO)
	{
		*old_stdin = dup(STDIN_FILENO);
		dup2(((t_command *)msh->commands->prev->content)->std_in, STDIN_FILENO);
	}
}

void	restore_fd(t_master *msh, int old_stdout, int old_stdin)
{
	if (((t_command *)msh->commands->prev->content)->std_out != STDOUT_FILENO)
	{
		dup2(old_stdout, STDOUT_FILENO);
		close(old_stdout);
		close(((t_command *)msh->commands->prev->content)->std_out);
	}
	if (((t_command *)msh->commands->prev->content)->std_in != STDIN_FILENO)
	{
		dup2(old_stdin, STDIN_FILENO);
		close(old_stdin);
		close(((t_command *)msh->commands->prev->content)->std_in);
	}
}

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
			ft_putstr_fd("msh: ", STDERR_FILENO);
			ft_putstr_fd(arg[0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			return (-1);
		}
		command = add_path_in_command(msh, arg[0], i);
	}
	change_shlvl(msh);
	execve(command, arg, msh->envp);
	return (0);
}

int	execute_fct_pipe(t_master *msh)
{
	int		built_in_i;
	char	**arg;
	int		old_stdout;
	int		old_stdin;
	int		ret;

	ret = 0;
	arg = ((t_command *)msh->commands->prev->content)->command_arg;
	arg = manage_arg(msh, arg);
	if (!arg)
		return (-1);
	msh->commmand_running = true;
	built_in_i = is_built_in(msh, arg[0]);
	setup_fd(msh, &old_stdout, &old_stdin);
	if (built_in_i != -1)
		msh->built_in->built_in_fct[built_in_i](msh, arg);
	else
	{
		init_path(&msh);
		ret = exec_command_pipe(msh, arg);
		free_path(msh);
	}
	restore_fd(msh, old_stdout, old_stdin);
	return (ret);
}
