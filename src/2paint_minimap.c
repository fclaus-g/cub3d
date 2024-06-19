/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2paint_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:51:30 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/06/18 16:42:57 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void ft_init_minimap(t_game *cub)
{
	ft_printf("Inicializando mapa\n");

	// Crear una nueva imagen para el suelo
	cub->mini_w = cub->map.w_px / 4;
    cub->mini_h = cub->map.h_px / 4;
	cub->mini = mlx_new_image(cub->mlx, cub->mini_w, cub->mini_h);
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
	while (++y < cub->mini_h)
	{
		x = 0;
		while (++x < cub->mini_w)
		{
			if (cub->map.map[y / (PIX/4)][x / (PIX/4)] == '1')
				mlx_put_pixel(cub->mini, x, y, 0xff0000ff);
			else
				mlx_put_pixel(cub->mini, x, y, 0xff00ffff);	
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
