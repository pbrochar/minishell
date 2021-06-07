/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:15:04 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/07 15:47:13 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	ps1;
	unsigned char	ps2;

	if (!n)
		return (0);
	ps1 = (unsigned char)*s1;
	ps2 = (unsigned char)*s2;
	while (ps1 == ps2 && n--)
	{
		ps1 = (unsigned char)*s1++;
		ps2 = (unsigned char)*s2++;
		if (!ps1 || !ps2)
			return (ps1 - ps2);
	}
	return (ps1 - ps2);
}
