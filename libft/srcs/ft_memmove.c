/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:10:56 by pbrochar          #+#    #+#             */
/*   Updated: 2020/11/19 18:44:12 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*buffd;
	unsigned char	*buffc;

	if (!src && !dest)
		return (dest);
	if (dest <= src)
		return (ft_memcpy(dest, src, n));
	buffd = (unsigned char *)dest;
	buffc = (unsigned char *)src;
	while (n)
	{
		n--;
		buffd[n] = buffc[n];
	}
	return (dest);
}
