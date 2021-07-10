/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_fct_chevron.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 18:53:46 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/10 19:53:04 by pbrochar         ###   ########.fr       */
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

static int	line_arg_comp(char *line, char *arg)
{
	int	i;

	i = ft_strlen(line);
	while (i > 0 && line[i] != '\n')
		i--;
	if (line[i] == '\n')
		i++;
	if (ft_strcmp(&line[i], arg) == 0)
		return (1);
	return (0);
}

static void	rest_term(t_master *msh)
{
	if (msh->sigint_signal == true)
	{
		msh->term->term.c_cc[VMIN] = 1;
		msh->term->term.c_cc[VTIME] = 0;
		tcsetattr(0, TCSANOW, &((msh->term)->term));
	}
}

static void	remove_lst_elem(t_master *msh)
{
	msh->commands = msh->commands->prev;
	lst_del_one(msh->commands->next);
	lst_del_one(msh->commands->next);
}

static void	fill_heredoc_str(char **heredoc_str, char c)
{
	int	size;

	write(1, &c, 1);
	size = ft_strlen(*heredoc_str);
	(*heredoc_str) = ft_mem_exp((*heredoc_str), size, size + 2);
	size++;
	(*heredoc_str)[size - 1] = c;
	(*heredoc_str)[size] = '\0';
}

static void	leave_db_chevron_left(t_master *msh, char *heredoc_str)
{
	rest_term(msh);
	((t_command *)msh->commands->prev->content)->std_in_data = heredoc_str;
	remove_lst_elem(msh);
	msh->heredoc_running = false;
}

static char	*init_db_chevron_left(t_master *msh)
{
	char	*heredoc_str;

	msh->heredoc_running = true;
	heredoc_str = malloc(sizeof(char));
	if (heredoc_str == NULL)
		return (NULL);
	heredoc_str[0] = '\0';
	write(1, "> ", 2);
	return (heredoc_str);
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
	write(1, "\n", 1);
}
