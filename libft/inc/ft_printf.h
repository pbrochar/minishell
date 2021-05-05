/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 15:52:46 by pbrochar          #+#    #+#             */
/*   Updated: 2021/04/18 12:55:23 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include "libft.h"

typedef struct	s_varg
{
	const char	*str;
	int			pos;
	va_list		*lst;
	size_t		nb_print;
	int			indicator;
}				t_varg;

typedef struct	s_flags
{
	int		nb_zero;
	int		nb_dash;
	int		nb_space;
	int		precision;
	int		len;
	int		eq_type;
	char	type;

}				t_flags;

void			ft_puthex_min(t_varg *ftpf);
void			ft_puthex_maj(t_varg *ftpf);
void			ft_putaddr(t_varg *ftpf);
void			ft_putid(t_varg *ftpf);
void			ft_putstring(t_varg *ftpf);
void			ft_putcharac(t_varg *ftpf);
void			ft_putpct(t_varg *ftpf);
void			ft_putunsigned(t_varg *ftpf);

void			init_s_varg(t_varg *ftpf, const char *format,
va_list *parameters);
void			init_s_flags(t_flags *flags);
int				pf_istype(char c);
int				pf_isflag(char c);
int				nb_len_addr(void *ptr);
int				nb_len_unsigned(unsigned int nb);
int				nb_len_str(char *str);
void			print_arg(t_varg *ftpf, t_flags *flags);
void			print_flags(t_varg *ftpf, t_flags *flags);

void			pf_print_zero(t_varg *ftpf, t_flags *flags);
void			pf_print_space(t_varg *ftpf, t_flags *flags);
void			pf_print_dash(t_varg *ftpf, t_flags *flags);
void			pf_print_precision(t_varg *ftpf, t_flags *flags);

int				ft_printf(const char *format, ...);
void			ft_putnbr_pf(int n, size_t *i, int indicator);
void			ft_putchar_pf(char c, size_t *i);
void			ft_putstr_pf(char *s, size_t *i);
void			ft_put_param(t_varg *ftpf);
void			print_zero(t_varg *test);
int				nb_len_dec(int n);
int				nb_len_hex(int n);

void			int_precision(t_varg *ftpf, t_flags *flags);
void			unsigned_precision(t_varg *ftpf, t_flags *flags);

#endif
