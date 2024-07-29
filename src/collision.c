/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgarcia <frgarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:32:12 by frgarcia          #+#    #+#             */
/*   Updated: 2024/07/29 15:32:15 by frgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/**
 * @brief Check if a coordinate is colliding with a wall
 * Considerations:
 * * the map is a grid of 1x1 squares
 * * the coordinates are inside the map, otherwise it will return 1
 */
int	ft_check_collision(t_cub3d *cub, double x, double y)
{
	t_coord	min_coord;
	t_coord	max_coord;

	min_coord.x = (int)(x - OFFSET);
	min_coord.y = (int)(y - OFFSET);
	max_coord.x = (int)(x + OFFSET);
	max_coord.y = (int)(y + OFFSET);
	if (min_coord.x < 0 || min_coord.y < 0 || \
		min_coord.y >= cub->map.rows || min_coord.x >= cub->map.cols)
		return (1);
	if (cub->map.map[min_coord.y][min_coord.x] == '1' || \
		cub->map.map[min_coord.y][max_coord.x] == '1' || \
		cub->map.map[max_coord.y][min_coord.x] == '1' || \
		cub->map.map[max_coord.y][max_coord.x] == '1')
		return (1);
	return (0);
}
