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

void	uint32_to_rgba(uint32_t color, uint8_t *a, uint8_t *r, uint8_t *g, uint8_t *b)
{
	*a = (color >> 24) & 0xFF;
	*b = (color >> 16) & 0xFF;
	*g = (color >> 8) & 0xFF;
	*r = color & 0xFF;
}

uint32_t	rgba_to_uint32(uint8_t a, uint8_t r, uint8_t g, uint8_t b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

void	test_color(void)
{
	void			*window;
	mlx_image_t		*image;
	mlx_texture_t	*texture;
	uint32_t		color;
	uint8_t			a, r, g, b;
	int 			x, y;

	x = 0; y = 0;
	window = mlx_init(800, 600, "test", 0);
	image = mlx_new_image(window, 800, 600);
	texture = malloc(sizeof(mlx_texture_t));
    // texture = mlx_load_png("textures/W.png");
	// texture = mlx_load_png("textures/Lwall.png");
	texture = mlx_load_png("textures/minigun.png");

	color = get_pixel_color_from_texture(texture, 0, 0);
	uint32_to_rgba(color, &a, &r, &g, &b);
    printf("El color de la textura en (%d, %d) es %u con A:%u, R: %u, G: %u, B: %u\n", x, y, color, a, r, g, b);
	for (int i = 0; i < 800; i++)
	{
		for (int j = 0; j < 600; j++)
		{
			mlx_put_pixel(image, i, j, color);
		}
	}
	// color = rgba_to_uint32(a, r, g, b);
	// uint32_to_rgba(color, &a, &b, &g, &r);
    // printf("El color de la textura en (%d, %d) es %u con A:%u, R: %u, G: %u, B: %u\n", x, y, color, a, r, g, b);
	// for (int i = 400; i < 800; i++)
	// {
	// 	for (int j = 0; j < 600; j++)
	// 	{
	// 		mlx_put_pixel(image, i, j, color);
	// 	}
	// }
	mlx_image_to_window(window, image, 0, 0);
	mlx_loop(window);
}

// void test_texture_pick_color(void)
// {
//     mlx_texture_t *test;
//     int x;
//     int y;
//     uint8_t a, r, g, b;
//     uint32_t color;

//     test = malloc(sizeof(mlx_texture_t));
//     test = mlx_load_png("textures/W.png");
//     x = 0; y = 0;
//     color = get_pixel_color_from_texture(test, x, y);
//     uint32_to_rgba(color, &a, &r, &g, &b);
//     printf("El color de la textura en (%d, %d) es %u con R: %u, G: %u, B: %u\n", x, y, color, r, g, b);
//     x = 32; y = 32;
//     color = get_pixel_color_from_texture(test, x, y);
//     uint32_to_rgba(color, &a, &r, &g, &b);
//     printf("El color de la textura en (%d, %d) es %u con R: %u, G: %u, B: %u\n", x, y, color, r, g, b);
//     x = 15; y = 9;
//     color = get_pixel_color_from_texture(test, x, y);
//     uint32_to_rgba(color, &a, &r, &g, &b);
//     printf("El color de la textura en (%d, %d) es %u con R: %u, G: %u, B: %u\n", x, y, color, r, g, b);
// }

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
		free_matrix(cub.map.map);
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
	mlx_terminate(cub.window);
	free(cub.map.map);
	return (0);
}
