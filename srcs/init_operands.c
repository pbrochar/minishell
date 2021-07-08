/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_operands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 20:00:03 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/08 20:05:33 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_operands(t_master **msh)
{
	(*msh)->operands[0] = SEMICOLON;
	(*msh)->operands[1] = PIPE;
	(*msh)->operands[2] = CHEVRON_RIGHT;
	(*msh)->operands[3] = DB_CHEVRON_RIGHT;
	(*msh)->operands[4] = CHEVRON_LEFT;
	(*msh)->operands[5] = DB_CHEVRON_LEFT;
	(*msh)->operands[6] = NULL;
}

void	init_operands_fct(t_master **msh)
{
	(*msh)->ops_fct[0] = &semicolon_fct;
	(*msh)->ops_fct[1] = &pipe_fct;
	(*msh)->ops_fct[2] = &chevron_right_fct;
	(*msh)->ops_fct[3] = &db_chevron_right_fct;
	(*msh)->ops_fct[4] = &chevron_left_fct;
	(*msh)->ops_fct[5] = &db_chevron_left_fct;
	(*msh)->ops_fct[6] = NULL;
}
