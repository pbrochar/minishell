/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_history.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 17:35:59 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/05 17:36:12 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_HISTORY_H
# define MSH_HISTORY_H

# include "msh_structs.h"

/*
** from srcs/history_browse.c
*/
void		browse_history_back(t_master *msh);
void		browse_history_front(t_master *msh);

/*
** from srcs/history_management.c
*/
void		history_management(t_master *msh);

#endif