/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 15:48:33 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/19 19:25:15 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		remove_quote_size(char *line, int quote)
{
	int	i;
	int	count;
	int	size;

	if (!line)
		return (-1);
	i = 0;
	size = ft_strlen(line);
	count = 0;
	while(i < size)
	{
		if (line[i] == '\\')
		{
			i += 2;
			count += 2;
			if (i > size)
				break ;
		}
		if (line[i] && line[i] == quote)
		{
			i++;
		}
		if (i > size)
			break ;
		i++;
		count++;
	}
	return (count);
}

void	remove_quote(char **arg, int i, int quote)
{
	int		size;
	char	*temp;
	int		j;
	int		a;

	if (!arg || !*arg)
		return ;
	j = 0;
	a = 0;
	size = remove_quote_size(arg[i], quote);
	temp = malloc(sizeof(char) * (size + 1));
	if (temp == NULL)
		return ;
	ft_bzero(temp, size + 1);
	while (arg[i][j])
	{
		if (arg[i][j] == '\\')
		{
			temp[a] = arg[i][j];
			temp[++a] = arg[i][++j];
		}
		if (arg[i][j] == quote)
			j++;
		if (!arg[i][j] || a >= size)
			break ;
		temp[a] = arg[i][j];
		j++;
		a++;
	}
	free(arg[i]);
	arg[i] = temp;
}

char	*parser(t_master *msh, char *line)
{
	int	i;
	int	j;
	int	size;
	char *new_line;
	bool simple_quote_flag;
	
	simple_quote_flag = false;
	i = -1;
	j = 0;
	size = ft_strlen(line);
	new_line = malloc(sizeof(char) * 1);
	if (!new_line)
		return (NULL);
	ft_bzero(new_line, 1);
	while (++i < size)
	{
		if (line[i] == '\'')
		{
			simple_quote_flag = !simple_quote_flag;
			continue ;
		}
		else if (!simple_quote_flag && line[i] == '\\')
			i++;
		else if (!simple_quote_flag && line[i] == '\"')
			continue ;
		else if (!simple_quote_flag && line[i] == '$')
		{
			i += (insert_env_value(msh, &new_line, &line[i], &j) - 1);
			continue ;
		}
		new_line = ft_mem_exp(new_line, sizeof(char) * (j + 1), sizeof(char) * (j + 2));
		new_line[j] = line[i];
		j++;
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
