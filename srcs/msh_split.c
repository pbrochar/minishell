/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 14:13:38 by pbrochar          #+#    #+#             */
/*   Updated: 2021/09/10 19:17:45 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(char *command, int op_pos)
{
	t_count_words	var;
	int				i;

	i = 0;
	init_var_count_words(&var, command);
	while (command[i] && ft_isspace(command[i]) && i < op_pos)
		i++;
	while (i < var.len && i < op_pos)
	{
		if (command[i] == '\'')
			change_quote('\'', &var.is_quote);
		else if (!var.is_quote && command[i] == '\\')
			i++;
		else if (command[i] == '\"')
			change_quote('\"', &var.is_quote);
		update_nb_words(&var, &i, command, op_pos);
	}
	return (var.nb_word);
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
