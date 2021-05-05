/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:09:17 by pbrochar          #+#    #+#             */
/*   Updated: 2020/11/18 19:09:22 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_int_len(int n)
{
	int				i;
	unsigned int	nbr;

	i = 0;
	if (n == 0)
		return (2);
	if (n < 0)
	{
		nbr = -n;
		i++;
	}
	else
		nbr = n;
	while (nbr > 0)
	{
		nbr /= 10;
		i++;
	}
	return (i + 1);
}

static	char	*ft_add_in_tab(char *tab, int size, unsigned int nbr)
{
	while (nbr > 0)
	{
		tab[size - 1] = (nbr % 10) + '0';
		nbr /= 10;
		size--;
	}
	return (tab);
}

char			*ft_itoa(int n)
{
	unsigned int	nbr;
	char			*tab;
	int				size;

	size = ft_int_len(n);
	tab = (char *)malloc(sizeof(char) * size);
	if (tab == NULL)
		return (NULL);
	tab[size - 1] = '\0';
	if (n == 0)
		tab[0] = '0';
	if (n < 0)
	{
		nbr = -n;
		tab[0] = '-';
	}
	else
		nbr = n;
	ft_add_in_tab(tab, size - 1, nbr);
	return (tab);
}
