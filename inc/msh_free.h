/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_free.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 17:46:06 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/05 17:46:15 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_FREE_H
# define MSH_FREE_H

# include "msh_structs.h"

/*
** from srcs/free_buffer.c
*/
void		free_buffer(t_master *msh);

/*
** from srcs/free_command_arg.c
*/
void		free_command_arg(char **arg);

/*
** from srcs/free_env.c
*/
void		free_env(t_master *msh);

/*
** from srcs/free_history.c
*/
void		free_history(t_master *msh);

/*
** from srcs/free_main.c
*/
void		free_main(t_master *msh, char **arg);

/*
** from srcs/free_path.c
*/
void		free_path(t_master *msh);

#endif