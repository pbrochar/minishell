/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   idsc_convert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 14:48:42 by pbrochar          #+#    #+#             */
/*   Updated: 2021/04/18 12:44:36 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

void	ft_putid(t_varg *ftpf)
{
	ft_putnbr_pf(va_arg(*(ftpf->lst), int), &ftpf->nb_print, ftpf->indicator);
}

void	ft_putstring(t_varg *ftpf)
{
	char	*str;
	char	*null;
	int		i;

	i = 0;
	null = "(null)";
	str = va_arg(*(ftpf->lst), char *);
	if (ftpf->indicator > -1 && str)
	{
		while ((ftpf->indicator)-- > 0)
			ft_putchar_pf(str[i++], &ftpf->nb_print);
		return ;
	}
	if (!str)
	{
		if (ftpf->indicator > -1)
			while ((ftpf->indicator)-- > 0)
				ft_putchar_pf(null[i++], &ftpf->nb_print);
		else
			ft_putstr_pf(null, &ftpf->nb_print);
		return ;
	}
	ft_putstr_pf(str, &ftpf->nb_print);
}

void	ft_putcharac(t_varg *ftpf)
{
	ft_putchar_pf(va_arg(*(ftpf->lst), int), &ftpf->nb_print);
}

void	ft_putpct(t_varg *ftpf)
{
	ft_putchar_pf('%', &ftpf->nb_print);
}
