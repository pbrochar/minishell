/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_fct_chevron.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 18:53:46 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/21 14:50:22 by pbrochar         ###   ########.fr       */
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
	char	*heredoc_str;

	heredoc_str = init_db_chevron_left(msh);
	ret = read(STDIN_FILENO, buf, 50);
	while (ret > 0)
	{
		buf[ret] = '\0';
		if (ret == 1 && buf[0] == '\n')
		{
			if (line_arg_comp(heredoc_str, ((t_command *)msh->commands->next \
									->content)->command_arg[0]) == 1)
				break ;
			fill_heredoc_str(&heredoc_str, buf[0]);
			write(1, "> ", 2);
		}
		else if (is_char_to_print(buf, ret) == 1)
			fill_heredoc_str(&heredoc_str, buf[0]);
		ft_bzero(buf, 51);
		ret = read(STDIN_FILENO, buf, 50);
	}
	leave_db_chevron_left(msh, heredoc_str);
}
