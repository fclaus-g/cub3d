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
	cub->map.map[(int)cub->player.y_pix
		/ GRID_SIZE][(int)cub->player.x_pix / GRID_SIZE] = '0';
	ft_load_textures(cub);
	ft_paint_floor_and_ceiling(cub);
	ft_raycaster(cub);
}

void	ft_hook(void *param)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)param;
	ft_keys_moves(cub);
	ft_paint_floor_and_ceiling(cub);
	ft_raycaster(cub);
}

int	main(int argc, char **argv)
{
	t_cub3d	cub;

	init_cub(&cub);
	if (argc != 2)
	{
		show_error("Invalid number of arguments\n");
		exit(1);
	}
	if (!validate_scene(argv[1], &cub))
	{
		free_cub(&cub);
		exit(1);
	}
	cub.window = mlx_init(WIDTH, HEIGHT, "cub3d", 0);
	ft_init_view(&cub);
	mlx_loop_hook(cub.window, &ft_hook, &cub);
	mlx_loop(cub.window);
	free_cub(&cub);
	return (0);
}
