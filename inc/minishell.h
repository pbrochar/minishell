/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 16:45:11 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/06 17:33:41 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "msh_include.h"

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


void	update_prompt_values(t_master *msh);
void	print_prompt(t_master *msh);

int	exec_command(t_master *msh, char **arg);
char **msh_split_command(char *command, int op_pos);
char **manage_arg(t_master *msh, char **arg);

char *find_in_env(t_master *msh, char *var);
char	*env_value(char *env_var);
char	*manage_env_variable(t_master *msh, char *arg);
void semicolon_fct(t_master *msh);
void pipe_fct(t_master *msh);
void chevron_right_fct(t_master *msh);
void db_chevron_right_fct(t_master *msh);
void chevron_left_fct(t_master *msh);
void db_chevron_left_fct(t_master *msh);
void msh_split_ops(t_master *msh);
void end_of_list(t_master *msh);

int	is_built_in(t_master *msh, char *name);

void	manage_word(char *command, int *i, int op_pos, int *nb_word);
void	manage_quote(char *command, int *i, int op_pos, int *nb_word);
void	pass_char(char *command, int *i, int op_pos, int c);
char	*add_path_in_command(t_master *msh, char *name, int path_index);
int search_command(t_master *msh, char **arg);

#endif