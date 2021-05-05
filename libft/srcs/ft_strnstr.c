/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:12:15 by pbrochar          #+#    #+#             */
/*   Updated: 2020/11/21 18:13:07 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *need, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	if (!need[i] || !need)
		return ((char *)hay);
	while (hay[i] && i < len)
	{
		j = 0;
		while (j + i < len && need[j] == hay[i + j])
		{
			if (!need[j + 1])
				return ((char *)hay + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
