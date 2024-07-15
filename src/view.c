#include "../inc/cub3d.h"

void	ft_init_view(t_cub3d *cub)
{
	cub->window_canvas = mlx_new_image(cub->window, WIDTH, HEIGHT);
	if (!cub->window_canvas)
	{
		show_error("Map canvas creation failed\n");
		exit(1);
	}
	mlx_image_to_window(cub->window, cub->window_canvas, 0, 0);
	cub->map.map[(int)cub->player.y_pix / GRID_SIZE][(int)cub->player.x_pix / GRID_SIZE] = '0';
	ft_paint_floor_and_ceiling(cub);
	//ft_print_player(cub);
	ft_load_textures(cub);
	ft_raycaster(cub);
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
			mlx_put_pixel(cub->window_canvas, x, y, 0x00ff00ff);
		}
	}
	y--;
	while (++y < cub->window_canvas->height - 1)
	{
		x = -1;
		while (++x < cub->window_canvas->width)
		{
			mlx_put_pixel(cub->window_canvas, x, y, 0xffffffff);
		}
	}
}
