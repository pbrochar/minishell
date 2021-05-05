/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:13:31 by pbrochar          #+#    #+#             */
/*   Updated: 2020/11/21 18:12:09 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			*ft_strndup(char const *s, int n)
{
	int		i;
	char	*dup;

	i = 0;
	while (s[i] && i < n)
		i++;
	if (!(dup = (char*)malloc((i + 1) * sizeof(char))))
		return (0);
	i = 0;
	while (s[i] && i < n)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static int			count_words(char const *s, char c)
{
	int words;
	int i;

	words = 0;
	i = 0;
	while (s[i])
	{
		if (!s[i + 1] || (s[i] == c && s[i + 1] != c) ||
				(s[i + 1] == c && !s[i + 1]))
			words++;
		i++;
	}
	if (words == 0)
		words++;
	return (words);
}

static int			len_stop(char const *s, char c)
{
	int i;

	i = 0;
	while (c != s[i] && s[i])
		i++;
	return (i);
}

static void			*free_tab(char **tab)
{
	size_t i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

char				**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**split;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (!(split = (char**)malloc((count_words(s, c) + 1) * sizeof(char *))))
		return (NULL);
	while (j < count_words(s, c))
	{
		while (s[i] == c && s[i])
			i++;
		if (!s[i])
			break ;
		split[j] = ft_strndup(&s[i], len_stop(&s[i], c));
		if (!split[j])
			return (free_tab(split));
		j++;
		i += len_stop(&s[i], c);
	}
	split[j] = 0;
	return (split);
}
