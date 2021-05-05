/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 10:27:18 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/05 13:33:09 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void		add_in_history(t_master *msh)
{
	char *new_line;

	new_line = ft_strdup(msh->line);
	if (new_line != NULL)
		ft_lstadd_front(&msh->history, ft_lstnew(new_line));
}

static int		line_is_empty(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i])
		return (0);
	return (1);
}

void			history_management(t_master *msh)
{
	if (line_is_empty(msh->line) == 1)
		return ;
	else
	{
		add_in_history(msh);
		msh->pos_in_history = msh->history;
	}
}
