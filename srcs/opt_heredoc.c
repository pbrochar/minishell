/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 19:07:32 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/19 20:03:29 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leave_db_chevron_left(t_master *msh, char *heredoc_str)
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

void	db_chevron_pass_quote(char *arg, int *i, int c)
{
	while (arg[*i] != c)
		(*i)++;
	(*i)++;
}

char	*remove_key_word(char *heredoc_str)
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

void	db_chevron_remove_quote(t_master *msh)
{
	int		i;
	char	*arg;
	char	*new_arg;

	i = 1;
	arg = ((t_command *)msh->commands->next->content)->command_arg[0];
	printf("%s\n", arg);
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
	printf("%s\n", new_arg);
	free(((t_command *)msh->commands->next->content)->command_arg[0]);
	((t_command *)msh->commands->next->content)->command_arg[0] = new_arg;
}

char	*init_db_chevron_left(t_master *msh)
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
