/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_px_convert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 11:28:10 by pbrochar          #+#    #+#             */
/*   Updated: 2021/04/18 12:44:30 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static void	ft_printhex(int v, int upper, size_t *i)
{
	if (v >= 0 && v < 10)
		ft_putchar_pf('0' + v, i);
	else
	{
		if (upper == 0)
			ft_putchar_pf('a' + v - 10, i);
		else
			ft_putchar_pf('A' + v - 10, i);
	}
}

void		ft_putaddr(t_varg *ftpf)
{
	size_t	b;
	int		i;
	void	*ptr;

	ptr = va_arg(*(ftpf->lst), void *);
	if (ptr == NULL)
	{
		if (ftpf->indicator == -2)
			ft_putstr_pf("0x", &ftpf->nb_print);
		else
			ft_putstr_pf("0x0", &ftpf->nb_print);
		return ;
	}
	b = (size_t)ptr;
	i = (sizeof(b) << 3) - 4;
	ft_putstr_pf("0x", &ftpf->nb_print);
	while (((b >> i) & 0xf) == 0)
		i -= 4;
	while (i >= 0)
	{
		ft_printhex((b >> i) & 0xf, 0, &ftpf->nb_print);
		i -= 4;
	}
}

void		ft_puthex_min(t_varg *ftpf)
{
	int i;
	int nb;

	nb = va_arg(*(ftpf->lst), int);
	if (ftpf->indicator == -2)
		return ;
	if (nb == 0)
	{
		ft_printhex(0, 0, &ftpf->nb_print);
		return ;
	}
	i = (sizeof(nb) << 3) - 4;
	while (((nb >> i) & 0xf) == 0)
		i -= 4;
	while (i >= 0)
	{
		ft_printhex((nb >> i) & 0xf, 0, &ftpf->nb_print);
		i -= 4;
	}
}

void		ft_puthex_maj(t_varg *ftpf)
{
	int i;
	int nb;

	nb = va_arg(*(ftpf->lst), int);
	if (ftpf->indicator == -2)
		return ;
	if (nb == 0)
	{
		ft_printhex(0, 1, &ftpf->nb_print);
		return ;
	}
	i = (sizeof(nb) << 3) - 4;
	while (((nb >> i) & 0xf) == 0)
		i -= 4;
	while (i >= 0)
	{
		ft_printhex((nb >> i) & 0xf, 1, &ftpf->nb_print);
		i -= 4;
	}
}
