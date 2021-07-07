/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_opt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 14:06:26 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/07 17:02:55 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_OPT_H
# define MSH_OPT_H

# include "minishell.h"
 
/*
** from srcs/pipe_opt.c
*/
void		pipe_fct(t_master *msh);

/*
** from srcs/pipe_opt_child.c
*/
void		manage_child_fd(int i, int old_fd[2], int new_fd[2], int pipe_count);

/*
** from srcs/pipe_opt_exec.c
*/
int		execute_fct_pipe(t_master *msh);

/*
** from srcs/pipe_opt_parent.c
*/
void		manage_parent_fd(int old_fd[2], int new_fd[2], int i, int pipe_count);

/*
** from srcs/opt_wait_pid.c
*/
void		parent_wait_pid(t_master *msh);

#endif