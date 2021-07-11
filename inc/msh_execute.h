/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_execute.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 19:24:48 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/11 19:24:59 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_EXECUTE_H
# define MSH_EXECUTE_H

# include "minishell.h"

/*
** from srcs/execute.c
*/
int			execute_line(t_master *msh);
void		execute_list(t_master *msh);
void		heredoc_parser(t_master *msh);
void		rest_struct_after_exec(t_master *msh);

/*
** from srcs/execute_command.c
*/
char		*add_path_in_command(t_master *msh, char *name, int path_index);
int			exec_command(t_master *msh, char **arg);

/*
** from srcs/execute_command_child.c
*/
void		exec_manage_child_process(t_master *msh, int fd_pipe[2], char *command, char **arg);
void		manage_heredoc_child(t_master *msh, int fd_pipe[2]);

/*
** from srcs/execute_command_parent.c
*/
void		exec_manage_parent_process(t_master *msh, int fd_pipe[2], char *command);
void		manage_heredoc_parent(t_master *msh, int fd_pipe[2]);

#endif