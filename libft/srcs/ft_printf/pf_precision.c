/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_precision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 11:29:19 by pbrochar          #+#    #+#             */
/*   Updated: 2021/04/18 12:44:51 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	int_precision(t_varg *ftpf, t_flags *flags)
{
	va_list		cpy;
	int			nb;

	va_copy(cpy, *(ftpf->lst));
	nb = va_arg(cpy, int);
	if (nb < 0 && (flags->type == 'i' || flags->type == 'd'))
	{
		ft_putchar_pf('-', &ftpf->nb_print);
		ftpf->indicator = 0;
	}
	if (nb == 0 && flags->precision == 0)
		ftpf->indicator = -2;
	while ((flags->precision)-- > flags->len)
		ft_putchar_pf('0', &ftpf->nb_print);
}

void	unsigned_precision(t_varg *ftpf, t_flags *flags)
{
	va_list			cpy;
	unsigned int	u_nb;

	va_copy(cpy, *(ftpf->lst));
	u_nb = va_arg(cpy, unsigned int);
	if (u_nb == 0 && flags->precision == 0)
		ftpf->indicator = -2;
	while ((flags->precision)-- > flags->len)
		ft_putchar_pf('0', &ftpf->nb_print);
}
