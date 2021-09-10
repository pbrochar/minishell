/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 15:32:05 by pbrochar          #+#    #+#             */
/*   Updated: 2021/09/10 15:37:12 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_err_too_m_a(t_master *msh)
{
	ft_putstr_fd(CD_TOO_M_A, STDERR_FILENO);
	return (ret_value(msh, 1));
}

int	print_err_bad_folder(t_master *msh, char *folder, int err)
{
	printf("cd : %s: %s\n", folder, strerror(err));
	return (ret_value(msh, 1));
}
