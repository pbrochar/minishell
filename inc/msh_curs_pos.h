/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_curs_pos.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 17:34:40 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/05 17:36:27 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_CURS_POS_H
# define MSH_CURS_POS_H

# include "msh_structs.h"

/*
** from srcs/set_curs_pos.c
*/
void		dec_curs_pos(t_master *msh);
void		inc_curs_pos(t_master *msh);
void		reset_curs_pos(t_master *msh);
void		set_alt_curs_pos(t_master *msh, t_curs_pos *pos, int abs);
void		set_curs_pos(t_master *msh, int abs);

#endif