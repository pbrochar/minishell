/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 15:48:33 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/18 15:23:42 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		remove_quote_size(char *line, int quote)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while(line[i])
	{
		if (line[i] == '\\')
		{
			i += 2;
			count += 2;
			if (!line[i])
				break ;
		}
		if (line[i] == quote)
			i++;
		if (!line[i])
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

char	**manage_arg(t_master *msh, char **arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (arg);
	while (arg[i])
	{
		remove_quote(arg, i, 34);
		arg[i] = manage_env_variable(msh, arg[i]);
		i++;
	}
	return (arg);
}
