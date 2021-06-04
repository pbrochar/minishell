/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 16:45:11 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/02 18:32:00 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>
# include "msh_structs.h"
# include "select_mode.h"
# include "cursor_movements.h"
# include "history.h"
# include "curs_pos.h"

void	paste_clipboard(t_master *msh);
void 	manage_delete_multiline(t_master *msh);

void	clear_line_display(t_master *msh);
void	delete_key_display(t_master *msh);
void	save_curs_pos(t_master *msh);
void	rest_curs_pos(t_master *msh);

void	update_line_front(t_master *msh);
int init_msh_master_struct(t_master **msh_m, char **envp, t_term *term_c);
void init_prompt(t_master **msh_m);
int	init_term(t_term **term_conf);
int	init_key_terms(t_term **key_terms);

void	print_mode(t_master *msh, char c, char *color);



int		paste_clipboard_management(t_master *msh, int clip_len);
int		key_is_term_select(t_master *msh, char *buf);

int built_in_cd(t_master *msh, char **arg);
int built_in_env(t_master *msh);
int built_in_pwd(t_master *msh);
int	built_in_export(t_master *msh, char **arg);
int built_in_unset(t_master *msh, char **arg);
int built_in_echo(t_master *msh, char **arg);
int	built_in_exit(t_master *msh, char **arg);

void	update_prompt_values(t_master *msh);
void	print_prompt(t_master *msh);

#endif