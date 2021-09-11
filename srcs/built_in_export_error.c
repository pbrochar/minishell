/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export_error.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 18:09:37 by pbrochar          #+#    #+#             */
/*   Updated: 2021/09/10 18:10:47 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_err_bad_identifier(char *arg)
{
	ft_printf("msh: export: ");
	ft_printf("`%s\': ", arg);
	ft_printf("not a valid identifier\n");
}
