/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 16:45:11 by pbrochar          #+#    #+#             */
/*   Updated: 2021/09/10 15:41:32 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "msh_include.h"

const static t_master *g_msh;

void	paste_clipboard(t_master *msh);
void	manage_delete_multiline(t_master *msh);
void	clear_line_display(t_master *msh);
void	delete_key_display(t_master *msh);
void	save_curs_pos(t_master *msh);
void	rest_curs_pos(t_master *msh);
void	update_line_front(t_master *msh);
void	print_mode(t_master *msh, char c, char *color);
int		paste_clipboard_management(t_master *msh, int clip_len);
int		key_is_term_select(t_master *msh, char *buf);
void	update_prompt_values(t_master *msh);
void	print_prompt(t_master *msh);
int		exec_command(t_master *msh, char **arg);
char	**msh_split_command(char *command, int op_pos);
char	**manage_arg(t_master *msh, char **arg);
char	*find_in_env(t_master *msh, char *var);
char	*env_value(char *env_var);
char	*manage_env_variable(t_master *msh, char *arg);
void	msh_split_ops(t_master *msh);
int		is_built_in(t_master *msh, char *name);
void	manage_word(char *command, int *i, int op_pos, int *nb_word);
void	manage_quote(char *command, int *i, int op_pos, int *nb_word);
void	pass_char(char *command, int *i, int op_pos, int c);
char	*add_path_in_command(t_master *msh, char *name, int path_index);
int		search_command(t_master *msh, char **arg);
int		ret_value(t_master *msh, int ret);
void	lst_del_one(t_list *lst);
void	setup_fd(t_master *msh, int *old_stdout, int *old_stdin);
void	restore_fd(t_master *msh, int old_stdout, int old_stdin);
void	pass_quote(t_master *msh, int *i);
int		is_operand(char *op, int i);
void	pass_backspace(char *arg, char *new_line, int *i, int *j);
int		is_env_var(char *arg, int i);
void	execute_list(t_master *msh);
int		execute_line(t_master *msh);
int		is_built_in(t_master *msh, char *name);
int		msh_main_loop(t_master *msh_m);
int		print_char_management(t_master *msh, char *buf);
void	add_in_line(t_master *msh, char c);
void	rest_struct_after_exec(t_master *msh);
int		is_char_to_print(char *buf, int ret);
void	init_path(t_master **msh);
void	change_env_value(t_master *msh, char *arg, int index);
void	change_shlvl(t_master *msh);
int		insert_env_value(t_master *msh, char **new_line, char *arg, int *pos);

void	print_err_num_arg(char *arg);
int	print_err_too_m_a(t_master *msh);
int	print_err_bad_folder(t_master *msh, char *folder, int err);
void	final_parser(t_master *msh);

#endif