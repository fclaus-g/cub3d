#include "../inc/cub3d.h"

mlx_texture_t	*ft_choice_texture(t_cub3d *cub)
{
	if (cub->ray.side == 0)
	{
		if (cub->ray.step_x == 1)
			return (cub->EA);
		else
			return (cub->WE);
	}
	else
	{
		if (cub->ray.step_y == 1)
			return (cub->SO);
		else
			return (cub->NO);
	}
}

uint32_t	get_pixel_color_from_texture(mlx_texture_t *texture, int x, int y)
{
	uint32_t	*pixels;
	uint32_t	color;
	uint8_t		argb[4];

	if (x < 0 || (uint32_t)x >= texture->width || y < 0 || (uint32_t)y >= texture->height)
		return (0);
	pixels = (uint32_t *)texture->pixels;
	color = pixels[y * texture->width + x];
	argb[0] = (color >> 24) & 0xFF;
    argb[1] = (color >> 16) & 0xFF; // Rojo
    argb[2] = (color >> 8) & 0xFF;  // Verde
    argb[3] = color & 0xFF;   
	if (argb[0] < 128)
		return (0);
	color = (argb[0] << 24) | (argb[1] << 8) | (argb[2]<<16) | (argb[3]);
	return (color);
}

void	ft_load_textures(t_cub3d *cub)
{
	cub->NO = malloc(sizeof(mlx_texture_t));
	cub->SO = malloc(sizeof(mlx_texture_t));
	cub->WE = malloc(sizeof(mlx_texture_t));
	cub->EA = malloc(sizeof(mlx_texture_t));
	cub->hand = malloc(sizeof(mlx_texture_t));
	cub->floor = malloc(sizeof(mlx_texture_t));
	cub->ceil = malloc(sizeof(mlx_texture_t));
	if (!cub->NO || !cub->SO || !cub->WE || !cub->EA)
	{
		show_error("Texture allocation failed\n");
		exit(1);
	}
	cub->NO = mlx_load_png("textures/Lwall.png");
	cub->SO = mlx_load_png("textures/S.png");
	cub->WE = mlx_load_png("textures/W.png");
	cub->EA = mlx_load_png("textures/E.png");
	cub->hand = mlx_load_png("textures/minigun.png");
	cub->floor = mlx_load_png("textures/Sbyn.png");
	cub->ceil = mlx_load_png("textures/oxido.png");
	printf("Textures loaded NO %p, SO %p, WE %p, EA %p\n", cub->NO, cub->SO, cub->WE, cub->EA);
}
