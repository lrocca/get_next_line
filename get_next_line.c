/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:02:16 by lrocca            #+#    #+#             */
/*   Updated: 2021/01/20 18:43:33 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		verify_line(char **stack, char **line) // 0 not valid
{
	char	*s;

	s = *stack;
	while (*s != '\n')
		if (!*s++)
			return (0);
	*s = '\0';
	*line = ft_strdup(*stack);
	*stack = ft_strdup(s + 1);
	return (1);
}

static	int		read_file(int fd, char *heap, char **stack, char **line)
{
	int		ret;
	char	*tmp;

	while ((ret = read(fd, heap, BUFFER_SIZE)) > 0)
	{
		heap[ret] = '\0';
		if (*stack)
		{
			tmp = *stack;
			*stack = ft_strjoin(tmp, heap);
			free(tmp);
			tmp = NULL;
		}
		else
			*stack = ft_strdup(heap);
		if (verify_line(stack, line))
			break ;
	}
	return (ret > 0 ? 1 : ret);
}

int				get_next_line(int fd, char **line)
{
	static char		*stack[256 + 1];
	char			*heap;
	int				ret;
	int				i;

	if (fd < 0 || !line || (read(fd, stack[fd], 0) < 0) \
		|| !(heap = malloc(BUFFER_SIZE + 1)))
		return (-1);
	if (stack[fd])
		if (verify_line(&stack[fd], line))
			return (1);
	i = 0;
	while (i < BUFFER_SIZE)
		heap[i++] = '\0';
	ret = read_file(fd, heap, &stack[fd], line);
	free(heap);
	if (ret != 0 || stack[fd] == NULL || stack[fd][0] == '\0')
	{
		if (!ret && *line)
			*line = NULL;
		return (ret);
	}
	*line = stack[fd];
	stack[fd] = NULL;
	return (1);
}

int	main(void)
{
	int		ret;
	char	*line;

	line = 0;
	ret = get_next_line(0, &line);
	while (ret > 0)
	{
		write(1, line, ft_strlen(line));
		write(1, "\n", 1);
		free(line);
		line = 0;
		ret = get_next_line(0, &line);
	}
	if (ret == 0)
	{
		write(1, line, ft_strlen(line));
		write(1, "\n", 1);
		free(line);
		line = 0;
	}
}
