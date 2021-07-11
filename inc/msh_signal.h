/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_signal.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 19:31:36 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/11 19:31:44 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_SIGNAL_H
# define MSH_SIGNAL_H

# include "minishell.h"

/*
** from srcs/signal_handler.c
*/
void		eot_handler(t_master *msh);
void		sigint_handler(int sig);
void		sigquit_handler(int sig);

#endif