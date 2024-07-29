/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgarcia <frgarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:53:53 by frgarcia          #+#    #+#             */
/*   Updated: 2024/07/29 15:53:56 by frgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int	matrix_len(char **matrix)
{
	int	len;

	len = 0;
	if (!matrix)
		return (len);
	while (matrix[len] != NULL)
		len++;
	return (len);
}

int	starts_with_and_space(char *line, char *start)
{
	int		i;
	int		spaces;

	i = 0;
	spaces = 0;
	while (line[spaces] && is_map_space(line[spaces]))
		spaces++;
	while (start[i] && line[i + spaces])
	{
		if (line[i + spaces] != start[i])
			return (0);
		i++;
	}
	if (!is_map_space(line[i]))
		return (0);
	return (1);
}
