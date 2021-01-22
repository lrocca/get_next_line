/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:02:29 by lrocca            #+#    #+#             */
/*   Updated: 2021/01/22 18:31:37 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (*s++)
		len++;
	return (len);
}

int		ft_realloc(char **line, char *buf, size_t len)
{
	char	*new;
	size_t	i;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (!(new = malloc(len + i + 1)))
		return (0);
	i = 0;
	while (i < len)
	{
		new[i] = (*line)[i];
		++i;
	}
	new[i] = '\0';
	free(*line);
	*line = new;
	return (1);
}

t_buf	*ft_lstnew(int fd)
{
	t_buf	*new;

	if (!(new = malloc(sizeof(t_buf))))
		return (NULL);
	new->fd = fd;
	new->next = NULL;
	new->buffer[0] = '\0';
	return (new);
}

t_buf	*ft_findbuf(int fd, t_buf *curr)
{
	while (curr->fd != fd && curr->next)
		curr = curr->next;
	if (curr->fd == fd)
		return (curr);
	return (curr->next = ft_lstnew(fd));
}

void	ft_cleanbuf(t_buf **buffer, int fd)
{
	t_buf	*curr;
	t_buf	*tmp;

	curr = *buffer;
	if (curr->fd == fd)
	{
		tmp = curr->next;
		free(curr);
		*buffer = tmp;
		return ;
	}
	while (curr->next->fd != fd)
		curr = curr->next;
	tmp = ft_findbuf(fd, *buffer);
	curr->next = tmp->next;
	free(tmp);
}
