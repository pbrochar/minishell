#ifndef CURSOR_MOVEMENTS_H
# define CURSOR_MOVEMENTS_H

# include "msh_structs.h"

/*
** from srcs/mv_curs_abs.c
*/
void		mv_curs_abs(t_master *msh, int x, int y);

/*
** from srcs/mv_curs_home_end.c
*/
void		mv_curs_end(t_master *msh);
void		mv_curs_home(t_master *msh);

/*
** from srcs/mv_curs_right_left.c
*/
void		go_to_end_term_line(t_master *msh);
void		go_to_start_term_line(t_master *msh);
void		mv_curs_left(t_master *msh);
void		mv_curs_right(t_master *msh);

/*
** from srcs/mv_curs_up_down.c
*/
void		mv_curs_down_multiline(t_master *msh);
void		mv_curs_up_multiline(t_master *msh);

/*
** from srcs/mv_curs_words.c
*/
void		mv_curs_left_word(t_master *msh);
void		mv_curs_right_word(t_master *msh);

#endif