/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:12:14 by pbrochar          #+#    #+#             */
/*   Updated: 2020/11/21 18:12:53 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;
	size_t	k;

	k = 0;
	i = (size_t)start;
	if (!s)
		return (NULL);
	if (!(sub = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	if ((size_t)start < ft_strlen(s))
	{
		while (s[i] && i < len + start)
		{
			sub[k] = s[i];
			i++;
			k++;
		}
	}
	sub[k] = '\0';
	return (sub);
}
