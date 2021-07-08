/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_opt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 21:34:32 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/08 21:42:42 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_OPT_H
# define MSH_OPT_H

# include "minishell.h"

/*
** from srcs/opt_fct.c
*/
void		end_of_list(t_master *msh);
void		execute_fct(t_master *msh, char **arg);
void		semicolon_fct(t_master *msh);

/*
** from srcs/opt_fct_chevron.c
*/
void		chevron_left_fct(t_master *msh);
void		chevron_right_fct(t_master *msh);
void		db_chevron_left_fct(t_master *msh);
void		db_chevron_right_fct(t_master *msh);

/*
** from srcs/opt_pipe.c
*/
void		pipe_fct(t_master *msh);

/*
** from srcs/opt_pipe_child.c
*/
void		manage_child_fd(int i, int old_fd[2], \
							int new_fd[2], int pipe_count);

/*
** from srcs/opt_pipe_exec.c
*/
int			execute_fct_pipe(t_master *msh);

/*
** from srcs/opt_pipe_parent.c
*/
void		manage_parent_fd(int old_fd[2], int new_fd[2], \
								int i, int pipe_count);

/*
** from srcs/opt_wait_pid.c
*/
void		parent_wait_pid(t_master *msh);

#endif