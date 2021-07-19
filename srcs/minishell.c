/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 16:43:57 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/19 16:10:37 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sig)
{
	((t_master *)g_msh)->sigint_signal = true;
	if (g_msh->commmand_running == true)
	{
		kill(g_msh->pid, sig);
		write(1, "\n", 1);
	}
	else if (g_msh->heredoc_running == false)
	{
		write(1, "^C", 2);
		write(1, "\n", 1);
		rest_struct_after_exec((t_master *)(g_msh));
		print_prompt((t_master *)(g_msh));
		((t_master *)g_msh)->sigint_signal = false;
	}
	if (g_msh->heredoc_running == true)
	{
		write(1, "^C", 2);
		write(1, "\n", 1);
		g_msh->term->term.c_cc[VMIN] = 0;
		g_msh->term->term.c_cc[VTIME] = 1;
		tcsetattr(0, TCSANOW, &((g_msh->term)->term));
	}
}

void	sigquit_handler(int sig)
{
	(void)sig;
	return ;
}

void	eot_handler(t_master *msh)
{
	write(1, "exit\n", 5);
	built_in_exit(msh, NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_term		*term_c;
	t_master	*msh;

	(void)argc;
	(void)argv;
	msh = NULL;
	term_c = NULL;
	if (init_term(&term_c) == -1 || \
		init_key_terms(&term_c) == -1)
	{
		tcsetattr(0, TCSANOW, &(term_c->backup));
		free(term_c);
		return (-1);
	}
	if (init_msh_master_struct(&msh, envp, term_c) == -1)
	{
		free_main(msh);
		return (-1);
	}
	g_msh = msh;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	msh_main_loop(msh);
	tcsetattr(0, TCSANOW, &(term_c->backup));
	return (0);
}
