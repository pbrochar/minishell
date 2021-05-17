/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv_curs_abs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 21:12:22 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/17 22:03:44 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** The cursor movements are allowed thanks to two integers, defining the
** relative and absolute position of the cursor.
** These two integers are defined in the curs_pos structure
**
** These positions are specific to the line (between the prompt and the size
** of the command entered) and not in relation to the terminal window.
**
** The relative position represents the position of the cursor in relation
** to the command entered. So a 0 position is located just after the prompt.
**
** So there is a correlation between the relative position and the
** char in the char * line.
*/

/*
** This function allows to move the cursor to a given place on the line.
** It starts by moving to the requested y and then to the x.
** This function does not update the cursor position.
*/

void	mv_curs_abs(t_master *msh, int x, int y)
{
	int curr_line;

	if (msh->is_multiline == 1)
		curr_line = msh->curr_line;
	else
		curr_line = msh->curs_pos->curs_pos_abs / msh->res_x;
	if (x < 0)
		return ;
	if (y < 0 || y > msh->nb_line)
		return ;
//	printf("y = %d, curr = %d\n", y, curr_line);
	if (y < curr_line)
	{
		while (y < curr_line)
		{
		
			tputs(tgetstr("up", NULL), 1, ft_putchar);
			y++;
		}
	}
	if (y > curr_line)
	{
		while (y > curr_line)
		{
			tputs(tgetstr("sf", NULL), 1, ft_putchar);
			y--;
		}
	}
	tputs(tgoto(tgetstr("ch", NULL), 0, x), 1, ft_putchar);
}
