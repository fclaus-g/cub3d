#include "../../inc/cub3d_bonus.h"

/**
 * @brief Paint the stats of the player
 * @todo scale the stats to the size of the window (width and height)
 * @param cub 
 */
void	ft_paint_hand(t_cub3d *cub)
{
	int			y;
	int			x;
	uint32_t	color;
	double		scale;

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
		{
			if (y >= cub->window_canvas->height - cub->hand->height * scale && x >= ((cub->window_canvas->width - cub->hand->width * scale) / 2) &&  x <= ((cub->window_canvas->width - cub->hand->width * scale) / 2) + cub->hand->width * scale)
			{
				color = get_pixel_color_from_texture(cub->hand, (int)(x - (cub->window_canvas->width - cub->hand->width * scale) / 2), (int)(y + (cub->hand->height * scale - cub->window_canvas->height)));
				if (color != 0)
					mlx_put_pixel(cub->window_canvas, x, y, color);
			}
			x++;
		}
		y++;
	}
}
static void ft_prepare_ray_dir(t_cub3d *cub, int y)
{
	cub->ray.ray_dir_x0 = cub->ray.dir_x - cub->plane.x;
	cub->ray.ray_dir_y0 = cub->ray.dir_y - cub->plane.y;
	cub->ray.ray_dir_x1 = cub->ray.dir_x + cub->plane.x;
	cub->ray.ray_dir_y1 = cub->ray.dir_y + cub->plane.y;
	cub->ray.row_dist = 0.5 * cub->window_canvas->height / (y - cub->window_canvas->height / 2);
	cub->ray.floor_step_x = cub->ray.row_dist * (cub->ray.ray_dir_x1 - cub->ray.ray_dir_x0) / cub->window_canvas->width;
	cub->ray.floor_step_y = cub->ray.row_dist * (cub->ray.ray_dir_y1 - cub->ray.ray_dir_y0) / cub->window_canvas->width;
	cub->ray.floor_x = (cub->player.x_pix / 64) + cub->ray.row_dist * cub->ray.ray_dir_x0;
	// printf("floor_x: %f\n", cub->ray.floor_x);
	cub->ray.floor_y = (cub->player.x_pix / 64) + cub->ray.row_dist * cub->ray.ray_dir_y0;
	// printf("floor_y: %f\n", cub->ray.floor_y);
}

static void ft_get_texture_coord(t_cub3d *cub, mlx_texture_t *texture)
{
	// printf("texture width: %d\n", texture->width);
	// printf("previo a la petacion\n");
	cub->ray.tx_x = (int)(texture->width * (cub->ray.floor_x - (int)cub->ray.floor_x)) % (texture->width - 1);
	// printf("aquir petal\n");
	cub->ray.tx_y = (int)(texture->height * (cub->ray.floor_y - (int)cub->ray.floor_y)) % (texture->height - 1);
	cub->ray.floor_x += cub->ray.floor_step_x;
	cub->ray.floor_y += cub->ray.floor_step_y;
}

void ft_render_floor_and_ceiling(t_cub3d *cub)
{
	int y;
	int x;

	y = 0;
	while (y < (int)cub->window_canvas->height)
	{
		ft_prepare_ray_dir(cub, y);
		// printf("ray_dir_x0: %f\n", cub->ray.ray_dir_x0);
		// printf("texture width: \n");
		x = 0;
		while (x < (int)cub->window_canvas->width)
		{
			ft_get_texture_coord(cub, cub->floor);
			// printf("tx_x: %d\n", cub->ray.tx_x);
			mlx_put_pixel(cub->window_canvas, x, y, get_pixel_color_from_texture(cub->floor, cub->ray.tx_x, cub->ray.tx_y));
			x++;
		}
		y++;
	}

}

void	ft_paint_stats(t_cub3d *cub, mlx_texture_t *stats)
{
	int			y;
	int			x;
	uint32_t	color;
	double		scale;

	if (!stats)
		return ;
	y = 0;
	if (cub->window_canvas->width < stats->width)
		scale = stats->width / cub->window_canvas->width;
	else
		scale = 1;
	while (y < (int)cub->window_canvas->height)
	{
		x = 0;
		while (x < (int)cub->window_canvas->width)
		{
			if (y >= cub->window_canvas->height - stats->height * scale && x >= ((cub->window_canvas->width - stats->width * scale) / 2) &&  x <= ((cub->window_canvas->width - stats->width * scale) / 2) + stats->width * scale)
			{
				color = get_pixel_color_from_texture(stats, (int)(x - (cub->window_canvas->width - stats->width * scale) / 2), (int)(y + (stats->height * scale - cub->window_canvas->height)));
				if (color != 0)
					mlx_put_pixel(cub->window_canvas, x, y, color);
			}
			x++;
		}
		y++;
	}
}

