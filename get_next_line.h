/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:02:40 by lrocca            #+#    #+#             */
/*   Updated: 2021/01/21 18:29:47 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

typedef	struct	s_buf
{
	int				fd;
	char			buffer[BUFFER_SIZE + 1];
	struct s_buf	*next;
}				t_buf;

t_buf			*ft_lstnew(int fd);
t_buf			*ft_findbuf(int fd, t_buf *curr);

int				get_next_line(int fd, char **line);

#endif
