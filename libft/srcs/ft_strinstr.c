/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <pbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 18:58:54 by pbrochar          #+#    #+#             */
/*   Updated: 2021/06/16 20:23:06 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strinstr(char *src, char *insert, int pos)
{
	int		i;
	int		size;
	int		insert_size;
	int		src_size;
	char	*temp;

	insert_size = ft_strlen(insert);
	src_size = ft_strlen(src);
	size = insert_size + src_size + 1;
	temp = malloc(sizeof(char) * (size + 1));
	if (temp == NULL)
		return (NULL);
	ft_bzero(temp, size);
	ft_memcpy(temp, src, pos);
	i = pos;
	ft_memcpy(&temp[i], insert, insert_size);
	i += insert_size;
	ft_memcpy(&temp[i], &src[pos], src_size - pos);
	temp[size] = '\0';
	return (temp);
}
