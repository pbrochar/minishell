/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:29:13 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/02 18:12:17 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "colors.h"

/*
** Function to update the shell mode display.
** Possible modes :
** 'n' (normal)
** 's' (select mode)
** 'b' (copy in buffer mode)
** 'p' (paste buffer mode)
*/

void	print_mode(t_master *msh, char c, char *color)
{
	save_curs_pos(msh);
	mv_curs_abs(msh, msh->prompt_len - 3, 0);
	set_curs_pos(msh, msh->prompt_len - 3);
	write(1, color, ft_strlen(color));
	write(1, &c, 1);
	write(1, TEXT_NORMAL, 4);
	mv_curs_abs(msh, msh->save_curs_pos->curs_pos_abs % msh->res_x, \
				msh->save_curs_pos->curs_pos_abs / msh->res_x);
	rest_curs_pos(msh);
}
