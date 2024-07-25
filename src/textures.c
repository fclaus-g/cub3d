#include "../inc/cub3d.h"

mlx_texture_t	*ft_choice_texture(t_cub3d *cub)
{
	if (cub->ray.side == 0)
	{
		if (cub->ray.step.x == 1)
			return (cub->ea);
		else
			return (cub->we);
	}
	else
	{
		if (cub->ray.step.y == 1)
			return (cub->so);
		else
			return (cub->no);
	}
}

/**
 * @brief transform a color from ARGB to RGBA
 * 
 * @param color 
 * @return uint32_t rgba color
 * @return 0 if the alpha channel is not completely opaque
 */
uint32_t	transform_color(uint32_t color)
{
	uint8_t	a;
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	a = (color >> 24) & 0xFF;
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	if (a < 128)
		return (0);
	return (b << 24 | g << 16 | r << 8 | a);
}

uint32_t	get_pixel_color_from_texture(mlx_texture_t *texture, int x, int y)
{
	uint32_t	*pixels;
	uint32_t	color;

	if (x < 0 || (uint32_t)x >= texture->width || y < 0
		|| (uint32_t)y >= texture->height)
		return (0);
	pixels = (uint32_t *)texture->pixels;
	color = pixels[y * texture->width + x];
	return (transform_color(color));
}

void	ft_load_textures(t_cub3d *cub)
{
	cub->no = mlx_load_png(cub->scene.textures.no);
	cub->so = mlx_load_png(cub->scene.textures.so);
	cub->we = mlx_load_png(cub->scene.textures.we);
	cub->ea = mlx_load_png(cub->scene.textures.ea);
}
