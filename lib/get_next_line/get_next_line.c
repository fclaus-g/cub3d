/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:25:17 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/07/10 18:38:11 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	ft_strlcpy_gnl(line, static_buf, count);
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
	temp = (char *)malloc(sizeof(char) * \
		(ft_strlen_gnl(static_buf) - count + 1));
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
	static char	*static_buf = NULL;
	char		*line;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	bytes_read = 1;
	line = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!line)
		return (free(line), NULL);
	while (!(ft_strchr_gnl(static_buf, '\n')) && bytes_read)
	{
		bytes_read = read(fd, line, BUFFER_SIZE);
		if (bytes_read < 0 || (bytes_read == 0 && !static_buf))
			return (free(line), free(static_buf), static_buf = NULL, NULL);
		line[bytes_read] = '\0';
		static_buf = ft_strjoin_gnl(static_buf, line);
	}
	free (line);
	line = ft_line(static_buf);
	static_buf = up_buf(static_buf);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("text.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	printf("%s\n", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s\n", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("%s\n", line);
// 	free(line);
// 	close(fd);
// 	return (0);
// }
