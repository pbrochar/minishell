/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 16:43:57 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/05 15:36:05 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "msh_structs.h"
#include "colors.h"
#include "define_msh.h"

void	print_prompt(t_master *msh_m)
{
	write(1, TEXT_GREEN, 7);
	write(1, msh_m->prompt->user, msh_m->prompt->user_len);
	write(1, TEXT_NORMAL, 4);
	write(1, "@", 1);
	write(1, TEXT_CYAN, 7);
	write(1, msh_m->prompt->dir, msh_m->prompt->dir_len);
	write(1, TEXT_NORMAL, 4);
	write(1, " ", 1);
}

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

int	execute_line(t_master *msh)
{
	history_management(msh);
	write(1, "\n", 1);
	print_prompt(msh);
	free(msh->line);
	msh->line = malloc(sizeof(char));
	if (msh->line == NULL)
		return (-1);
	ft_bzero(msh->line, 1);
	msh->line_len = 0;
	msh->curs_pos = 0;
	return (0);
}

int	is_char_to_print(char *buf, int ret)
{
	if (ret == 1 && ft_isprint(buf[0]) && buf[0] != '\n')
		return (1);
	return (-1);
}

void add_in_line(t_master *msh, char c)
{
	int i;

	i = msh->line_len;
	while (i > msh->curs_pos)
	{
		msh->line[i] = msh->line[i - 1];
		i--;
	}
	msh->line[msh->curs_pos] = c;
}

int print_char_management(t_master *msh, char *buf)
{
	if (msh->curs_pos < msh->line_len)
	{
		tputs(msh->term->ipt_mode, 1, ft_putchar);
		msh->line = ft_mem_exp(msh->line, msh->line_len, msh->line_len + 1);
		add_in_line(msh, buf[0]);
		msh->line_len++;
		write(1, buf, 1);
		tputs(msh->term->lve_ipt_mode, 1, ft_putchar);
		msh->curs_pos++;
	}
	else
	{
		write(1, buf, 1);
		msh->line = ft_mem_exp(msh->line, msh->line_len, msh->line_len + 1);
		msh->line = ft_strcat(msh->line, buf);
		msh->line_len++;
		msh->curs_pos++;
	}
	return (0);
}

int	msh_main_loop(t_master *msh_m)
{
	char	buf[51];
	int		ret;
	int		key_term_v;
	void	(*key_fct[NB_KEY])(t_master *) = {&mv_curs_left, &mv_curs_right, 
										&browse_history_back, &browse_history_front,
										&mv_curs_home, &mv_curs_end, &delete_key_display,
										&mv_curs_left_word, &mv_curs_right_word , NULL};
	
	print_prompt(msh_m);
	while ((ret = read(0, buf, 50)) > 0)
	{
		buf[ret] = '\0';
		if ((key_term_v = key_is_term(msh_m, buf)) != -1)
			key_fct[key_term_v](msh_m);
		else if (is_new_line(buf, ret) == 1)
			execute_line(msh_m);
		else if (is_char_to_print(buf, ret) == 1)
			print_char_management(msh_m, buf);
		ft_bzero(buf, 50);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_term		*term_c;
	t_master	*msh_m;
	
	(void)argc;
	(void)argv;
	msh_m = NULL;
	term_c = NULL;
	init_term(&term_c);
	init_key_terms(&term_c);
	init_msh_master_struct(&msh_m, envp, term_c);
	msh_main_loop(msh_m);
	tcsetattr(0, TCSANOW, &(term_c->backup));
	return (0);
}
