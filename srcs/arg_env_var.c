/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 15:11:24 by pbrochar          #+#    #+#             */
/*   Updated: 2021/09/10 15:29:59 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_value_in_arg(char *temp, int pos, char **new_line)
{
	temp = ft_strinstr(*new_line, temp, pos);
	free(*new_line);
	*new_line = temp;
}

static char	*create_new_line(char **new_line)
{
	*new_line = malloc(sizeof(char) * 1);
	if (!(*new_line))
		return (NULL);
	ft_bzero(*new_line, 1);
	return (*new_line);
}

int	insert_env_value(t_master *msh, char **new_line, char *arg, int *pos)
{
	char	*temp;
	int		i;

	i = 1;
	temp = find_in_env(msh, &arg[0]);
	if (temp)
	{
		add_value_in_arg(temp, *pos, new_line);
		*pos += ft_strlen(temp);
	}
	if (arg[i] == '?')
		return (2);
	while (&arg[i] && (ft_isalnum(arg[i]) || arg[i] == '_'))
		i++;
	return (i);
}

static void	fill_new_line(char **new_line, int *j, int i, char *arg)
{
	*new_line = ft_mem_exp(*new_line, sizeof(char) * ((*j) + 1), \
						sizeof(char) * ((*j) + 2));
	(*new_line)[*j] = arg[i];
	(*j)++;
}

char	*manage_env_variable(t_master *msh, char *arg)
{
	int		i;
	int		j;
	int		size;
	char	*new_line;

	i = -1;
	j = 0;
	size = ft_strlen(arg);
	if (create_new_line(&new_line) == NULL)
		return (NULL);
	while (++i < size)
	{
		if (arg[i] == '\\')
			i++;
		else if (arg[i] == '$')
		{
			i += (insert_env_value(msh, &new_line, &arg[i], &j) - 1);
			continue ;
		}
		fill_new_line(&new_line, &j, i, arg);
	}
	free(arg);
	return (new_line);
}
