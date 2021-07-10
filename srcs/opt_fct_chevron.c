/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_fct_chevron.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 18:53:46 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/10 18:26:02 by pbrochar         ###   ########.fr       */
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
	int		ret;
	char	buf[51];

	msh->heredoc_running = true;
	write(1, "> ", 2);
	ret = read(STDIN_FILENO, buf, 50);
	while (ret > 0)
	{
		buf[ret] = '\0';
		//printf("%d\n", buf[0]);
		if (buf[0] == 'a')
			printf("toto\n");
		else if (ret == 1 && buf[0] == '\n')
		{
			write(1, "\n> ", 3);
		}
		else if (ft_isalnum(buf[0]) != 0)
			write(1, buf, 1);
		ft_bzero(buf, 51);
		ret = read(STDIN_FILENO, buf, 50);
	}
	if (msh->sigint_signal == true)
	{
		msh->term->term.c_cc[VMIN] = 1;
		msh->term->term.c_cc[VTIME] = 0;
		tcsetattr(0, TCSANOW, &((msh->term)->term));
	}
	msh->heredoc_running = false;
}
