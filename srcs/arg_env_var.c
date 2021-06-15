/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 15:11:24 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/15 16:42:05 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len_without_var(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i - 1] != '\\')
		{
			i++;
			while (line[i] && ft_isalnum(line[i]))
				i++;
			if (!line[i])
				return (count);
		}
		i++;
		count++;
	}
	return (count);
}

static void	add_value_in_arg(char *temp, int *i, int *j, char **new_line)
{
	int	a;

	(*i)++;
	a = ft_strlen(temp);
	temp = ft_strinstr(*new_line, temp, *j);
	(*j) += a - 1;
	free(*new_line);
	*new_line = temp;
}

static char	*insert_env_value(t_master *msh, char *new_line, char *arg)
{
	int		i;
	int		j;
	int		a;
	char	*temp;

	i = 0;
	j = 0;
	a = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i - 1] != '\\')
		{
			temp = find_in_env(msh, &arg[i]);
			if (temp)
			{
				add_value_in_arg(temp, &i, &j, &new_line);
				while (arg[i + 1] && ft_isalnum(arg[i + 1]))
					i++;
			}
		}
		i++;
		j++;
	}
	free(arg);
	return (new_line);
}

static char	*create_new_line(char *arg)
{
	int		size;
	char	*new_line;

	size = len_without_var(arg) + 1;
	new_line = malloc(sizeof(char) * size);
	if (new_line == NULL)
		return (NULL);
	ft_bzero(new_line, size);
	return (new_line);
}

char	*manage_env_variable(t_master *msh, char *arg)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = 0;
	new_line = create_new_line(arg);
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i - 1] != '\\')
		{
			i++;
			while (arg[i] && ft_isalnum(arg[i]))
				i++;
		}
		else
		{
			if (arg[i] == '\\')
				i++;
			new_line[j] = arg[i];
			i++;
			j++;
		}
	}
	return (insert_env_value(msh, new_line, arg));
}
