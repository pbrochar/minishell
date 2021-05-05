/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 18:56:18 by pbrochar          #+#    #+#             */
/*   Updated: 2021/05/01 19:43:22 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"
#include "libft.h"

/*
** Simply display functions of string or char.
** Some colors are defined in the define color.h
**
** TEXT_NORMAL represents the default color of your terminal and \
** it can be changed in colors.h
*/

void	ft_putstr_color(const char *str, char *color_term)
{
	write(1, color_term, ft_strlen(color_term));
	write(1, str, ft_strlen(str));
	write(1, TEXT_NORMAL, ft_strlen(TEXT_NORMAL));
}

void	ft_putchar_color(int c, char *color_term)
{
	write(1, color_term, 7);
	write(1, &c, 1);
	write(1, TEXT_NORMAL, ft_strlen(TEXT_NORMAL));
}
