#include "../inc/cub3d.h"

void ft_paint_hand(t_cub3d *cub)
{
	int y;
	int x;
	uint32_t color;

	y = 0;
	while (y < (int)cub->hand->height)
	{
		x = 0;
		while (x < (int)cub->hand->width)
		{
			color = get_pixel_color_from_texture(cub->hand, x, y);
			if (color != 0)
				mlx_put_pixel(cub->window_canvas, x, y, color);
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
