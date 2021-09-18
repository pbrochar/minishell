/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_final.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 15:40:58 by pbrochar          #+#    #+#             */
/*   Updated: 2021/09/12 17:53:41 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_synt_err(t_master *msh)
{
	if (((t_command *)msh->commands->content)->op != NULL && \
		(((t_command *)msh->commands->content)->op[0] == ';' || \
		((t_command *)msh->commands->content)->op[0] == '|' || \
		((t_command *)msh->commands->content)->op[0] == '>') && \
		((t_command *)msh->commands->prev && \
		((t_command *)msh->commands->prev->content)->op != NULL))
	{
		ft_putstr_fd(SYNT_ERR, STDERR_FILENO);
		ft_putstr_fd(((t_command *)msh->commands->content)->op, \
						STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		msh->abort = true;
		ret_value(msh, 2);
		return (true);
	}
	return (false);
}

void	final_parser(t_master *msh)
{
	t_list	*temp;

	temp = msh->commands;
	while (msh->commands)
	{
		if (((t_command *)msh->commands->content)->op != NULL && \
			ft_strcmp(((t_command *)msh->commands->content)->op, "<<") == 0)
			((t_command *)msh->commands->content)->op_fct(msh);
		if (msh->sigint_signal == true)
			break ;
		if (check_synt_err(msh) == true)
			break ;
		msh->commands = msh->commands->next;
	}
	msh->commands = temp;
}
