#ifndef HISTORY_H
# define HISTORY_H

# include "msh_structs.h"

/*
** from srcs/history_browse.c
*/
void		browse_history_back(t_master *msh);
void		browse_history_front(t_master *msh);

/*
** from srcs/history_management.c
*/
void		history_management(t_master *msh);

#endif