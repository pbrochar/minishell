/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_opt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:26:59 by pbrochar          #+#    #+#             */
/*   Updated: 2021/09/18 16:27:20 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_OPT_H
# define MSH_OPT_H

/*
** from srcs/opt_fct.c
*/
void		end_of_list(t_master *msh);
void		execute_fct(t_master *msh, char **arg);
void		init_path(t_master **msh);
void		semicolon_fct(t_master *msh);

/*
** from srcs/opt_fct_chevron.c
*/
void		chevron_left_fct(t_master *msh);
void		chevron_right_fct(t_master *msh);
void		db_chevron_left_fct(t_master *msh);
void		db_chevron_right_fct(t_master *msh);

/*
** from srcs/opt_heredoc.c
*/
char		*init_db_chevron_left(t_master *msh);
char		*remove_key_word(char *heredoc_str);
void		db_chevron_pass_quote(char *arg, int *i, int c);
void		db_chevron_remove_quote(t_master *msh);
void		leave_db_chevron_left(t_master *msh, char *heredoc_str);

/*
** from srcs/opt_heredoc_utils.c
*/
int			line_arg_comp(char *line, char *arg);
void		fill_heredoc_str(char **heredoc_str, char c);
void		remove_lst_elem(t_master *msh);
void		rest_term(t_master *msh);

/*
** from srcs/opt_pipe.c
*/
void		pipe_fct(t_master *msh);

/*
** from srcs/opt_pipe_child.c
*/
void		manage_child_fd(t_master *msh, int i, int pipe_count);
void		manage_child_process(t_master *msh, int i, int pipe_count);

/*
** from srcs/opt_pipe_exec.c
*/
int			execute_fct_pipe(t_master *msh);
void		restore_fd(t_master *msh, int old_stdout, int old_stdin);
void		setup_fd(t_master *msh, int *old_stdout, int *old_stdin);

/*
** from srcs/opt_pipe_heredoc.c
*/
void		heredoc_pipe_parent(t_master *msh, int heredoc_fd[2]);
void		pipe_heredoc(t_master *msh);
void		heredoc_pipe_child(t_master *msh, int heredoc_fd[2]);

/*
** from srcs/opt_pipe_parent.c
*/
void		manage_parent_fd(int old_fd[2], int new_fd[2], int i, \
								int pipe_count);
void		manage_parent_process(t_master *msh, int i, int pipe_count);

/*
** from srcs/opt_wait_pid.c
*/
void		parent_wait_pid(t_master *msh);

#endif