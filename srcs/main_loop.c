/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 20:24:49 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/09 19:01:31 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	key_is_term(t_master *msh, char *buf)
{
	int	i;

	i = 0;
	while (msh->term->key_term[i])
	{
		if (ft_strncmp(buf, msh->term->key_term[i], ft_strlen(buf)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	is_new_line(char *buf, int ret)
{
	if (ret == 1 && buf[0] == '\n')
		return (1);
	return (-1);
}

int	is_char_to_print(char *buf, int ret)
{
	if (ret == 1 && ft_isprint(buf[0]) && buf[0] != '\n')
		return (1);
	return (-1);
}

void	sigint_handler(int sig)
{
	if (g_msh->commmand_running == true)
	{
		kill(g_msh->pid, sig);
		write(1, "\n", 1);
	}
	else
	{
		write(1, "^C", 2);
		write(1, "\n", 1);
		rest_struct_after_exec((t_master *)(g_msh));
		print_prompt((t_master *)(g_msh));
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

int	msh_main_loop(t_master *msh_m)
{
	char	buf[51];
	int		ret;
	int		key_term_v;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	print_prompt(msh_m);
	g_msh = msh_m;
	ret = read(STDIN_FILENO, buf, 50);
	while (ret > 0)
	{
		buf[ret] = '\0';
		if (buf[0] == 4 && msh_m->line_len == 0)
			eot_handler(msh_m);
		key_term_v = key_is_term(msh_m, buf);
		if (key_term_v != -1)
			msh_m->term->key_fct[key_term_v](msh_m);
		else if (is_new_line(buf, ret) == 1)
		{
			if (execute_line(msh_m) == -1)
				break ;
		}
		else if (is_char_to_print(buf, ret) == 1)
			print_char_management(msh_m, buf);
		ft_bzero(buf, 50);
		ret = read(STDIN_FILENO, buf, 50);
	}
	return (0);
}
