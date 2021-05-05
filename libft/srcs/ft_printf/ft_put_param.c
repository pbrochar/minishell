/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_param.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 15:45:54 by pbrochar          #+#    #+#             */
/*   Updated: 2021/04/18 12:44:25 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static int		count_flags(t_varg *ftpf)
{
	int nb;

	nb = 0;
	if (ftpf->str[ftpf->pos] == '*')
	{
		nb = va_arg(*(ftpf->lst), int);
		ftpf->pos++;
		return (nb);
	}
	if (ft_isdigit(ftpf->str[ftpf->pos]))
	{
		nb = ft_atoi(&(ftpf->str[ftpf->pos]));
		while (ft_isdigit(ftpf->str[ftpf->pos]))
			ftpf->pos++;
		return (nb);
	}
	return (0);
}

static void		pf_iszero(t_varg *ftpf, t_flags *flags)
{
	int nb;

	while (ftpf->str[ftpf->pos] == '0')
		ftpf->pos++;
	nb = count_flags(ftpf);
	if (nb < 0)
		flags->nb_dash = -nb;
	else
		flags->nb_zero = nb;
}

static void		pf_isdash(t_varg *ftpf, t_flags *flags)
{
	int nb;

	while (ftpf->str[ftpf->pos] == '-')
		ftpf->pos++;
	nb = count_flags(ftpf);
	if (nb < 0)
		nb = -nb;
	flags->nb_dash = nb;
	flags->nb_zero = -1;
}

static void		init_param(t_varg *ftpf, t_flags *flags)
{
	int nb;

	if (ftpf->str[ftpf->pos] == '0')
		pf_iszero(ftpf, flags);
	if (ftpf->str[ftpf->pos] == '-')
		pf_isdash(ftpf, flags);
	else if (ftpf->str[ftpf->pos] != '.' &&
			(pf_istype(ftpf->str[ftpf->pos]) == -1))
	{
		nb = count_flags(ftpf);
		if (nb < 0)
			flags->nb_dash = -nb;
		else
			flags->nb_space = nb;
	}
	if (ftpf->str[ftpf->pos] == '.')
	{
		ftpf->pos++;
		flags->precision = count_flags(ftpf);
	}
	flags->eq_type = pf_istype(ftpf->str[ftpf->pos]);
	flags->type = ftpf->str[ftpf->pos];
}

void			ft_put_param(t_varg *ftpf)
{
	t_flags	flags;

	init_s_flags(&flags);
	ftpf->pos++;
	init_param(ftpf, &flags);
	print_flags(ftpf, &flags);
}
