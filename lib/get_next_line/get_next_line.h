/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:26:12 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/05/29 20:21:18 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *s1, char *s2);
size_t	ft_strlen_gnl(const char *s);
char	*ft_join(char *str, char *s1, char *s2);
char	*ft_strchr_gnl(const char *s, int c);
char	*up_buf(char *static_buf);
char	*ft_line(char *static_buf);
char	*ft_strlcpy_gnl(char *line, const char *static_buf, size_t dstsize);

#endif