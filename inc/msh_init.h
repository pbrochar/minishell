/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_init.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 21:39:50 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/08 21:42:26 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_INIT_H
# define MSH_INIT_H

# include "minishell.h"

/*
** from srcs/init_built_in.c
*/
void		init_built_in(t_master **msh);

/*
** from srcs/init_key_select.c
*/
int			init_key_term_select(t_term **key_terms);
void		init_key_fct_select(t_term **key_terms);

/*
** from srcs/init_key_terms.c
*/
int			init_key_terms(t_term **key_terms);

/*
** from srcs/init_msh.c
*/
int			init_msh_master_struct(t_master **msh_m, \
							char **envp, t_term *term_c);
void		init_buffer(t_master **msh_m);
void		init_prompt(t_master **msh_m);

/*
** from srcs/init_operands.c
*/
void		init_operands(t_master **msh);
void		init_operands_fct(t_master **msh);

/*
** from srcs/init_structs.c
*/
int			init_main_struct(t_master **msh_m, char **envp, t_term *term_c);
int			init_select_struct(t_master **msh);
int			init_struct(t_master **msh_m);

/*
** from srcs/init_term.c
*/
int			init_term(t_term **term_conf);

/*
** from srcs/init_termcaps.c
*/
int			init_termcaps_values(t_term **key_terms);

#endif