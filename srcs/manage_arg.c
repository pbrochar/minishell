/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 15:48:33 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/07 18:11:16 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *env_value(char *env_var)
{
	int	i;

	i = 0;
	while (env_var[i] && env_var[i] != '=')
		i++;
	i++;
	if (!env_var[i])
		return (NULL);
	return (&env_var[i]);
}

char *find_in_env(t_master *msh, char *var)
{
	int		i;
	int		size;
	char	buf[4096];

	i = 1;
	while (var[i] && ft_isalnum(var[i]))
		i++;
	ft_strlcpy(buf, &var[1], i);
	size = ft_strlen(buf);
	i = 0;
	while (msh->envp[i])
	{
		if (ft_strncmp(buf, msh->envp[i], size) == 0 && \
			msh->envp[i][size] == '=')
			return (env_value(msh->envp[i]));
		i++;
	}
	return (NULL);
}

int		nb_env_var(char *arg)
{
	int	i;
	int count;

	i = 0;
	count = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
			count++;
		i++;
	}
	return (count);
}

int	len_without_var(char *line)
{
	int	i;
	int count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
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

int	len_all_var_in_line(t_master *msh, char *line)
{
	int		i;
	char	*temp;
	int		size;

	i = 0;
	size = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			temp = find_in_env(msh, &line[i]);
			if (temp != NULL)
				size += ft_strlen(temp);
		}
		i++;
	}
	return (size);
}

char	*manage_dollar(t_master *msh, char *arg)
{
	int	i;
	int j;
	int	size;
	char	*new_line;
	char *temp;
	
	i = 0;
	j = 0;
	size = len_without_var(arg) + 1;
	new_line = malloc(sizeof(char) * size);
	if (new_line == NULL)
		return (NULL);
	ft_bzero(new_line, size);
	while(arg[i])
	{
		if (arg[i] == '$')
		{
			i++;
			while (arg[i] && ft_isalnum(arg[i]))
				i++;
			if (!arg[i])
				break ;
		}
		else
		{
			new_line[j] = arg[i];
			i++;
			j++;
		}
	}
	i = 0;
	j = 0;
	int a = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			temp = find_in_env(msh, &arg[i]);
			if (temp)
			{
				i++;
				a = ft_strlen(temp);
				temp = ft_strinstr(new_line, temp, j);
				free(new_line);
				new_line = temp;
				j += a - 1;
				while(arg[i + 1] && ft_isalnum(arg[i + 1]))
					i++;
			}
		}
		i++;
		j++;
	}
	return (new_line);
}

void	manage_single_quote(char **arg, int i)
{
	int j;
	char *temp;

	j = ft_strlen(&arg[i][1]);
	temp = malloc(sizeof(char) * j);
	if (temp == NULL)
		return ;
	ft_strlcpy(temp, &arg[i][1], j);
	free(arg[i]);
	arg[i] = temp;
}

void	manage_double_quote(t_master *msh, char **arg, int i)
{
	int		j;
	int		count;
//	char	*temp;
	(void)msh;
	j = 0;
	count = 0;
	while (arg[i][j])
	{
		if (arg[i][j] == '$')
			count++;
		j++;
	}
	printf("%d\n", count);
}

char **manage_arg(t_master *msh, char **arg)
{
	int	i;
	
	i = 1;
	while (arg[i])
	{
		if (arg[i][0] == 34)
			manage_double_quote(msh, arg, i);
		else if (arg[i][0] == 39)
			manage_single_quote(arg, i);
		else
			arg[i] = manage_dollar(msh, arg[i]);
		i++;
	}
	return (arg);
}