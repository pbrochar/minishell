/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 20:07:15 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/08 20:09:12 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_built_in(t_master **msh)
{
	(*msh)->built_in = malloc(sizeof(t_built_in));
	if ((*msh)->built_in == NULL)
		return ;
	(*msh)->built_in->built_in_list[0] = BI_CD;
	(*msh)->built_in->built_in_list[1] = BI_ECHO;
	(*msh)->built_in->built_in_list[2] = BI_ENV;
	(*msh)->built_in->built_in_list[3] = BI_EXIT;
	(*msh)->built_in->built_in_list[4] = BI_EXPORT;
	(*msh)->built_in->built_in_list[5] = BI_PWD;
	(*msh)->built_in->built_in_list[6] = BI_UNSET;
	(*msh)->built_in->built_in_list[7] = NULL;
	(*msh)->built_in->built_in_fct[0] = &built_in_cd;
	(*msh)->built_in->built_in_fct[1] = &built_in_echo;
	(*msh)->built_in->built_in_fct[2] = &built_in_env;
	(*msh)->built_in->built_in_fct[3] = &built_in_exit;
	(*msh)->built_in->built_in_fct[4] = &built_in_export;
	(*msh)->built_in->built_in_fct[5] = &built_in_pwd;
	(*msh)->built_in->built_in_fct[6] = &built_in_unset;
	(*msh)->built_in->built_in_fct[7] = NULL;
}
