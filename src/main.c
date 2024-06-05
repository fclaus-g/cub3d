/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:19:56 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/06/05 20:01:43 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void ft_hook(void *mlx)
{
	(void)mlx;
}

int main (void)
{
	t_game cub;

    char *temp_map[5] = {
		"1111111111111111111111111",
		"1000000000000000000000001",
		"1000000000111000000000001",
		"1000000P00000000000000001",
		"1111111111111111111111111"
	};
	cub.map.map = temp_map;
	ft_init_struct(&cub);
	ft_init_minimap(&cub);
	printf("Hello World\n");
	cub.mlx = mlx_init(1024, 768, "Cub3D", 0);
	mlx_loop_hook(cub.mlx, &ft_hook, &cub);
	mlx_loop(cub.mlx);
	mlx_terminate(cub.mlx);
	return (0);
}