/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgarcia <frgarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:43:31 by frgarcia          #+#    #+#             */
/*   Updated: 2024/07/29 18:10:35 by frgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d_bonus.h"

void	ft_init_minimap(t_cub3d *cub)
{
	cub->mini.w = cub->map.cols * GRID_SIZE / 4;
	cub->mini.h = cub->map.rows * GRID_SIZE / 4;
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
	int	y;
	int	x;
	int	grid_x;
	int	grid_y;

	y = -1;
	while (++y < cub->mini.h)
	{
		x = 0;
		grid_y = y / (GRID_SIZE / 4);
		while (++x < cub->mini.w)
		{
			grid_x = x / (GRID_SIZE / 4);
			if (cub->map.map[grid_y][grid_x] == '1')
				mlx_put_pixel(cub->mini.canvas, x, y, 0x000000ff);
			else if (cub->map.map[grid_y][grid_x] == '0')
				mlx_put_pixel(cub->mini.canvas, x, y, 0xffffffff);
			else
				mlx_put_pixel(cub->mini.canvas, x, y, 0xffffff77);
		}
	}
	ft_draw_ray(cub);
	ft_draw_player(cub->mini.canvas, cub->player.y_pix, cub->player.x_pix,
		0x999999ff);
}

void	ft_draw_player(mlx_image_t *canvas, double y, double x, int color)
{
	int	i;
	int	j;

	i = -1;
	x = (x - 0.25) * GRID_SIZE / 4;
	y = (y - 0.25) * GRID_SIZE / 4;
	while (++i < GRID_SIZE / 8)
	{
		j = -1;
		while (++j < GRID_SIZE / 8)
			mlx_put_pixel(canvas, x + j, y + i, color);
	}
}

void	ft_draw_square(mlx_image_t *canvas, int y, int x, int color)
{
	int	i;
	int	j;

	i = -1;
	if ((unsigned int)color != 0xffffffff)
	{
		while (++i < GRID_SIZE)
		{
			j = -1;
			while (++j < GRID_SIZE)
			{
				mlx_put_pixel(canvas, x + j, y + i, color);
			}
		}
	}
}

void	ft_draw_ray(t_cub3d *cub)
{
	double		x;
	double		y;
	double		angle;
	int			rays;

	angle = cub->player.angle - cub->player.fov / 2;
	rays = 0;
	while (rays++ < NUM_RAYS)
	{
		x = cub->player.x_pix * GRID_SIZE / 4;
		y = cub->player.y_pix * GRID_SIZE / 4;
		while (cub->map.map[(int)(y / GRID_SIZE * 4)][
				(int)(x / GRID_SIZE * 4)] != '1')
		{
			mlx_put_pixel(cub->mini.canvas, (int)x, (int)y,
				0xccccccff);
			x += cos(angle);
			y -= sin(angle);
		}
		angle += cub->player.fov / (NUM_RAYS - 1);
	}
}
