/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:11:34 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/06/05 20:01:11 by fclaus-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "../MLX42/include/MLX42/MLX42.h"
#include "../lib/libft/libft.h"
#include "../lib/get_next_line/get_next_line.h"
#include "../lib/ft_printf/ft_printf.h"

# define PIX 64//tamaño de cada cuadro de la cuadricula
# define MOV 4//velocidad de movimiento del player


//ESTRUCTURAS
typedef struct s_pdv
{
	float x;//horizontal
	float y;//vertical
	float angle;
} t_pdv;

typedef struct s_map
{
	int weigth;//ancho
	int width;//alto
	char **map;
} t_map;

typedef struct s_game
{
	mlx_t *mlx;
	t_map map;
	t_pdv player;
	
} t_game;

//FUNCIONES
void ft_hook(void *mlx);
void ft_init_struct(t_game *cub);
void ft_init_minimap(t_game *cub);
#endif