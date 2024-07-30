#include "../inc/cub3d.h"

/**
 * @brief calcule distance that the ray need to travel to hit a wall
 * on the axis x and y.
 * ray.perp_wall_dist -> the distance between the player and the wall
 * @param cub 
 */
void	ft_wall_distance(t_cub3d *cub)
{
	if (cub->ray.side == 0)
	{
		cub->ray.perp_wall_dist = (cub->ray.map_x
				- cub->player.x_pix + (1 - cub->ray.step_x) / 2)
			/ cub->ray.dir_x;
	}
	else
	{
		cub->ray.perp_wall_dist = (cub->ray.map_y
				- cub->player.y_pix + (1 - cub->ray.step_y) / 2)
			/ cub->ray.dir_y;
	}
	cub->ray.line_height = (int)HEIGHT / cub->ray.perp_wall_dist;
}

/**
 * @brief calcule the height of the wall to draw
 * cub->ray.start_wall -> the start of the wall to draw
 * cub->ray.end_wall -> the end of the wall to draw
 * @param cub 
 */
void	ft_wall_height(t_cub3d *cub)
{
	cub->ray.start_wall = ((-1) * cub->ray.line_height) / 2 + HEIGHT / 2;
	cub->ray.real_start_wall = cub->ray.start_wall;
	if (cub->ray.start_wall < 0)
	{
		cub->ray.start_wall = 0;
	}
	cub->ray.end_wall = cub->ray.line_height / 2 + HEIGHT / 2;
	cub->ray.real_end_wall = cub->ray.end_wall;
	if (cub->ray.end_wall >= HEIGHT)
	{
		cub->ray.end_wall = HEIGHT;
	}
}

/**
 * @brief calcule the x position of the texture to draw on the point that
 * the ray touch the wall.
 * @param cub 
 */
void	ft_wall_x(t_cub3d *cub)
{
	if (cub->ray.side == 0)
	{
		cub->ray.wall_x = cub->player.y_pix
			+ cub->ray.perp_wall_dist * cub->ray.dir_y;
	}
	else
	{
		cub->ray.wall_x = cub->player.x_pix
			+ cub->ray.perp_wall_dist * cub->ray.dir_x;
	}
	cub->ray.wall_x -= floor(cub->ray.wall_x);
}

/**
 * @brief paint the wall on the view (canvas_window) with the x position
 *calculating the y position of the wall to draw and the color of the pixel
 * of the texture to draw. 
 * @param cub 
 * @param x the x position of the canvas_window 
 */
void	ft_paint_wall(t_cub3d *cub, int x)
{
	int				y;
	mlx_texture_t	*texture;
	int				wall_height;
	int				real_wall_height;
	t_coord			calculated;

	texture = ft_choice_texture(cub);
	y = cub->ray.start_wall;
	wall_height = cub->ray.end_wall - cub->ray.start_wall;
	real_wall_height = cub->ray.real_end_wall - cub->ray.real_start_wall;
	calculated.x = (int)(cub->ray.wall_x * (double)texture->width);
	while (y < cub->ray.end_wall)
	{
		if (wall_height < (int)(cub->window_canvas->height))
			calculated.y = (y - cub->ray.start_wall) * texture->height
				/ wall_height;
		else
			calculated.y = (y + (real_wall_height - wall_height) / 2)
				* texture->height / real_wall_height;
		mlx_put_pixel(cub->window_canvas, x, y,
			get_pixel_color_from_texture(texture, calculated.x, calculated.y));
		y++;
	}
}

/**
 * @brief if the walls dont have texture paint the wall with a color for each 
 * side of the wall 
 * @param cub 
 * @return uint32_t 
 */
uint32_t	ft_wall_color(t_cub3d *cub)
{
	if (cub->ray.side == 0)
	{
		if (cub->ray.step_x == 1)
			return (0xff0000ff);
		else
			return (0x00ff00ff);
	}
	else
	{
		if (cub->ray.step_y == 1)
			return (0x0000ffff);
		else
			return (0xffff00ff);
	}
}
