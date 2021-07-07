/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 13:12:14 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/07 13:19:57 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

static int	find_directory(t_master *msh, int i, DIR **directory)
{
	i++;
	*directory = opendir(msh->path[i]);
	return (i);
}

int	search_command(t_master *msh, char **arg)
{
	DIR				*directory;
	struct dirent	*files;
	int				i;

	i = 0;
	while (msh->path[i])
	{
		directory = opendir(msh->path[i]);
		while (msh->path[i] && directory == NULL)
			i = find_directory(msh, i, &directory);
		files = readdir(directory);
		while (files != NULL)
		{
			if (ft_strcmp(arg[0], files->d_name) == 0)
			{
				closedir(directory);
				return (i);
			}
			files = readdir(directory);
		}
		closedir(directory);
		i++;
	}
	return (-1);
}
