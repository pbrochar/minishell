/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_built_in.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 17:42:02 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/05 17:42:11 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSH_BUILT_IN_H
# define MSH_BUILT_IN_H

# include "msh_structs.h"

/*
** from srcs/built_in_cd.c
*/
int			built_in_cd(t_master *msh, char **arg);

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
** from srcs/built_in_export.c
*/
int			built_in_export(t_master *msh, char **arg);
int			var_already_exist(t_master *msh, char *arg);

/*
** from srcs/built_in_pwd.c
*/
int			built_in_pwd(t_master *msh, char **arg);

/*
** from srcs/built_in_unset.c
*/
int			built_in_unset(t_master *msh, char **arg);

#endif