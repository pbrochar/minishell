/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 17:42:38 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/08 18:24:58 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_string(t_master *msh)
{
	if (msh->line)
		free(msh->line);
	if (msh->clipboard)
		free(msh->clipboard);
	if (msh->prompt->dir)
		free(msh->prompt->dir);
	if (msh->return_value_char)
		free(msh->return_value_char);
}

void	free_main(t_master *msh)
{
	free_string(msh);
	if (msh->prompt)
		free(msh->prompt);
	if (msh->curs_pos)
		free(msh->curs_pos);
	if (msh->save_curs_pos)
		free(msh->save_curs_pos);
	if (msh->select->begin)
		free(msh->select->begin);
	if (msh->select->end)
		free(msh->select->end);
	if (msh->select)
		free(msh->select);
	if (msh->built_in)
		free(msh->built_in);
	free_env(msh);
	free_history(msh);
	free_buffer(msh);
	free_command_arg(msh);
}
