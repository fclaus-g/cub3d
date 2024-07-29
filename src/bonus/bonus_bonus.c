/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgarcia <frgarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:43:38 by frgarcia          #+#    #+#             */
/*   Updated: 2024/07/29 18:03:07 by frgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

static int	check_center(t_cub3d *c, mlx_texture_t *txt, t_coord ps, double sc)
{
	if (ps.y >= c->window_canvas->height - txt->height * sc
		&& ps.x >= ((c->window_canvas->width - txt->width * sc) / 2)
		&& ps.x <= ((c->window_canvas->width - txt->width * sc) / 2)
		+ txt->width * sc)
		return (1);
	return (0);
}

/**
 * @brief Paint the stats of the player
 * @todo scale the stats to the size of the window (width and height)
 * @param cub 
 */
void	ft_paint_hand(t_cub3d *cub)
{
	t_coord		pos;
	uint32_t	color;
	double		scale;

	pos.y = -1;
	scale = 1;
	if (cub->window_canvas->width < cub->hand->width)
		scale = cub->hand->width / cub->window_canvas->width;
	while (++pos.y < (int)cub->window_canvas->height)
	{
		pos.x = -1;
		while (++pos.x < (int)cub->window_canvas->width)
		{
			if (check_center(cub, cub->hand, pos, scale))
			{
				color = get_pixel_color_from_texture(cub->hand,
						(int)(pos.x - (cub->window_canvas->width
								- cub->hand->width * scale) / 2),
						(int)(pos.y + (cub->hand->height * scale
								- cub->window_canvas->height)));
				if (color != 0)
					mlx_put_pixel(cub->window_canvas, pos.x, pos.y, color);
			}
		}
	}
}

void	ft_paint_stats(t_cub3d *cub, mlx_texture_t *stats)
{
	t_coord		pos;
	uint32_t	color;
	double		scale;

	pos.y = 0;
	if (cub->window_canvas->width < stats->width)
		scale = stats->width / cub->window_canvas->width;
	else
		scale = 1;
	while (pos.y++ < (int)cub->window_canvas->height)
	{
		pos.x = 0;
		while (pos.x++ < (int)cub->window_canvas->width)
		{
			if (check_center(cub, stats, pos, scale))
			{
				color = get_pixel_color_from_texture(stats, (int)(pos.x
							- (cub->window_canvas->width - stats->width * scale)
							/ 2), (int)(pos.y + (stats->height * scale
								- cub->window_canvas->height)));
				if (color != 0)
					mlx_put_pixel(cub->window_canvas, pos.x, pos.y, color);
			}
		}
	}
}
