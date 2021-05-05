/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_structs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 17:02:09 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/05 15:24:33 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_STRUCTS_H
# define MSH_STRUCTS_H

# include "libft.h"
# include "define_msh.h"
# include "minishell.h"

/*
** key_term array contains only the keyboard keys that will have a particular 
** action the shell behavior.
** Basically it contains left/right/up/down arrow, Backspace, Home and End key.
*/
typedef struct	s_term
{
	struct termios	term;
	struct termios	backup;
	char			*key_term[NB_KEY];
	char			*delete_char;
	char			*clean_line;
	char			*mv_left;
	char			*mv_right;
	char			*ipt_mode;
	char 			*lve_ipt_mode;
	char			*inv_curs;
	char			*vis_curs;
}				t_term;

typedef struct	s_command
{
	char *command;
	char **command_args;
}				t_command;

typedef struct	s_prompt
{
	char	*user;
	char	*dir;
	int		user_len;
	int		dir_len;
}				t_prompt;

typedef struct	s_master
{
	int			curs_pos;
	int			prompt_len;
	int			line_len;
	t_prompt	*prompt;
	t_list		*commands;
	t_list		*history;
	t_list		*pos_in_history;
	t_term		*term;
	char		*line;
	char		**envp;
}				t_master;

#endif