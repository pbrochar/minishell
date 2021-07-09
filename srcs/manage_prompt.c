/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 15:25:51 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/09 16:17:30 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "colors.h"

void	update_prompt_values(t_master *msh)
{
	char	buf[51];
	int		i;

	getcwd(buf, 50);
	i = ft_strlen(buf) - 1;
	while (i != 0 && buf[i] != '/')
		i--;
	if (buf[i + 1] && buf[i] == '/')
		i++;
	free(msh->prompt->dir);
	msh->prompt->dir = ft_strdup(&buf[i]);
	msh->prompt->dir_len = ft_strlen(msh->prompt->dir);
	msh->prompt_len = msh->prompt->user_len + msh->prompt->dir_len + 5;
}

void	print_prompt(t_master *msh)
{
	write(1, TEXT_GREEN, 7);
	write(1, msh->prompt->user, msh->prompt->user_len);
	write(1, TEXT_NORMAL, 4);
	write(1, "@", 1);
	write(1, TEXT_CYAN, 7);
	write(1, msh->prompt->dir, msh->prompt->dir_len);
	write(1, TEXT_NORMAL, 4);
	write(1, "[n] ", 4);
}
