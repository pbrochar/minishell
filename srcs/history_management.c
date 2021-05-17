/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 10:27:18 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/17 20:16:23 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/*
** These functions allow the line to be added to the history.
**
** The history is represented by a double chained list,
** allowing then to navigate in both directions (see history_browse).
**
** If the line is empty (= if the line contains only spaces) then it is not
** added to the history.
*/

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
	if (!line)
		return (1);
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
