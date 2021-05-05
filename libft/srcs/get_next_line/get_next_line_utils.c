/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 14:09:43 by pbrochar          #+#    #+#             */
/*   Updated: 2021/04/19 15:42:25 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

size_t		ft_strclen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i + 1);
}

int			ft_strccat(t_gnl *gnl, char **dst)
{
	size_t	i;
	size_t	a;

	i = 0;
	a = gnl->pos;
	*dst = ft_char_realloc(*dst, ft_strclen(&(gnl->buf[a]))
						+ ft_strclen(*dst));
	while ((*dst)[i])
		i++;
	while (gnl->buf[a] && gnl->buf[a] != '\n')
	{
		(*dst)[i] = gnl->buf[a];
		i++;
		a++;
	}
	(*dst)[i] = '\0';
	if (gnl->buf[a] == '\n')
	{
		gnl->pos = a + 1;
		return (1);
	}
	gnl->pos = 0;
	return (0);
}

char		*ft_char_realloc(char *src, size_t newsize)
{
	int		i;
	char	*new;

	if (!(new = malloc(sizeof(char) * newsize)))
		return (NULL);
	i = 0;
	while (src[i])
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	free(src);
	return (new);
}
