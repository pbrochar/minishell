#ifndef CURS_POS_H
# define CURS_POS_H

# include "msh_structs.h"

/*
** from srcs/set_curs_pos.c
*/
void		dec_curs_pos(t_master *msh);
void		inc_curs_pos(t_master *msh);
void		reset_curs_pos(t_master *msh);
void		set_alt_curs_pos(t_master *msh, t_curs_pos *pos, int abs);
void		set_curs_pos(t_master *msh, int abs);

#endif