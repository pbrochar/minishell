/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_split.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:27:26 by pbrochar          #+#    #+#             */
/*   Updated: 2021/09/18 16:27:30 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_SPLIT_H
# define MSH_SPLIT_H

/*
** from srcs/msh_split.c
*/
char		**msh_split_command(char *command, int op_pos);

/*
** from srcs/msh_split_manage.c
*/
void		manage_quote(char *command, int *i, int op_pos, int *nb_word);
void		manage_word(char *command, int *i, int op_pos, int *nb_word);
void		pass_char(char *command, int *i, int op_pos, int c);

/*
** from srcs/msh_split_ops.c
*/
int			check_space(t_master *msh, int a, int i);
void		msh_split_ops(t_master *msh);

/*
** from srcs/msh_split_ops_fill.c
*/
int			fill_begin_list(t_master *msh);
int			fill_end_list(t_master *msh);
int			fill_list(t_master *msh, int a, int ret, int *i);
int			fill_list_command(t_master *msh, int a, int i);
int			fill_list_op(t_master *msh, int ret);

/*
** from srcs/msh_split_opt_utils.c
*/
int			is_operand(char *op, int i);
void		pass_quote(t_master *msh, int *i);

/*
** from srcs/msh_split_utils.c
*/
char		*create_word(int *i, int j, char *command);
char		*return_word(char *command, int op_pos, int *i);
void		change_quote(int quote_type, int *is_quote);
void		init_var_count_words(t_count_words *var, char *command);
void		update_nb_words(t_count_words *var, int *i, char *com, int op_pos);

#endif