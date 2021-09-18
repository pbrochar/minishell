/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_built_in.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 18:11:55 by pbrochar          #+#    #+#             */
/*   Updated: 2021/09/12 18:05:31 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_BUILT_IN_H
# define MSH_BUILT_IN_H

# include "minishell.h"

/*
** from srcs/built_in_cd.c
*/
int			built_in_cd(t_master *msh, char **arg);

/*
** from srcs/built_in_cd_error.c
*/
int			print_err_bad_folder(t_master *msh, char *folder, int err);
int			print_err_too_m_a(t_master *msh);

/*
** from srcs/built_in_cd_utils.c
*/
char		*cd_home_not_set(t_master *msh);
char		*cd_return_home(t_master *msh);
char		*cd_return_oldpwd(t_master *msh, char *arg);

/*
** from srcs/built_in_echo.c
*/
int			built_in_echo(t_master *msh, char **arg);

/*
** from srcs/built_in_env.c
*/
int			built_in_env(t_master *msh, char **arg);

/*
** from srcs/built_in_exit.c
*/
int			built_in_exit(t_master *msh, char **arg);

/*
** from srcs/built_in_exit_error.c
*/
void		print_err_num_arg(char *arg);

/*
** from srcs/built_in_export.c
*/
int			built_in_export(t_master *msh, char **arg);
int			var_already_exist(t_master *msh, char *arg);
void		change_env_value(t_master *msh, char *arg, int index);

/*
** from srcs/built_in_export_error.c
*/
void		print_err_bad_identifier(char *arg);

/*
** from srcs/built_in_pwd.c
*/
int			built_in_pwd(t_master *msh, char **arg);

/*
** from srcs/built_in_unset.c
*/
int			built_in_unset(t_master *msh, char **arg);

/*
** from srcs/built_in_utils.c
*/
int			is_built_in(t_master *msh, char *name);

#endif