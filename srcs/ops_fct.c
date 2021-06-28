/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_fct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:26:19 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/28 17:59:22 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_fct(t_master *msh, char **arg)
{
	int built_in_i;

	if (!arg)
		return ;
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

static int parse_pipes(t_master *msh)
{
	int		n_pipes;
	t_list	*temp;

	n_pipes = 1;
	temp = msh->commands;
	while (((t_command *)temp->content)->op[0] == '|')
	{
		temp = temp->next->next;
		n_pipes++;
	}
	return (n_pipes);
}

void	pipe_fct(t_master *msh)
{
	int	old_fd[2];
	int	new_fd[2];
	t_list *temp;
	int pid;
	int i;
	i = 0;
	int n_pipe = parse_pipes(msh);

	temp = msh->commands;
	tcsetattr(0, TCSANOW, &(msh->term->backup));
	while (i < n_pipe)
	{
		if (i < (n_pipe - 1))
			pipe(new_fd);
		pid = fork();
		if (!pid)
		{
			if (i > 0)
			{
				dup2(old_fd[0], STDIN_FILENO);
				close(old_fd[0]);
				close(old_fd[1]);
			}
			if (i < (n_pipe - 1))
			{
				close(new_fd[0]);
				dup2(new_fd[1], STDOUT_FILENO);
				close(new_fd[1]);
			}
			execve(((t_command *)temp->prev->content)->command_arg[0], \
				((t_command *)temp->prev->content)->command_arg, msh->envp);	
		}
		else
		{
			if (i > 0)
			{
				close(old_fd[0]);
				close(old_fd[1]);
			}
			if (i < (n_pipe - 1))
			{
				old_fd[0] = new_fd[0];
				old_fd[1] = new_fd[1];
			}
			waitpid(pid, NULL, 0);
			i++;
			if (i < n_pipe) 
				temp = temp->next->next;
		}
	}
	msh->commands = temp;
	close(old_fd[0]);
	close(old_fd[1]);
	tcsetattr(0, TCSANOW, &msh->term->term);
}

void chevron_right_fct(t_master *msh)
{
	int	fd;
	int	save_out;

	if (((t_command *)msh->commands->next->content)->command_arg == NULL)
	{
		printf("Error, need a file name\n");
		return ;
	}
	else
		fd = open(((t_command *)msh->commands->next->content)->command_arg[0], O_RDWR | O_CREAT | O_TRUNC, 0644);
	save_out = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	execute_fct(msh, ((t_command *)msh->commands->prev->content)->command_arg);
	dup2(save_out, STDOUT_FILENO);
	close(save_out);
	close(fd);
}

void db_chevron_right_fct(t_master *msh)
{
	int	fd;
	int	save_out;

	if (((t_command *)msh->commands->next->content)->command_arg == NULL)
	{
		printf("Error, need a file name\n");
		return ;
	}
	else
		fd = open(((t_command *)msh->commands->next->content)->command_arg[0], O_RDWR | O_CREAT | O_APPEND, 0644);
	save_out = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	execute_fct(msh, ((t_command *)msh->commands->prev->content)->command_arg);
	dup2(save_out, STDOUT_FILENO);
	close(save_out);
	close(fd);
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