/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_convert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 16:26:40 by pbrochar          #+#    #+#             */
/*   Updated: 2021/02/26 16:01:33 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static void	ft_printunsigned(unsigned int nb, size_t *i)
{
	if (nb > 9)
	{
		ft_printunsigned(nb / 10, i);
		ft_putchar_pf((nb % 10) + '0', i);
	}
	else
		ft_putchar_pf((nb % 10) + '0', i);
}

void		ft_putunsigned(t_varg *ftpf)
{
	unsigned int nb;
	unsigned int unsign_max;

	nb = va_arg(*(ftpf->lst), unsigned int);
	unsign_max = 4294967295;
	if (nb == 0 && ftpf->indicator == -2)
		return ;
	if (nb < 0)
		nb = nb + unsign_max + 1;
	ft_printunsigned(nb, &ftpf->nb_print);
}
