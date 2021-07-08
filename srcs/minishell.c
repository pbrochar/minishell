/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 16:43:57 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/08 19:31:34 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "msh_structs.h"
#include "colors.h"
#include "msh_define.h"

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

int	is_built_in(t_master *msh, char *name)
{
	int	i;

	i = 0;
	if (!name)
		return (-1);
	while (msh->built_in->built_in_list[i])
	{
		if (ft_strcmp(name, msh->built_in->built_in_list[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void rest_struct_after_exec(t_master *msh)
{
	if (msh->line)
		free(msh->line);
	free_command_arg(msh);
	msh->line = NULL;
	msh->line_len = 0;
	msh->nb_line = 0;
	msh->commands = NULL;
	msh->save_commands_list = NULL;
	reset_curs_pos(msh);	
}
void	print_list(t_master *msh)
{
	t_list *temp;
	temp = msh->commands;
	while (temp)
	{
		printf("%d\n", ((t_command *)temp->content)->std_out);
		temp = temp->next;
	}
}
void	execute_list(t_master *msh)
{
//	print_list(msh);
	msh->commands = msh->commands->next;
	while (msh->commands)
	{
		((t_command *)msh->commands->content)->op_fct(msh);
		if (((t_command *)msh->commands->content)->op != NULL && \
			((t_command *)msh->commands->content)->op[0] == '\0')
			return ;
		msh->commands = msh->commands->next;
		while (((t_command *)msh->commands->content)->op == NULL)
			msh->commands = msh->commands->next;
	}
}

int	execute_line(t_master *msh)
{
	update_prompt_values(msh);
	write(1, "\n", 1);
	if (msh->line_len != 0)
	{
		msh_split_ops(msh);
		history_management(msh);
		execute_list(msh);
	}
	print_prompt(msh);
	rest_struct_after_exec(msh);
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
	msh->line[msh->line_len + 1] = '\0';
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
		tputs(msh->term->scroll_line_up, 1, ft_putchar);
		msh->nb_line++;
		n++;
	}
	while (n > 0)
	{
		mv_curs_abs(msh, 0, msh->curs_pos->curs_pos_abs / msh->res_x);
		set_curs_pos(msh, msh->curs_pos->curs_pos_abs - (msh->curs_pos->curs_pos_abs % msh->res_x));
		write(1, &msh->line[msh->curs_pos->curs_pos_rel], 1);
		tputs(msh->term->up_curs, 1, ft_putchar);
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
		msh->line = ft_mem_exp(msh->line, sizeof(char) * msh->line_len, \
			sizeof(char) * msh->line_len + 2);
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
		msh->line = ft_mem_exp(msh->line, sizeof(char) * msh->line_len, \
			sizeof(char) * msh->line_len + 2);
		msh->line_len++;
		msh->line[msh->line_len - 1] = buf[0];
		msh->line[msh->line_len] = '\0';
		inc_curs_pos(msh);
	}
	if (msh->curs_pos->curs_pos_abs % (msh->res_x) == 0)
		write(1, "\n", 1);
	msh->nb_line = (msh->line_len + msh->prompt_len) / msh->res_x;
	return (0);
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
	while ((ret = read(0, buf, 50)) > 0)
	{
		buf[ret] = '\0';
		if (buf[0] == 3)
		{
			write(1, "^C", 2);
			write(1, "\n", 1);
			free(msh_m->line);
			msh_m->line = NULL;
			print_prompt(msh_m);
		}
		else if ((key_term_v = key_is_term(msh_m, buf)) != -1)
			msh_m->term->key_fct[key_term_v](msh_m);
		else if (is_new_line(buf, ret) == 1)
		{
			if (execute_line(msh_m) == -1)
				break;
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
	t_master	*msh;
	
	(void)argc;
	(void)argv;
	msh = NULL;
	term_c = NULL;
	if (init_term(&term_c) == -1)
		return (-1);
	init_key_terms(&term_c);
	init_msh_master_struct(&msh, envp, term_c);
	msh_main_loop(msh);
	tcsetattr(0, TCSANOW, &(term_c->backup));
	return (0);
}
