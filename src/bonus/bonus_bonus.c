#include "../../inc/cub3d_bonus.h"

static int	check_center(t_cub3d *c, mlx_texture_t *txt, t_coord ps, double sc)
{
	if (ps.y >= c->window_canvas->height - txt->height * sc
		&& ps.x >= ((c->window_canvas->width - txt->width * sc) / 2)
		&& ps.x <= ((c->window_canvas->width - txt->width * sc) / 2)
		+ txt->width * sc)
		return (1);
	return (0);
}
/**
 * @brief Paint the stats of the player
 * @todo scale the stats to the size of the window (width and height)
 * @param cub 
 */
void	ft_paint_hand(t_cub3d *cub)
{
	t_coord		pos;
	uint32_t	color;
	double		scale;

	if (!cub->hand)
		return ;
	pos.y = 0;
	if (cub->window_canvas->width < cub->hand->width)
		scale = cub->hand->width / cub->window_canvas->width;
	else
		scale = 1;
	while (pos.y < (int)cub->window_canvas->height)
	{
		pos.x = 0;
		while (pos.x < (int)cub->window_canvas->width)
		{
			if (check_center(cub, cub->hand, pos, scale))
			{
				color = get_pixel_color_from_texture(cub->hand, (int)(pos.x - (cub->window_canvas->width - cub->hand->width * scale) / 2), (int)(pos.y + (cub->hand->height * scale - cub->window_canvas->height)));
				if (color != 0)
					mlx_put_pixel(cub->window_canvas, pos.x, pos.y, color);
			}
			pos.x++;
		}
		pos.y++;
	}
}

// static void ft_prepare_ray_dir(t_cub3d *cub, int y)
// {
// 	cub->ray.ray_dir_x0 = cub->ray.dir_x - cub->plane.x;
// 	cub->ray.ray_dir_y0 = cub->ray.dir_y - cub->plane.y;
// 	cub->ray.ray_dir_x1 = cub->ray.dir_x + cub->plane.x;
// 	cub->ray.ray_dir_y1 = cub->ray.dir_y + cub->plane.y;
// 	cub->ray.row_dist = (0.5 * cub->window_canvas->height) / (y - cub->window_canvas->height / 2);
// 	cub->ray.floor_step_x = cub->ray.row_dist * (cub->ray.ray_dir_x1 - cub->ray.ray_dir_x0) / cub->window_canvas->width;
// 	cub->ray.floor_step_y = cub->ray.row_dist * (cub->ray.ray_dir_y1 - cub->ray.ray_dir_y0) / cub->window_canvas->width;
// 	cub->ray.floor_x = (cub->player.x_pix) + (cub->ray.row_dist * cub->ray.ray_dir_x0);
// 	cub->ray.floor_y = (cub->player.y_pix) + (cub->ray.row_dist * cub->ray.ray_dir_y0);
// }

// static void ft_get_texture_coord(t_cub3d *cub, mlx_texture_t *texture)
// {
// 	if (!texture)
// 		return ;
// 	cub->ray.tx_x = (int)(texture->width * (cub->ray.floor_x - (int)cub->ray.floor_x)) % (texture->width - 1);
// 	cub->ray.tx_y = (int)(texture->height * (cub->ray.floor_y - (int)cub->ray.floor_y)) % (texture->height - 1);
// 	cub->ray.floor_x += cub->ray.floor_step_x;
// 	cub->ray.floor_y += cub->ray.floor_step_y;
//}

// void ft_render_floor_and_ceiling(t_cub3d *cub)
// {
// 	int y;
// 	int x;

