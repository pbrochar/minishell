/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:11:27 by pbrochar          #+#    #+#             */
/*   Updated: 2020/11/18 19:11:33 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_stradd(char *dest, char const *s1, char const *s2)
{
	size_t i;
	size_t x;

	i = 0;
	x = 0;
	while (s1[x])
	{
		dest[i] = s1[x];
		i++;
		x++;
	}
	x = 0;
	while (s2[x])
	{
		dest[i] = s2[x];
		i++;
		x++;
	}
	dest[i] = '\0';
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	size;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	dest = (char *)malloc(sizeof(char) * size);
	if (dest == NULL)
		return (NULL);
	ft_stradd(dest, s1, s2);
	return (dest);
}
