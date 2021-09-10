/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_structs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 17:02:09 by pbrochar          #+#    #+#             */
/*   Updated: 2021/09/10 17:18:45 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_STRUCTS_H
# define MSH_STRUCTS_H

# include "libft.h"
# include "msh_define.h"
# include "minishell.h"

typedef struct s_master	t_master;

/*
** key_term array contains only the keyboard keys that will have a particular 
** action the shell behavior.
** Basically it contains left/right/up/down arrow, Backspace, Home and End key.
**
** key_fct is an array to function's pointer. It is used for the different 
** functions of the keyboard keys as well as the keyboard shortcuts.
** It works with the key_term array.
*/
typedef struct s_term
{
	struct termios	term;
	struct termios	backup;
	int				fd;
	char			*key_term[NB_KEY];
	void			(*key_fct[NB_KEY])(t_master *);
	char			*key_term_select_mode[NB_KEY_SELECT];
	void			(*key_fct_select_mode[NB_KEY_SELECT])(t_master *);
	char			*delete_char;
	char			*clean_line;
	char			*mv_left;
	char			*mv_right;
	char			*ipt_mode;
	char			*lve_ipt_mode;
	char			*inv_curs;
	char			*vis_curs;
	char			*standout_enter;
	char			*standout_leave;
	char			*up_curs;
	char			*scroll_line_up;
	char			*set_curs_on_line;
}				t_term;

typedef struct s_command
{
	char	*op;
	char	**command_arg;
	void	(*op_fct)(t_master *);
	int		std_in;
	int		std_out;
	char	*std_in_data;
}				t_command;

typedef struct s_prompt
{
	char	*user;
	char	*dir;
	int		user_len;
	int		dir_len;
}				t_prompt;

typedef struct s_curs_pos
{
	int	curs_pos_rel;
	int	curs_pos_abs;	
}				t_curs_pos;

typedef struct s_select
{
	int			is_select;
	t_curs_pos	*begin;
	t_curs_pos	*end;
}				t_select;

typedef struct s_built_in
{
	char	*built_in_list[NB_BUILT_IN];
	int		(*built_in_fct[NB_BUILT_IN])(t_master *, char **);
}				t_built_in;

typedef struct s_master
{
	t_curs_pos	*curs_pos;
	t_curs_pos	*save_curs_pos;
	t_select	*select;
	t_built_in	*built_in;
	int			prompt_len;
	int			line_len;
	int			nb_line;
	int			res_x;
	int			res_y;
	t_prompt	*prompt;
	t_list		*commands;
	t_list		*save_commands_list;
	t_list		*history;
	t_list		*pos_in_history;
	t_term		*term;
	char		*line;
	char		*clipboard;
	char		**envp;
	char		**buffer;
	char		**path;
	char		*operands[NB_OPERAND];
	void		(*ops_fct[NB_OPERAND])(t_master *);
	int			return_value;
	char		*return_value_char;
	int			pid;
	bool		commmand_running;
	bool		heredoc_running;
	bool		heredoc_env_var;
	bool		sigint_signal;
	bool		abort;
	int			old_fd[2];
	int			new_fd[2];
	int			heredoc_fd[2];
}				t_master;

typedef struct	s_parser
{
	int		j;
	int		size;
	bool	simple_quote_flag;
}				t_parser;

typedef struct	s_count_words
{
	int	nb_word;
	int	len;
	int	is_quote;
}				t_count_words;

typedef struct	s_split_ops
{
	int	a;
	int	ret;
	int	is_quote;
}				t_split_ops;

#endif