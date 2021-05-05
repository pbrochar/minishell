/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 17:06:08 by pbrochar          #+#    #+#             */
/*   Updated: 2021/02/28 11:35:07 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static int	pf_calcul_total(t_flags *flags, int flag_type)
{
	int total;

	total = flag_type - flags->len;
	if (flags->precision > -1 && flags->len < flags->precision
		&& ft_strchr("iduxX", flags->type))
		total -= (flags->precision - flags->len);
	if (flags->precision > -1 && flags->len > flags->precision
		&& flags->type == 's')
		total += (flags->len - flags->precision);
	return (total);
}

void		pf_print_zero(t_varg *ftpf, t_flags *flags)
{
	int		total;
	va_list cpy;

	va_copy(cpy, *(ftpf->lst));
	total = (flags->nb_zero) - (flags->len);
	if (flags->precision > -1 && flags->type != '%')
	{
		flags->nb_space = flags->nb_zero;
		pf_print_space(ftpf, flags);
		return ;
	}
	if (va_arg(cpy, int) < 0 && (flags->type == 'd' || flags->type == 'i'))
	{
		ft_putchar_pf('-', &ftpf->nb_print);
		ftpf->indicator = 0;
		total--;
	}
	while (total-- > 0)
		ft_putchar_pf('0', &ftpf->nb_print);
	print_arg(ftpf, flags);
}

void		pf_print_space(t_varg *ftpf, t_flags *flags)
{
	int		total;
	va_list	cpy;

	va_copy(cpy, *(ftpf->lst));
	total = pf_calcul_total(flags, flags->nb_space);
	if (va_arg(cpy, int) < 0 && (flags->type == 'd' || flags->type == 'i'))
		total--;
	while (total-- > 0)
		ft_putchar_pf(' ', &ftpf->nb_print);
	pf_print_precision(ftpf, flags);
	print_arg(ftpf, flags);
}

void		pf_print_dash(t_varg *ftpf, t_flags *flags)
{
	int		total;
	va_list	cpy;

	va_copy(cpy, *(ftpf->lst));
	total = pf_calcul_total(flags, flags->nb_dash);
	if (va_arg(cpy, int) < 0 && (flags->type == 'd' || flags->type == 'i'))
		total--;
	pf_print_precision(ftpf, flags);
	print_arg(ftpf, flags);
	while (total-- > 0)
		ft_putchar_pf(' ', &ftpf->nb_print);
}

void		pf_print_precision(t_varg *ftpf, t_flags *flags)
{
	if (ft_strchr("idxX", flags->type))
		int_precision(ftpf, flags);
	else if (flags->type == 'u')
		unsigned_precision(ftpf, flags);
	else if (flags->type == 's' && (flags->precision <= flags->len))
		ftpf->indicator = flags->precision;
	else if (flags->type == 'p' && flags->precision == 0)
		ftpf->indicator = -2;
}
