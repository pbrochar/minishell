/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 18:26:19 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/04 18:32:18 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_buffer(t_master *msh)
{
	int	i;

	i = 0;
	while (i < NB_BUFFER)
	{
		free(msh->buffer[i]);
		i++;
	}
	free(msh->buffer);
}

void	free_env(t_master *msh)
{
	int	i;

	i = 0;
	while (msh->envp[i])
	{
		free(msh->envp[i]);
		i++;
	}
	free(msh->envp);
}

void	free_history(t_master *msh)
{
	t_list *temp;
	
	while (msh->history != NULL)
	{
		if (msh->history->content)
			free(msh->history->content);
		temp = msh->history;
		msh->history = msh->history->next;
		free(temp);
	}
}

int	built_in_exit(t_master *msh, char **arg)
{
	int	i;

	i = 0;
	if (msh->line)
		free(msh->line);
	if (msh->clipboard)
		free(msh->clipboard);
	free_buffer(msh);
	free(msh->prompt->dir);
	free(msh->prompt);
	free(msh->curs_pos);
	free(msh->save_curs_pos);
	free(msh->select->begin);
	free(msh->select->end);
	free(msh->select);
	free_env(msh);
	free_history(msh);
	while (arg[i])
	{
		free(arg[i]);
		i++;
	}
	if (arg)
		free(arg);
	//free_term_struct(msh);
//	free(msh->term);
	//other free to do
	tcsetattr(0, TCSANOW, &(msh->term->backup));
	free(msh->term);
	free(msh);
	exit(0);
}
