/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 15:11:24 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/19 20:17:37 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static int	len_without_var(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if ((line[i] == '$' && i == 0) || \
			(i > 0 && line[i] == '$' && line[i - 1] != '\\'))
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
}*/

static void	add_value_in_arg(char *temp, int pos, char **new_line)
{
	temp = ft_strinstr(*new_line, temp, pos);
	free(*new_line);
	*new_line = temp;
}

int insert_env_value(t_master *msh, char **new_line, char *arg, int *pos)
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
/*
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
*/
char	*manage_env_variable(t_master *msh, char *arg)
{
	int	i;
	int	j;
	int	size;
	char *new_line;
	
	i = -1;
	j = 0;
	size = ft_strlen(arg);
	new_line = malloc(sizeof(char) * 1);
	if (!new_line)
		return (NULL);
	ft_bzero(new_line, 1);
	while (++i < size)
	{
		if (arg[i] == '\\')
			i++;
		else if (arg[i] == '$')
		{
			i += (insert_env_value(msh, &new_line, &arg[i], &j) - 1);
			continue ;
		}
		new_line = ft_mem_exp(new_line, sizeof(char) * (j + 1), sizeof(char) * (j + 2));
		new_line[j] = arg[i];
		j++;
	}
	free(arg);
	return (new_line);
}
