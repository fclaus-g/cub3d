/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:51:30 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/06/05 20:13:41 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void ft_init_struct(t_game *cub)
{
	cub->player.x = 0;
	cub->player.y = 0;
	cub->player.angle = 0;
	cub->mlx = NULL;
	cub->map.map = NULL;
	cub->map.weigth = 0;
	cub->map.width = 0;
}

void ft_init_minimap(t_game *cub)
{
	int i;
	int j;
	mlx_image_t *img;

	img = mlx_new_image(cub->mlx, cub->map.weigth * PIX, cub->map.width * PIX);
	i = 0;
	while (cub->map.map[i])
	{
		j = 0;
		while (cub->map.map[i][j])
		{
			if (cub->map.map[i][j] == '1')
				mlx_put_pixel(img, j * PIX, i * PIX, 0x00FF0000);
			else if (cub->map.map[i][j] == '0')
				mlx_put_pixel(img, j * PIX, i * PIX, 0x00000000);
			else if (cub->map.map[i][j] == 'P')
				mlx_put_pixel(img, j * PIX, i * PIX, 0x0000FF00);
			j++;
		}
		i++;
	}
	mlx_delete_image(cub->mlx, img);
}