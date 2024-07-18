#include "../inc/cub3d.h"

void	ft_hook(void *param)
{
	t_cub3d	*cub;

	cub = (t_cub3d *)param;
	ft_keys_moves(cub);
	ft_draw_map(cub);
	ft_draw_player(cub->mini.canvas, cub->player.y_pix, cub->player.x_pix, 0xffffffff);
	ft_draw_ray(cub);
	ft_paint_floor_and_ceiling(cub);
	// ft_render_floor_and_ceiling(cub);
	ft_raycaster(cub);
	ft_paint_hand(cub);
}

int	main(int argc, char **argv)
{
	// (void)argc;
	// (void)argv;
	// test_color();
	t_cub3d	cub;

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
	// print_scene(&cub);
	// printf("scene printed\n");
	cub.window = mlx_init(WIDTH, HEIGHT, "cub3d", 0);
	// printf("mlx iniciado\n");
	ft_init_view(&cub);
	// printf("mapa inicializado\n");
	ft_init_minimap(&cub);
	// printf("minimapa inicializado\n");
	mlx_loop_hook(cub.window, &ft_hook, &cub);
	mlx_loop(cub.window);
	free_cub(&cub);
	return (0);
}
