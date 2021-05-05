/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 16:05:34 by pbrochar          #+#    #+#             */
/*   Updated: 2021/04/19 17:35:40 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_mem_exp(void *ptr, size_t old_size, size_t new_size)
{
	void *new_ptr;

	if (new_size == 0)
		return (NULL);
	if (new_size < old_size)
		return (NULL);
	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	ft_bzero(new_ptr, new_size);
	if (old_size == 0 || !ptr)
		return (new_ptr);
	new_ptr = ft_memmove(new_ptr, ptr, old_size);
	free(ptr);
	return (new_ptr);
}
