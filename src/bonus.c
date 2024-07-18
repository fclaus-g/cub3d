#include "../inc/cub3d.h"

/**
 * @brief Paint the hand of the player
 * @todo scale the hand to the size of the window (width and height)
 * @param cub 
 */
void	ft_paint_hand(t_cub3d *cub)
{
	int			y;
	int			x;
	uint32_t	color;
	double		scale;
	// int			calculated_x;
	// int			calculated_y;

	if (!cub->hand)
		return ;
	y = 0;
	if (cub->window_canvas->width < cub->hand->width)
		scale = cub->hand->width / cub->window_canvas->width;
	else
		scale = 1;
	while (y < (int)cub->window_canvas->height)
	{
		x = 0;
		while (x < (int)cub->window_canvas->width)
		// {
		// 	// calculated_x = (int)(x * scale);
		// 	// calculated_y = (int)(y * scale);
		// 	// printf("x: %d, y: %d\n", x, y);
		// 	color = get_pixel_color_from_texture(cub->hand, (int)(x * scale), (int)(y * scale));
		// 	if (color != 0)
		// 		mlx_put_pixel(cub->window_canvas, x, y, color);
		// 	x++;
		// }
		{
			if (y >= cub->window_canvas->height - cub->hand->height * scale && x >= ((cub->window_canvas->width - cub->hand->width * scale) / 2) &&  x <= ((cub->window_canvas->width - cub->hand->width * scale) / 2) + cub->hand->width * scale)
			{
				// printf("x: %d, y: %d\n", x, y);
				color = get_pixel_color_from_texture(cub->hand, (int)(x - (cub->window_canvas->width - cub->hand->width * scale) / 2), (int)(y + (cub->hand->height * scale - cub->window_canvas->height)));
				if (color != 0)
					mlx_put_pixel(cub->window_canvas, x, y, color);
			}
			x++;
		}
		y++;
	}
}

void ft_render_floor_and_ceiling(t_cub3d *cub)
{
	uint32_t	y;
	uint32_t	x;
	uint32_t	color;
	uint32_t    z;

	y = -1;
	while (++y < cub->window_canvas->height / 2)
	{
		x = -1;
		z = 0;
		printf("Floor width %d, height %d\n", cub->floor->width, cub->floor->height);
		while (++x < cub->window_canvas->width)
		{
			if (z >= cub->floor->width)
				z = 0;
			color = get_pixel_color_from_texture(cub->ceil, x % cub->ceil->width, y % cub->ceil->height);
			mlx_put_pixel(cub->window_canvas, x, y, color);
		}
	}
	y--;
	while (++y < cub->window_canvas->height - 1)
	{
		x = -1;
		while (++x < cub->window_canvas->width)
		{
			color = get_pixel_color_from_texture(cub->floor, x % cub->floor->width, y % cub->floor->height);
			mlx_put_pixel(cub->window_canvas, x, y, color);
		}
	}
}
