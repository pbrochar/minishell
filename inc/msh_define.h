/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_define.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 20:41:42 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/05 13:55:22 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_MSH_H
# define DEFINE_MSH_H

# define NB_BUILT_IN 8
# define BI_CD "cd"
# define BI_ECHO "echo"
# define BI_ENV "env"
# define BI_EXIT "exit"
# define BI_EXPORT "export"
# define BI_PWD "pwd"
# define BI_UNSET "unset"

# define NB_BUFFER 10

/*
** define for main loop key
*/
# define NB_KEY 16
# define A_KEY_LEFT 0
# define A_KEY_RIGHT 1
# define A_KEY_UP 2
# define A_KEY_DOWN 3
# define A_KEY_HOME 4
# define A_KEY_END 5
# define A_KEY_BACK 6
# define A_CTRL_L_A 7
# define A_CTRL_R_A 8
# define A_CTRL_U_A 9
# define A_CTRL_D_A 10
# define A_CTRL_H_A 11
# define A_INSERT_A 12
# define A_KEY_PG_UP 13
# define A_KEY_PG_DW 14

/*
** define for select mode loop
*/
# define NB_KEY_SELECT 14
# define S_KEY_LEFT 0
# define S_KEY_RIGHT 1
# define S_KEY_HOME 2
# define S_KEY_END 3
# define S_KEY_BACK 4
# define S_CTRL_L_A 5
# define S_CTRL_R_A 6
# define S_CTRL_H_A 7
# define S_KEY_C 8
# define S_KEY_A 9
# define S_KEY_X 10
# define S_KEY_B 11
# define S_KEY_P 12


# define CTRL_LEFT_ARROW "\e[1;5D"
# define CTRL_RIGHT_ARROW "\e[1;5C"
# define CTRL_UP_ARROW "\e[1;5A"
# define CTRL_DOWN_ARROW "\e[1;5B"
# define CTRL_HOME "\e[1;5H"
# define INSERT "\e[2~"
# define PG_UP "\e[5~"
# define PG_DOWN "\e[6~"
# define KEY_A "a"
# define KEY_B "b"
# define KEY_C "c"
# define KEY_X "x"
# define KEY_P "p"

#endif