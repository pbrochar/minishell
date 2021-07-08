/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_del_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:40:11 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/08 20:54:54 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_del_one(t_list *lst)
{
	int	i;

	i = 0;
	if (lst->prev)
		lst->prev->next = lst->next;
	if (lst->next)
		lst->next->prev = lst->prev;
	if (((t_command *)lst->content)->op)
		free(((t_command *)lst->content)->op);
	if (((t_command *)lst->content)->command_arg)
	{
		while (((t_command *)lst->content)->command_arg[i])
		{
			free(((t_command *)lst->content)->command_arg[i]);
			i++;
		}
		free(((t_command *)lst->content)->command_arg);
	}
	free(lst->content);
	free(lst);
}
