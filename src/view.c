/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgarcia <frgarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:33:30 by frgarcia          #+#    #+#             */
/*   Updated: 2024/07/29 15:33:31 by frgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

uint32_t	rgb_to_uint32(t_rgb rgb)
{
	return (rgb.r << 24 | rgb.g << 16 | rgb.b << 8 | 0xFF);
}

void	ft_paint_floor_and_ceiling(t_cub3d *cub)
{
	uint32_t	y;
	uint32_t	x;

	y = -1;
	while (++y < cub->window_canvas->height / 2)
	{
		x = -1;
		while (++x < cub->window_canvas->width)
		{
			mlx_put_pixel(cub->window_canvas, x, y,
				rgb_to_uint32(cub->scene.textures.ceil));
		}
	}
	y--;
	while (++y < cub->window_canvas->height - 1)
	{
		x = -1;
		while (++x < cub->window_canvas->width)
		{
			mlx_put_pixel(cub->window_canvas, x, y,
				rgb_to_uint32(cub->scene.textures.floor));
		}
	}
}
