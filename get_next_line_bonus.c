/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:02:16 by lrocca            #+#    #+#             */
/*   Updated: 2021/01/22 18:18:05 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	ft_validate(t_buf *curr, char **line)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(*line);
	if (!ft_realloc(line, curr->buffer, i))
		return (-1);
	j = 0;
	while (curr->buffer[j] != '\n')
	{
		(*line)[i++] = curr->buffer[j];
		if (!curr->buffer[j++])
			return (0);
	}
	(*line)[i] = '\0';
	i = 0;
	j++;
	while (curr->buffer[j])
		curr->buffer[i++] = curr->buffer[j++];
	curr->buffer[i] = '\0';
	return (1);
}

static int	ft_read_error(char **line)
{
	if (*line)
		free(*line);
	*line = NULL;
	return (-1);
}

int			get_next_line(int fd, char **line)
{
	int				n;
	int				ret;
	static t_buf	*buffer;
	t_buf			*curr;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0 || !line \
		|| (!buffer && !(buffer = ft_lstnew(fd))) \
		|| !(curr = ft_findbuf(fd, buffer)))
		return (-1);
	*line = NULL;
	if ((ret = ft_validate(curr, line)))
		return (ret);
	while ((n = read(fd, curr->buffer, BUFFER_SIZE)) > 0)
	{
		curr->buffer[n] = '\0';
		if ((ret = ft_validate(curr, line)))
			return (ret);
	}
	if (n < 0)
		return (ft_read_error(line));
	ft_cleanbuf(&buffer, fd);
	return (n);
}
