/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 16:45:11 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/15 19:02:04 by pbrochar         ###   ########.fr       */
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

void	mv_curs_left(t_master *msh);
void	mv_curs_right(t_master *msh);
void	mv_curs_home(t_master *msh);
void	mv_curs_end(t_master *msh);
void	mv_curs_right_word(t_master *msh);
void	mv_curs_left_word(t_master *msh);
void	mv_curs_up_multiline(t_master *msh);
void	mv_curs_down_multiline(t_master *msh);
void	paste_selection(t_master *msh);
void	select_left(t_master *msh);
void	select_right(t_master *msh);
void	select_home(t_master *msh);
void	select_end(t_master *msh);
void	remove_select(t_master *msh);
void	select_word_left(t_master *msh);
void	select_word_right(t_master *msh);
void	copy_select(t_master *msh);
void	select_all(t_master *msh);
void	cut_select(t_master *msh);
void	buffer_select(t_master *msh);
void	paste_buff_select(t_master *msh);
void go_to_start_term_line(t_master *msh);
void	go_to_end_term_line(t_master *msh);
void manage_delete_multiline(t_master *msh);
void	select_mode(t_master *msh);
void	reset_curs_pos(t_master *msh);
void	set_curs_pos(t_master *msh, int abs);
void	set_alt_curs_pos(t_master *msh, t_curs_pos *pos, int abs);
void	dec_curs_pos(t_master *msh);
void	inc_curs_pos(t_master *msh);
void	mv_curs_abs(t_master *msh, int x, int y);
char *remove_multi_char(t_master *msh);
void	delete_multi_display(t_master *msh);
void	history_management(t_master *msh);
void	clear_line_display(t_master *msh);
void	delete_key_display(t_master *msh);
void		save_curs_pos(t_master *msh);
void		rest_curs_pos(t_master *msh);
void	manage_page_up(t_master *msh);
void	manage_page_dw(t_master *msh);
void	browse_history_back(t_master *msh);
void	browse_history_front(t_master *msh);
void	update_line_front(t_master *msh);
int init_msh_master_struct(t_master **msh_m, char **envp, t_term *term_c);
void init_prompt(t_master **msh_m);
int	init_term(t_term **term_conf);
int	init_key_terms(t_term **key_terms);
void	leave_select_mode(t_master *msh);


int built_in_cd(t_master *msh, const char *path);
#endif