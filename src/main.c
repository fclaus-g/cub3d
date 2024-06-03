/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:19:56 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/06/03 12:38:38 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void ft_hook(void *mlx)
{
	(void)mlx;
}

int main (void)
{
	mlx_t	*mlx;

	printf("Hello World\n");
	mlx = mlx_init(1024, 768, "Cub3D", 0);
	mlx_loop_hook(mlx, &ft_hook, &mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}