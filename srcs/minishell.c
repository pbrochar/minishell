/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 16:43:57 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/17 22:12:11 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "msh_structs.h"
#include "colors.h"
#include "msh_define.h"

void	print_prompt(t_master *msh_m)
{
	char buf[50];
	getcwd(buf, 50);
	int i;
	i = ft_strlen(buf) - 1;
	while (i != 0 && buf[i] != '/')
		i--;
	if (buf[i + 1] && buf[i] == '/')
		i++;
	msh_m->prompt->dir = ft_strdup(&buf[i]);

	write(1, TEXT_GREEN, 7);
	write(1, msh_m->prompt->user, msh_m->prompt->user_len);
	write(1, TEXT_NORMAL, 4);
	write(1, "@", 1);
	write(1, TEXT_CYAN, 7);
	write(1, msh_m->prompt->dir, msh_m->prompt->dir_len);
	write(1, TEXT_NORMAL, 4);
	write(1, "[n] ", 4);
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
	//char *toto[] = {"/bin/ls", "--color=tty", NULL}
	/*
	if (ft_strncmp(msh->line, "cd", 2) == 0)
		built_in_cd(msh, "..");
	int pid_ls;
	if (ft_strncmp(msh->line, "ls", 2) == 0)
	{
		if (!(pid_ls = fork()))
			execve("/bin/ls", toto, msh->envp);
		else
			waitpid(pid_ls, NULL, 0);
	}
	waitpid(-1, NULL, 0);*/
	if (msh->line_len == 0)
	{
		write(1, "\n", 1);
		print_prompt(msh);
		return (0);
	}
	if (ft_strncmp(msh->line, "exit", 4) == 0)
		return (-1);
	write(1, "\n", 1);
	history_management(msh);
	print_prompt(msh);
	if (msh->line)
		free(msh->line);
	msh->line = NULL;
	msh->line_len = 0;
	msh->nb_line = 0;
	msh->curr_line = 0;
	msh->is_multiline = 0;
	reset_curs_pos(msh);
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
	while (i > msh->curs_pos->curs_pos_rel)
	{
		msh->line[i] = msh->line[i - 1];
		i--;
	}
	msh->line[msh->curs_pos->curs_pos_rel] = c;
	msh->line[msh->line_len] = '\0';
}

void	update_line_front(t_master *msh)
{
	int n;
	
	n = msh->nb_line - (msh->curs_pos->curs_pos_abs / msh->res_x);
	if (n == 0)
		return ;
	save_curs_pos(msh);
	mv_curs_end(msh);
	if (msh->curs_pos->curs_pos_abs % msh->res_x == 0)
	{
		tputs(tgetstr("sf", NULL), 1, ft_putchar);
		msh->nb_line++;
		n++;
	}
	while (n > 0)
	{
		mv_curs_abs(msh, 0, msh->curs_pos->curs_pos_abs / msh->res_x);
		set_curs_pos(msh, msh->curs_pos->curs_pos_abs - (msh->curs_pos->curs_pos_abs % msh->res_x));
		write(1, &msh->line[msh->curs_pos->curs_pos_rel], 1);
		tputs(tgetstr("up", NULL), 1, ft_putchar);
		set_curs_pos(msh, (msh->curs_pos->curs_pos_abs - msh->res_x) + 1);
		n--;
	}
	mv_curs_abs(msh, msh->save_curs_pos->curs_pos_abs % msh->res_x, \
				msh->save_curs_pos->curs_pos_abs / msh->res_x);
	rest_curs_pos(msh);
}

int print_char_management(t_master *msh, char *buf)
{
	if (msh->curs_pos->curs_pos_rel < msh->line_len)
	{
		tputs(msh->term->ipt_mode, 1, ft_putchar);
		msh->line = ft_mem_exp(msh->line, msh->line_len, msh->line_len + 1);
		add_in_line(msh, buf[0]);
		msh->line_len++;
		update_line_front(msh);
		write(1, buf, 1);
		tputs(msh->term->lve_ipt_mode, 1, ft_putchar);
		inc_curs_pos(msh);
	}
	else
	{
		write(1, buf, 1);
		msh->line = ft_mem_exp(msh->line, msh->line_len, msh->line_len + 2);
		msh->line_len++;
		msh->line[msh->line_len - 1] = buf[0];
		msh->line[msh->line_len] = '\0';
		inc_curs_pos(msh);
	}
	if (msh->curs_pos->curs_pos_abs % (msh->res_x) == 0)
	{
		write(1, "\n", 1);
		msh->nb_line++;
	}
	return (0);
}

int	msh_main_loop(t_master *msh_m)
{
	char	buf[51];
	int		ret;
	int		key_term_v;

	print_prompt(msh_m);
	while ((ret = read(0, buf, 50)) > 0)
	{
		buf[ret] = '\0';
		if ((key_term_v = key_is_term(msh_m, buf)) != -1)
			msh_m->term->key_fct[key_term_v](msh_m);
		if ((int)buf[0] == 27 && buf[1] == '\n')
		{
			msh_m->is_multiline = 1;
			print_char_management(msh_m, &buf[1]);
			msh_m->nb_line++;
			msh_m->curr_line++;
		}
		else if (is_new_line(buf, ret) == 1)
		{
			if (execute_line(msh_m) == -1)
			{
				write(1, "\n", 1);
				break;
			}
		}
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