// 	y = cub->window_canvas->height / 2;
// 	while (y < (int)cub->window_canvas->height)
// 	{
// 		ft_prepare_ray_dir(cub, y);
// 		x = -1;
// 		while (++x < (int)cub->window_canvas->width/2)
// 		{
// 			cub->ray.tx_x = (int)(cub->floor->width * (cub->ray.floor_x - (int)cub->ray.floor_x)) % (cub->floor->width - 1);
// 			cub->ray.tx_y = (int)(cub->floor->height * (cub->ray.floor_y - (int)cub->ray.floor_y)) % (cub->floor->height - 1);	
// 			mlx_put_pixel(cub->window_canvas, x, y, get_pixel_color_from_texture(cub->floor, x, cub->ray.tx_y));
// 			//mlx_put_pixel(cub->window_canvas, x, y, get_pixel_color_from_texture(cub->floor, cub->ray.tx_x, cub->window_canvas->height - y - 1));
// 			//mlx_put_pixel(cub->window_canvas, x, y, get_pixel_color_from_texture(cub->floor, x, cub->ray.tx_y));
// 			// mlx_put_pixel(cub->window_canvas, x, y, get_pixel_color_from_texture(cub->floor, cub->ray.tx_x, y));
// 			cub->ray.floor_y += cub->ray.floor_step_y;
// 			cub->ray.floor_x += cub->ray.floor_step_x;
// 		}
// 		y++;
// 	}
// }

// void ft_render_floor_and_ceiling(t_cub3d *cub) {
//     int y;
//     int x;

//     for (y = 0; y < (int)cub->window_canvas->height; y++) {
//         ft_prepare_ray_dir(cub, y);

//         int p = y - cub->window_canvas->height / 2;
//         float posZ = 0.5 * cub->window_canvas->height;
//         float rowDistance = posZ / p;
//         float floorStepX = rowDistance * (cub->ray.ray_dir_x1 - cub->ray.ray_dir_x0) / cub->window_canvas->width;
//         float floorStepY = rowDistance * (cub->ray.ray_dir_y1 - cub->ray.ray_dir_y0) / cub->window_canvas->width;
//         cub->ray.floor_x = cub->player.x_pix + rowDistance * cub->ray.ray_dir_x0;
//         cub->ray.floor_y = cub->player.y_pix + rowDistance * cub->ray.ray_dir_y0;

//         for (x = 0; x < (int)cub->window_canvas->width; x++) {
//             int cellX = (int)(cub->ray.floor_x);
//             int cellY = (int)(cub->ray.floor_y);

//             cub->ray.tx_x = (int)(cub->floor->width * (cub->ray.floor_x - cellX)) & (cub->floor->width - 1);
//             cub->ray.tx_y = (int)(cub->floor->height * (cub->ray.floor_y - cellY)) & (cub->floor->height - 1);

//             cub->ray.floor_x += floorStepX;
//             cub->ray.floor_y += floorStepY;

//             mlx_put_pixel(cub->window_canvas, x, y, get_pixel_color_from_texture(cub->floor, cub->ray.tx_x, cub->ray.tx_y));
//             mlx_put_pixel(cub->window_canvas, x, cub->window_canvas->height - y - 1, get_pixel_color_from_texture(cub->ceil, cub->ray.tx_x, cub->ray.tx_y));
//         }
//     }
// }



void	ft_paint_stats(t_cub3d *cub, mlx_texture_t *stats)
{
	t_coord		pos;
	uint32_t	color;
	double		scale;

	pos.y = 0;
	if (cub->window_canvas->width < stats->width)
		scale = stats->width / cub->window_canvas->width;
	else
		scale = 1;
	while (pos.y++ < (int)cub->window_canvas->height)
	{
		pos.x = 0;
		while (pos.x++ < (int)cub->window_canvas->width)
		{
			if (check_center(cub, stats, pos, scale))
			{
				color = get_pixel_color_from_texture(stats, (int)(pos.x
							- (cub->window_canvas->width - stats->width * scale)
							/ 2), (int)(pos.y + (stats->height * scale
								- cub->window_canvas->height)));
				if (color != 0)
					mlx_put_pixel(cub->window_canvas, pos.x, pos.y, color);
			}
		}
	}
}
