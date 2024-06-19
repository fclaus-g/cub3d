/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2paint_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:51:30 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/06/14 12:23:52 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void ft_init_minimap(t_game *cub)
{
	ft_printf("Inicializando mapa\n");

	// Crear una nueva imagen para el suelo
	cub->mini = mlx_new_image(cub->mlx, cub->map.w_px, cub->map.h_px);
	if (!cub->mini)
	{
		ft_printf("Falló la creación de la imagen\n");
		exit(1);
	}

	ft_draw_map(cub);
	mlx_image_to_window(cub->mlx, cub->mini, 0, 0);
}

void ft_draw_map(t_game *cub)
{
	int y;
	int x;

	y = -1;
	while (++y < cub->map.rows)
	{
		x = -1;
		while (++x < cub->map.cols)
		{
			if (cub->map.map[y][x] == '1')
				ft_draw_square(cub->mini, y * PIX, x * PIX, 0xff0000ff);
			else if (cub->map.map[y][x] == 'P')
			{
				ft_draw_square(cub->mini, y * PIX, x * PIX, 0xff00ffff);
				ft_draw_player(cub->mini, (cub->pl.y * PIX) + 24, (cub->pl.x * PIX) + 24, 0xffffffff);
			}
			else
				ft_draw_square(cub->mini, y * PIX, x * PIX, 0xff00ffff);
		}
	}
}

void ft_draw_player(mlx_image_t *mini, int y, int x, int color)
{
	int i;
	int j;

	i = -1;
	while (++i < 16)
	{
		j = -1;
		while (++j < 16)
		{
			mlx_put_pixel(mini, x + j, y + i, color);
		}
	}
}

void ft_draw_square(mlx_image_t *canvas, int y, int x, int color)
{
	int i;
	int j;

	i = -1;
	if ((unsigned int)color != 0xffffffff)
	{
		while (++i < PIX)
		{
			j = -1;
			while (++j < PIX)
			{
				mlx_put_pixel(canvas, x + j, y + i, color);
			}
		}
	}
}
