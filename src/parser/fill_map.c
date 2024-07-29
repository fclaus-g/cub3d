/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgarcia <frgarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:52:43 by frgarcia          #+#    #+#             */
/*   Updated: 2024/07/29 15:52:44 by frgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	fill_map_line(t_cub3d *cub, char *line, int num_row)
{
	int	j;

	cub->map.map[num_row] = (char *)malloc(sizeof(char) * (cub->map.cols + 1));
	if (!cub->map.map[num_row])
		show_error_and_exit("Failed to allocate memory for map row.", 1);
	j = 0;
	while (j < cub->map.cols && line[j + cub->map.left_padding])
	{
		if (is_map_space(line[j + cub->map.left_padding]))
			cub->map.map[num_row][j] = MAP_FILL_SPACE;
		else
			cub->map.map[num_row][j] = line[j + cub->map.left_padding];
		j++;
	}
	while (j < cub->map.cols)
	{
		cub->map.map[num_row][j] = MAP_FILL_SPACE;
		j++;
	}
	cub->map.map[num_row][j] = '\0';
}

void	fill_map_matrix(t_cub3d *cub)
{
	t_list	*current;
	int		i;
	char	*line;

	cub->map.map = (char **)malloc(sizeof(char *) * (cub->map.rows + 1));
	if (!cub->map.map)
		show_error_and_exit("Failed to allocate memory for map matrix.", 1);
	i = 0;
	current = cub->map.lines;
	while (current)
	{
		line = (char *)current->content;
		fill_map_line(cub, line, i);
		current = current->next;
		i++;
	}
	cub->map.map[i] = NULL;
}
