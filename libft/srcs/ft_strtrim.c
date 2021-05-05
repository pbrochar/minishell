/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:12:16 by pbrochar          #+#    #+#             */
/*   Updated: 2020/11/18 19:12:20 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_trim_cmp(char const *set, char c)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static	char	*ft_strndup(char *trim, char const *s1, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		trim[i] = s1[i];
		i++;
	}
	return (trim);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	int		i;
	int		len;

	i = 0;
	while (s1[i] && ft_trim_cmp(set, s1[i]))
		i++;
	len = ft_strlen(&s1[i]);
	if (len != 0)
	{
		while (s1[i + len - 1] && ft_trim_cmp(set, s1[i + len - 1]))
			len--;
	}
	trim = (char *)malloc(sizeof(char) * (len + 1));
	if (trim == NULL)
		return (NULL);
	trim[len] = '\0';
	ft_strndup(trim, &s1[i], len);
	return (trim);
}
