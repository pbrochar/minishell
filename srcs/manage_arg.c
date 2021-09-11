/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 15:48:33 by pbrochar          #+#    #+#             */
/*   Updated: 2021/09/11 16:56:35 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_parser_var(t_parser *var, char *line, char **new_line, int *i)
{
	var->simple_quote_flag = false;
	var->double_quote_flag = false;
	*i = -1;
	var->j = 0;
	var->size = ft_strlen(line);
	*new_line = malloc(sizeof(char) * 1);
	if (!*new_line)
		return (-1);
	ft_bzero(*new_line, 1);
	return (0);
}

static void	update_new_line(char **new_line, int i, int *j, char *line)
{
	*new_line = ft_mem_exp(*new_line, sizeof(char) * ((*j) + 1), \
							sizeof(char) * ((*j) + 2));
	(*new_line)[*j] = line[i];
	(*j)++;
}

char	*parser(t_master *msh, char *line)
{
	t_parser	var;
	int			i;
	char		*new_line;

	init_parser_var(&var, line, &new_line, &i);
	while (++i < var.size)
	{
		if (!var.double_quote_flag && line[i] == '\'')
		{
			var.simple_quote_flag = !var.simple_quote_flag;
			continue ;
		}
		else if (!var.simple_quote_flag && line[i] == '\\')
		{
			if (line[i + 1] && (line[i + 1] == '\\' \
				|| line[i + 1] == '\"' || line[i + 1] == '$' || (is_operand(line, i + 1) != -1)))
				i++;
		}
		else if (!var.simple_quote_flag && line[i] == '\"')
		{
			var.double_quote_flag = !var.double_quote_flag;
			continue ;
		}
		else if (!var.simple_quote_flag && line[i] == '$')
		{
			i += (insert_env_value(msh, &new_line, &line[i], &var.j) - 1);
			continue ;
		}
		update_new_line(&new_line, i, &var.j, line);
	}
	free(line);
	return (new_line);
}

char	**manage_arg(t_master *msh, char **arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (arg);
	while (arg[i])
	{
		arg[i] = parser(msh, arg[i]);
		i++;
	}
	return (arg);
}
