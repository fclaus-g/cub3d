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

	if (x < 0 || (uint32_t)x >= texture->width || y < 0 || (uint32_t)y >= texture->height)
		return (0);
	pixels = (uint32_t *)texture->pixels;
	color = pixels[y * texture->width + x];
	return (color);
}

void	ft_load_textures(t_cub3d *cub)
{
	cub->NO = malloc(sizeof(mlx_texture_t));
	cub->SO = malloc(sizeof(mlx_texture_t));
	cub->WE = malloc(sizeof(mlx_texture_t));
	cub->EA = malloc(sizeof(mlx_texture_t));
	if (!cub->NO || !cub->SO || !cub->WE || !cub->EA)
	{
		show_error("Texture allocation failed\n");
		exit(1);
	}
	cub->NO = mlx_load_png("textures/N.png");
	cub->SO = mlx_load_png("textures/S.png");
	cub->WE = mlx_load_png("textures/W.png");
	cub->EA = mlx_load_png("textures/E.png");
	printf("Textures loaded NO %p, SO %p, WE %p, EA %p\n", cub->NO, cub->SO, cub->WE, cub->EA);
}
