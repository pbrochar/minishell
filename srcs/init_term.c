/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 20:08:33 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/10 18:24:40 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_term(t_term **term_conf)
{
	*term_conf = malloc(sizeof(t_term));
	if (*term_conf == NULL)
		return (-1);
	if (tcgetattr(0, &((*term_conf)->term)) == -1)
		return (-1);
	if (tcgetattr(0, &((*term_conf)->backup)) == -1)
		return (-1);
	(*term_conf)->term.c_lflag &= ~(ECHO);
	(*term_conf)->term.c_lflag &= ~(ICANON);
	(*term_conf)->term.c_cc[VMIN] = 1;
	(*term_conf)->term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &((*term_conf)->term)) == -1)
		return (-1);
	if (tgetent(0, getenv("TERM")) == -1)
		return (-1);
	return (0);
}
