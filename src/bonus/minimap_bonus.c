#include "../../inc/cub3d_bonus.h"

void	ft_init_minimap(t_cub3d *cub)
{
	if (!cub->window_canvas)
	{
		show_error("Window not initialized\n");
		exit(1);
	}
	cub->mini.w = cub->window_canvas->width / 6;
	cub->mini.h = cub->mini.w;
	cub->mini.canvas = mlx_new_image(cub->window, cub->mini.w, cub->mini.h);
	if (!cub->mini.canvas)
	{
		show_error("Minimap canvas creation failed\n");
		exit(1);
	}
	ft_draw_map(cub);
	mlx_image_to_window(cub->window, cub->mini.canvas, 0, 0);
}

void	ft_draw_map(t_cub3d *cub)
{
	int			y;
	int			x;
	t_coordi	map_start;
	t_coordi	map_coord;
	int		ZOOM = 160;
	printf("ft_draw_map: player.pos.x: %f, player.pos.y: %f\n", cub->player.pos.x, cub->player.pos.y);
	printf("ft_draw_map: mini.w: %d, mini.h: %d\n", cub->mini.w, cub->mini.h);
	map_start.y = fmax(0, cub->player.pos.y - cub->mini.h /  ZOOM);
	map_start.x = fmax(0, cub->player.pos.x - cub->mini.w / ZOOM);
	printf("map_start.y: %d, map_start.x: %d\n", map_start.y, map_start.x);
	// int	grid_x;
	// int	grid_y;
	(void) map_start;
	y = -1;
	while (++y < cub->mini.h)
	{
		x = -1;
		while (++x < cub->mini.w)
		{
			map_coord.x = map_start.x + x * MOV;
			map_coord.y = map_start.y + y * MOV;
			if (cub->map.map[(int)fmin(map_coord.x, cub->map.rows)][(int)fmin(map_coord.y, cub->map.cols)] == '1')
				mlx_put_pixel(cub->mini.canvas, x, y, 0xff0000ff);
			else
				mlx_put_pixel(cub->mini.canvas, x, y, 0xff00ffff);
			mlx_put_pixel(cub->mini.canvas, x, y, 0xff00ffff);
		}
	}
}

void	ft_draw_player(mlx_image_t *canvas, int y, int x, int color)
{
	(void) canvas;
	(void) y;
	(void) x;
	(void) color;
	// int	i;
	// int	j;

	// i = -1;
	// x = x / 4 - GRID_SIZE / 16;
	// y = y / 4 - GRID_SIZE / 16;
	// while (++i < GRID_SIZE / 8)
	// {
	// 	j = -1;
	// 	while (++j < GRID_SIZE / 8)
	// 		mlx_put_pixel(canvas, x + j, y + i, color);
	// }
}

void	ft_draw_ray(t_cub3d *cub)
{
	(void) cub;
	// int		x;
	// int		y;
	// double	angle;
	// int		rays;

	// angle = cub->player.angle - cub->player.fov / 2;
	// rays = 0;
	// while (rays++ < NUM_RAYS)
	// {
	// 	x = cub->player.pos.x;
	// 	y = cub->player.pos.y;
	// 	while (cub->map.map[(int)y][(int)x] != '1')
	// 	{
	// 		mlx_put_pixel(cub->mini.canvas, (int)x, (int)y,
	// 			0xffff0000);
	// 		x += cos(angle) * 20;
	// 		y -= sin(angle) * 20;
	// 	}
	// 	angle += cub->player.fov / (NUM_RAYS - 1);
	// }
}
