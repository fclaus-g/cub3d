/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fclaus-g <fclaus-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 11:11:34 by fclaus-g          #+#    #+#             */
/*   Updated: 2024/06/03 12:24:37 by fclaus-g         ###   ########.fr       */
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

typedef struct s_box
{
	char		**map;//matriz del mapa
	char		**map2;//copia del mapa
	int			alto;//altura del mapa
	int			ancho;//anchura del mapa
	//contadores
	int			coins;//contador de coleccionables recogidos
	int			col;//contador de coleccionables puestos en mapa
	int			movs;//contador de movimientos en pixeles
	int			moves;//contador de movs en cuadricula 
	int			exit;//contador de salidas
	int			p_pos;//num de entradas
	int			floor;//num de floor
	int			wall;//num de wall
	
	//posicion del player
	int			x_pos;//posicion x del player (horizontal)
	int			y_pos;//posicion y del player (vertical)

	//frames para las animaciones
	int			F_frame;//frame del floor
	int			C_frame;//frame del collectible
	int			P_frame;//frame del player
	int			E_frame;//frame del exit

	//estructuras de mlx
	mlx_t 		*mlx;//estructura de mlx
	mlx_image_t	*Pr_img1;//estructura de imagen del player donde guardamos la imagen renderizada
	mlx_image_t	*Pl_img1;//izquierda
	mlx_image_t	*F_img1;//estructura de imagen del floor donde guardamos la imagen renderizada
	mlx_image_t	*W_img;//estructura de imagen del wall donde guardamos la imagen renderizada
	mlx_image_t	*C_img1;//estructura de imagen del collectible donde guardamos la imagen renderizada
	mlx_image_t	*E_img1;//estructura de imagen del exit donde guardamos la imagen renderizada
	mlx_image_t	*E_img4;
}		t_box;

//FUNCIONES
//1main.c
void	ft_moves_control(t_box *box);
void 	ft_hook(void *param);

//2utils.c
void	ft_check_empty_line(char *str);
void	ft_readsave_map(char *str, t_box *box);
int		ft_mtrlen(char **matriz);
void	ft_initbox(t_box *box);
void	ft_printmap(char **map);

//3checkin.c 
int		ft_check_elements(t_box *box);
void	ft_element_count(char c, t_box *box, int y, int x);
int		ft_checkin_arg(int ac, char *str);
int		ft_checkforma(t_box *box);
void	ft_checkmap(t_box *box);

//3checkin2.c
int		ft_check_walls(t_box *box);
int		ft_way_ok(t_box *box);
void	ft_flood_fill(t_box *box, int y, int x);

//4load_images.c
void	ft_load_images(t_box *box);
void	ft_load_floor_and_wall(t_box *box);
void	ft_load_col(t_box *box);
void	ft_load_player(t_box *box);
void	ft_load_exit(t_box *box);

//5render_images.c 
void	ft_render_floor(t_box *box);
void	ft_render_wall(t_box *box);
void	ft_init_imgs(t_box *box);

//5render_images2.c
void	ft_render_col(t_box *box);
void	ft_render_exit(t_box *box);
void	ft_render_player(t_box *box);

//6player_moves.c 
void	ft_move_P_y(t_box *box, int direccion);
void	ft_move_P_x(t_box *box, int direccion);
void 	ft_key_control(t_box *box);
void 	ft_player_direction(t_box *box, char c);
 
//6player_moves2.c
void 	ft_move_up(t_box *box);
void 	ft_move_down(t_box *box);
void 	ft_move_left(t_box *box);
void 	ft_move_right(t_box *box);

//8collectable.c
void	ft_open_door(t_box *box);
void	ft_quit_col(t_box *box, int y, int x);

//9finish
void	ft_check_finish(t_box *box, int y, int x);//29lineas
void	ft_free_matrix(char **matrix);
void	ft_free_so_long(t_box *box);
void 	ft_win(void);


#endif