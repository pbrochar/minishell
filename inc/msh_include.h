/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_include.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 17:40:10 by pbrochar          #+#    #+#             */
/*   Updated: 2021/09/10 17:14:39 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_INCLUDE_H
# define MSH_INCLUDE_H

# include <stdio.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include "msh_structs.h"
# include "msh_select_mode.h"
# include "msh_cursor_movements.h"
# include "msh_history.h"
# include "msh_curs_pos.h"
# include "msh_free.h"
# include "msh_built_in.h"
# include "msh_opt.h"
# include "msh_init.h"
# include "libft.h"
# include "msh_execute.h"
# include "msh_signal.h"
# include "msh_split.h"

#endif