/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 14:13:38 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/18 14:46:42 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(char *command, int op_pos)
{
	int	i;
	int	nb_word;
	int	len;

	i = 0;
	nb_word = 0;
	len = ft_strlen(command);
	while (command[i] && i < op_pos)
	{
		while (command[i] && ft_isspace(command[i]) && i < op_pos)
			i++;
		if (command[i] == '\\')
			i += 2;
		if (command[i] == '\'')
		{
			i++;
			while (command[i] != '\'')
				i++;
			i++;
		}
		if (command[i] == '\"')
		{
			i++;
			while (command[i] != '\"')
			{
				if (command[i] == '\\')
					i++;
				i++;
			}
			i++;
		}
		while (command[i] && ft_isalnum(command[i]) && command[i] != 32)
			i++;
		if (command[i] == 32 || !command[i])
			nb_word++;
		if (i >= op_pos || i > len)
			break ;
		i++;
	}
	if (nb_word == 0)
		nb_word++;
	return (nb_word);
}

static char	*return_word(char *command, int op_pos, int *i)
{
	int		j;
	char	*word;

	while (command[*i] && ft_isspace(command[*i]) && *i < op_pos)
		(*i)++;
	j = *i;
	if (command[*i] == '\'')
	{
		(*i)++;
		while (command[*i] != '\'')
			(*i)++;
		(*i)++;
	}
	if (command[*i] == '\"')
	{
		(*i)++;
		while (command[*i] != '\"')
		{
			if (command[*i] == '\\')
			{
				(*i) += 2;
				continue ;
			}
			(*i)++;
		}
	}
	while (command[*i] && !ft_isspace(command[*i]) && *i < op_pos)
		(*i)++;
	word = malloc(sizeof(char *) * ((*i) - j + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, &command[j], ((*i) - j + 1));
	(*i)++;
	return (word);
}

char	**msh_split_command(char *command, int op_pos)
{
	int		i;
	int		j;
	int		nb_word;
	int		len;
	char	**command_array;

	i = 0;
	j = 0;
	len = ft_strlen(command);
	nb_word = count_words(command, op_pos);
	command_array = malloc(sizeof(char *) * (nb_word + 1));
	if (command_array == NULL)
		return (NULL);
	command_array[nb_word] = NULL;
	while (i < op_pos)
	{
		command_array[j] = return_word(command, op_pos, &i);
		j++;
		if (i > len)
			break ;
	}
	return (command_array);
}
