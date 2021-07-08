/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 20:24:49 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/08 20:35:16 by pbrochar         ###   ########.fr       */
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

void	signal_fct(int i)
{
	printf("coucou : %d\n", i);
}

int	msh_main_loop(t_master *msh_m)
{
	char	buf[51];
	int		ret;
	int		key_term_v;

	signal(SIGINT, signal_fct);
	print_prompt(msh_m);
	ret = read(STDIN_FILENO, buf, 50);
	while (ret > 0)
	{
		buf[ret] = '\0';
		/*if (buf[0] == 3)
		{
			write(1, "^C", 2);
			write(1, "\n", 1);
			free(msh_m->line);
			msh_m->line = NULL;
			print_prompt(msh_m);
		}*/
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
