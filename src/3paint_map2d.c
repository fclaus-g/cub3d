/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3paint_map2d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:04:03 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/06/12 17:32:59 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void ft_init_map2d(t_game *cub)
{
	ft_load_images(cub);
	ft_printf("Inicializando mapa\n");
	ft_render_wall_and_floor(cub);
	ft_render_player(cub);

}

void ft_load_images(t_game *cub)
{
	mlx_texture_t *aux;

	aux = malloc(sizeof(mlx_texture_t));
	aux = mlx_load_png("texture/E.png");
	cub->wall = mlx_texture_to_image(cub->mlx, aux);
	mlx_delete_texture(aux);
	aux = mlx_load_png("texture/Nbyn.png");
	cub->floor = mlx_texture_to_image(cub->mlx, aux);
	mlx_delete_texture(aux);
	aux = mlx_load_png("texture/0.png");
	cub->player = mlx_texture_to_image(cub->mlx, aux);
	mlx_delete_texture(aux);
}

void ft_render_wall_and_floor(t_game *cub)
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
			{
				mlx_image_to_window(cub->mlx, cub->wall, x * PIX, y * PIX);
				mlx_set_instance_depth(&cub->wall->instances[cub->ins_wall], 5);
				cub->ins_wall++;
			}
			else if (cub->map.map[y][x] == '0' || cub->map.map[y][x] == 'P')
			{
				mlx_image_to_window(cub->mlx, cub->floor, x * PIX, y * PIX);
				mlx_set_instance_depth(&cub->floor->instances[cub->ins_floor], 1);
				cub->ins_floor++;
			}
		}
	}
}

void  ft_render_player(t_game *cub)
{
	mlx_image_to_window(cub->mlx, cub->player, cub->x_p * PIX, cub->y_p * PIX);
	mlx_set_instance_depth(&cub->player->instances[0], 10);
}