/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 17:27:52 by pbrochar          #+#    #+#             */
/*   Updated: 2021/02/25 15:46:26 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void		ft_putnbr_pf(int n, size_t *i, int indicator)
{
	unsigned int nbr;

	if (indicator == -2)
		return ;
	if (n < 0)
	{
		nbr = -n;
		if (indicator == -1)
			ft_putchar_pf('-', i);
	}
	else
		nbr = n;
	if (nbr > 9)
	{
		ft_putnbr_pf(nbr / 10, i, -1);
		ft_putchar_pf((nbr % 10) + '0', i);
	}
	else
		ft_putchar_pf(nbr + '0', i);
}

void		ft_putchar_pf(char c, size_t *i)
{
	write(1, &c, 1);
	(*i)++;
}

void		ft_putstr_pf(char *s, size_t *i)
{
	int a;

	a = ft_strlen(s);
	write(1, s, a);
	(*i) += a;
}
