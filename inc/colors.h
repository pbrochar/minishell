/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 18:58:22 by pbrochar          #+#    #+#             */
/*   Updated: 2021/07/08 21:26:39 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLORS_H
# define COLORS_H

# define TEXT_RED		"\033[1;31m"
# define TEXT_GREEN		"\033[1;32m"
# define TEXT_YELLOW	"\033[0;33m"
# define TEXT_BLUE		"\033[0;34m"
# define TEXT_PURPLE	"\033[0;35m"
# define TEXT_CYAN		"\033[0;36m"
# define TEXT_NORMAL	"\033[0m"

void	ft_putstr_color(const char *str, char *color_term);
void	ft_putchar_color(int c, char *color_term);

#endif