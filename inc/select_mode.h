/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_mode.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 19:53:42 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/17 19:56:25 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECT_MODE_H
# define SELECT_MODE_H

# include "msh_structs.h"

/*
** from srcs/select_all.c
*/
void		select_all(t_master *msh);

/*
** from srcs/select_copy_buffer.c
*/
void		buffer_select(t_master *msh);
void		copy_in_buffer(t_master *msh, int rang);

/*
** from srcs/select_copy_cut.c
*/
void		copy_select(t_master *msh);
void		cut_select(t_master *msh);

/*
** from srcs/select_home_end.c
*/
void		select_end(t_master *msh);
void		select_home(t_master *msh);

/*
** from srcs/select_mode_main.c
*/
int			key_is_term_select(t_master *msh, char *buf);
void		leave_select_mode(t_master *msh);
void		manage_page_dw(t_master *msh);
void		manage_page_up(t_master *msh);
void		select_loop(t_master *msh);
void		select_mode(t_master *msh);

/*
** from srcs/select_paste_buffer.c
*/
char		*insert_buffer_in_line(t_master *msh, int rang);
int			paste_buffer_management(t_master *msh, int rang);
void		paste_buff_select(t_master *msh);
void		paste_buffer(t_master *msh, int rang);

/*
** from srcs/select_remove.c
*/
char		*remove_multi_char(t_master *msh);
void		delete_multi_display(t_master *msh);
void		remove_select(t_master *msh);

/*
** from srcs/select_right_left.c
*/
void		select_left(t_master *msh);
void		select_right(t_master *msh);

/*
** from srcs/select_unselect.c
*/
void		unselect_for_leave(t_master *msh);

/*
** from srcs/select_utils.c
*/
void		swap_select_curs(t_master *msh);

/*
** from srcs/select_words.c
*/
void		select_word_left(t_master *msh);
void		select_word_right(t_master *msh);

#endif