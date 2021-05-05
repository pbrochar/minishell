/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbrochar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 12:44:07 by pbrochar          #+#    #+#             */
/*   Updated: 2021/04/18 12:45:30 by pbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

static int			get_line(t_gnl *gnl, char **line)
{
	size_t	len;
	int		ret;

	len = 0;
	ret = 1;
	while (len == 0)
	{
		len = ft_strccat(gnl, line);
		if (len == 0)
		{
			ret = read(gnl->fd, gnl->buf, BUFFER_SIZE);
			if (ret == -1)
				return (-1);
			gnl->buf[ret] = '\0';
		}
		if (ret < 0)
			return (-1);
		if (ret == 0)
			return (0);
	}
	return (1);
}

static t_gnl		*get_gnl(int fd, t_list **lst)
{
	t_list	*temp;
	t_gnl	*new;

	temp = *lst;
	new = NULL;
	while (temp)
	{
		if (((t_gnl *)(temp->content))->fd == fd)
			return ((t_gnl *)(temp->content));
		temp = temp->next;
	}
	new = malloc(sizeof(t_gnl));
	if (new == NULL)
		return (NULL);
	new->fd = fd;
	new->pos = 0;
	new->buf[0] = '\0';
	temp = ft_lstnew(new);
	if (temp == NULL)
		return (NULL);
	ft_lstadd_back(lst, temp);
	return ((t_gnl *)(temp->content));
}

static	void		rem_lst(int fd, t_list **lst)
{
	t_list	*temp;
	t_list	*prev;

	temp = *lst;
	prev = NULL;
	while (temp)
	{
		if (((t_gnl *)(temp->content))->fd == fd)
		{
			if (prev)
				prev->next = temp->next;
			else
				*lst = temp->next;
			free(temp->content);
			free(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}

int					get_next_line(int fd, char **line)
{
	static t_list	*lst;
	t_gnl			*gnl;
	int				ret;
	char			*c;

	if (fd < 0 || !line || BUFFER_SIZE <= 0 || read(fd, &c, 0) == -1)
		return (-1);
	if ((gnl = get_gnl(fd, &lst)) == NULL)
	{
		rem_lst(fd, &lst);
		return (-1);
	}
	*line = malloc(sizeof(char));
	if (*line == NULL)
		return (-1);
	(*line)[0] = '\0';
	ret = get_line(gnl, line);
	if (ret == 0 || ret == -1)
		rem_lst(fd, &lst);
	return (ret);
}
