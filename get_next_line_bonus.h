/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrocca <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 16:02:40 by lrocca            #+#    #+#             */
/*   Updated: 2021/01/22 18:13:00 by lrocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

typedef	struct	s_buf
{
	int				fd;
	char			buffer[BUFFER_SIZE + 1];
	struct s_buf	*next;
}				t_buf;

size_t			ft_strlen(const char *s);
int				ft_realloc(char **line, char *buf, size_t len);
t_buf			*ft_lstnew(int fd);
t_buf			*ft_findbuf(int fd, t_buf *curr);
void			ft_cleanbuf(t_buf **buffer, int fd);

int				get_next_line(int fd, char **line);

#endif
