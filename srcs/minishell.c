/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 16:43:57 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/09 16:48:01 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_term		*term_c;
	t_master	*msh;

	(void)argc;
	(void)argv;
	msh = NULL;
	term_c = NULL;
	if (init_term(&term_c) == -1)
	{
		free_main(msh);
		return (-1);
	}
	if (init_key_terms(&term_c) == -1)
	{
		free_main(msh);
		return (-1);
	}
	if (init_msh_master_struct(&msh, envp, term_c) == -1)
	{
		free_main(msh);
		return (-1);
	}
	msh_main_loop(msh);
	tcsetattr(0, TCSANOW, &(term_c->backup));
	return (0);
}
