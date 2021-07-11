/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_fct_chevron.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 18:53:46 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/11 14:08:04 by pbrochar         ###   ########.fr       */
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

static char	*remove_key_word(char *heredoc_str)
{
	char	*new_str;
	int		i;

	i = ft_strlen(heredoc_str);
	while (i > 0 && heredoc_str[i] != '\n')
		i--;
	if (heredoc_str[i] == '\n')
		i++;
	new_str = malloc(sizeof(char) * (i + 2));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, heredoc_str, (i + 1));
	free(heredoc_str);
	return (new_str);
}

static void	leave_db_chevron_left(t_master *msh, char *heredoc_str)
{
	heredoc_str = remove_key_word(heredoc_str);
	if (msh->heredoc_env_var == true)
		heredoc_str = manage_env_variable(msh, heredoc_str);
	rest_term(msh);
	((t_command *)msh->commands->prev->content)->std_in_data = heredoc_str;
	remove_lst_elem(msh);
	msh->heredoc_running = false;
	write(1, "\n", 1);
}

static void	db_chevron_pass_quote(char *arg, int *i, int c)
{
	while (arg[*i] != c)
		(*i)++;
	(*i)++;
}

static void	db_chevron_remove_quote(t_master *msh)
{
	int		i;
	char	*arg;
	char	*new_arg;

	i = 1;
	arg = ((t_command *)msh->commands->next->content)->command_arg[0];
	if (arg[0] == 34)
	{
		msh->heredoc_env_var = true;
		db_chevron_pass_quote(&arg[i], &i, 34);
	}
	else if (arg[0] == 39)
		db_chevron_pass_quote(&arg[i], &i, 39);
	else
		return ;
	new_arg = malloc(sizeof(char) * (i + 1));
	if (new_arg == NULL)
		return ;
	ft_strlcpy(new_arg, &arg[1], i);
	free(((t_command *)msh->commands->next->content)->command_arg[0]);
	((t_command *)msh->commands->next->content)->command_arg[0] = new_arg;
}

static char	*init_db_chevron_left(t_master *msh)
{
	char	*heredoc_str;

	msh->heredoc_env_var = false;
	db_chevron_remove_quote(msh);
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
}
