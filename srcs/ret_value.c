/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 14:47:13 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/07 14:48:45 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ret_value(t_master *msh, int ret)
{
	msh->return_value = ret;
	if (msh->return_value_char != NULL)
		free(msh->return_value_char);
	msh->return_value_char = ft_itoa(ret);
}