/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 14:13:38 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/16 16:28:57 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pass_char(char *command, int *i, int op_pos, int c)
{
	(*i)++;
	while (command[*i] && *i < op_pos && command[*i] != c)
		(*i)++;
	(*i)++;
}

static void	manage_quote(char *command, int *i, int op_pos, int *nb_word)
{
	if (command[*i] == 34 && command[*i + 1])
	{
		pass_char(command, i, op_pos, 34);
		(*nb_word)++;
		return ;
	}
	if (command[*i] == 39 && command[*i + 1])
	{
		pass_char(command, i, op_pos, 39);
		(*nb_word)++;
		return ;
	}
}

static int	count_words(char *command, int op_pos)
{
	int	i;
	int	nb_word;

	i = 0;
	nb_word = 0;
	while (command[i] && i < op_pos)
	{
		if (command[i] == 34 || command[i] == 39)
			manage_quote(command, &i, op_pos, &nb_word);
		else if (!command[i + 1] || (command[i] == 32 && \
				command[i + 1] != 32) || (command[i + 1] == 32 && \
				!command[i + 1]))
			nb_word++;
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

	while (command[*i] && (*i) < op_pos && command[*i] == 32)
		(*i)++;
	j = *i;
	if (command[*i] == 34 && command[*i + 1])
		pass_char(command, i, op_pos, 34);
	else if (command[*i] == 39 && command[(*i) + 1])
		pass_char(command, i, op_pos, 39);
	else
	{
		while (command[*i] && command[*i] != 32 && *i < op_pos)
			(*i)++;
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
	char	**command_array;

	i = 0;
	j = 0;
	nb_word = count_words(command, op_pos);
	command_array = malloc(sizeof(char *) * (nb_word + 1));
	if (command_array == NULL)
		return (NULL);
	command_array[nb_word] = NULL;
	while (i < op_pos)
	{
		command_array[j] = return_word(command, op_pos, &i);
		j++;
	}
	return (command_array);
}
