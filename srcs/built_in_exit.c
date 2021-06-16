/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 18:26:19 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/16 15:34:49 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_in_exit(t_master *msh, char **arg)
{
	(void)arg;
	tcsetattr(0, TCSANOW, &(msh->term->backup));
	free_main(msh);
	exit(0);
}
