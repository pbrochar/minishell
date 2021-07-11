/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_heredoc_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 19:09:40 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/11 19:10:41 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	line_arg_comp(char *line, char *arg)
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

void	rest_term(t_master *msh)
{
	if (msh->sigint_signal == true)
	{
		msh->term->term.c_cc[VMIN] = 1;
		msh->term->term.c_cc[VTIME] = 0;
		tcsetattr(0, TCSANOW, &((msh->term)->term));
	}
}

void	remove_lst_elem(t_master *msh)
{
	msh->commands = msh->commands->prev;
	lst_del_one(msh->commands->next);
	lst_del_one(msh->commands->next);
}

void	fill_heredoc_str(char **heredoc_str, char c)
{
	int	size;

	write(1, &c, 1);
	size = ft_strlen(*heredoc_str);
	(*heredoc_str) = ft_mem_exp((*heredoc_str), size, size + 2);
	size++;
	(*heredoc_str)[size - 1] = c;
	(*heredoc_str)[size] = '\0';
}
