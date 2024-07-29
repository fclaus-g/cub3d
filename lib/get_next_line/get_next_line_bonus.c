/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 09:48:49 by fclaus-g          #+#    #+#             */
/*   Updated: 2022/12/23 12:45:01 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_line(char *static_buf)
{
	char	*line;
	int		count;

	count = 0;
	if (!static_buf || !*static_buf)
		return (NULL);
	while (static_buf[count] != '\n' && static_buf[count] != '\0')
		count++;
	if (static_buf[count] == '\n')
		count++;
	line = (char *)malloc(sizeof(char) * (count + 1));
	if (!line)
		return (NULL);
	ft_strlcpy(line, static_buf, count);
	return (line);
}

char	*up_buf(char *static_buf)
{
	char	*temp;
	int		count;
	int		copier;

	count = 0;
	copier = 0;
	if (!static_buf)
		return (NULL);
	while (static_buf[count] != '\n' && static_buf[count])
		count++;
	if (static_buf[count] == '\0')
		return (free (static_buf), NULL);
	temp = (char *)malloc(sizeof(char) * (ft_strlen(static_buf) - count + 1));
	if (!temp)
		return (NULL);
	count++;
	while (static_buf[count])
		temp[copier++] = static_buf[count++];
	temp[copier] = '\0';
	free (static_buf);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*static_buf[FD_MAX] = {NULL};
	char		*line;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	bytes_read = 1;
	line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line)
		return (free(line), NULL);
	while (!(ft_strchr(static_buf[fd], '\n')) && bytes_read)
	{
		bytes_read = read(fd, line, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(line), free(static_buf[fd]), \
			static_buf[fd] = NULL, NULL);
		line[bytes_read] = '\0';
		static_buf[fd] = ft_strjoin(static_buf[fd], line);
	}
	free (line);
	line = ft_line(static_buf[fd]);
	static_buf[fd] = up_buf(static_buf[fd]);
	return (line);
}
