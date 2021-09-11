/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_split_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:10:32 by pbrochar          #+#    #+#             */
/*   Updated: 2021/09/11 15:40:39 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_word(int *i, int j, char *command)
{
	char	*word;

	word = malloc(sizeof(char *) * ((*i) - j + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, &command[j], ((*i) - j + 1));
	(*i)++;
	printf("word = %s\n", word);
	return (word);
}

char	*return_word(char *command, int op_pos, int *i)
{
	int		j;
	int		is_quote;

	is_quote = 0;
	while (command[*i] && ft_isspace(command[*i]) && *i < op_pos)
		(*i)++;
	j = *i;
	(*i)--;
	while (command[++(*i)] && \
		(is_quote || !ft_isspace(command[*i])) && *i < op_pos)
	{
		if (command[*i] == '\'')
		{
			change_quote('\'', &is_quote);
			continue ;
		}
		else if (!is_quote && command[*i] == '\\')
			(*i)++;
		else if (command[*i] == '\"')
		{
			change_quote('\"', &is_quote);
			continue ;
		}
	}
	return (create_word(i, j, command));
}

void	change_quote(int quote_type, int *is_quote)
{
	if (*is_quote == quote_type)
		*is_quote = 0;
	else
		*is_quote = quote_type;
}

void	init_var_count_words(t_count_words *var, char *command)
{
	var->nb_word = 0;
	var->len = ft_strlen(command);
	var->is_quote = 0;
}

void	update_nb_words(t_count_words *var, int *i, char *com, int op_pos)
{
	if (!var->is_quote && ft_isspace(com[*i]))
	{
		var->nb_word++;
		while (ft_isspace(com[*i]))
			(*i)++;
	}
	else
	{
		(*i)++;
		if (!com[*i] || *i >= op_pos)
			var->nb_word++;
	}
}
