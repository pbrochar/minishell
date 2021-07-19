/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 14:13:38 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/19 22:07:21 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(char *command, int op_pos)
{
	int	i;
	int	nb_word;
	int	len;
	int is_quote;

	i = 0;
	nb_word = 0;
	len = ft_strlen(command);
	is_quote = 0;
	while (command[i] && ft_isspace(command[i]) && i < op_pos)
		i++;
	while (i < len && i < op_pos)
	{
		if (command[i] == '\'')
		{
			if (is_quote == '\'')
				is_quote = 0;
			else
				is_quote = '\'';
		}
		else if (!is_quote && command[i] == '\\')
			i++;
		else if (!is_quote && command[i] == '\"')
		{
			if (is_quote == '\"')
				is_quote = 0;
			else
				is_quote = '\"';
		}
		if (!is_quote && ft_isspace(command[i]))
		{
			nb_word++;
			while (ft_isspace(command[i]))
				i++;
		}
		else
		{
			i++;
			if (!command[i]) {
				nb_word++;
			}			
		}
	}
	return (nb_word);
}

static char	*return_word(char *command, int op_pos, int *i)
{
	int		j;
	int		is_quote;
	char	*word;

	is_quote = 0;
	while (command[*i] && ft_isspace(command[*i]) && *i < op_pos)
		(*i)++;
	j = *i;
	(*i)--;
	while (command[++(*i)] && (is_quote || !ft_isspace(command[*i])) && *i < op_pos)
	{
		if (command[*i] == '\'')
		{
			if (is_quote == '\'')
				is_quote = 0;
			else
				is_quote = '\'';
			continue ;
		}
		else if (!is_quote && command[*i] == '\\')
			(*i)++;
		else if (command[*i] == '\"')
		{
			if (is_quote == '\"')
				is_quote = 0;
			else
				is_quote = '\"';
			continue ;
		}
	}
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
	while (j < nb_word)
	{
		command_array[j] = return_word(command, op_pos, &i);
		if (i >= op_pos)
			break ;
		j++;
	}
	return (command_array);
}
