#ifndef CUB3D_H
# define CUB3D_H

#include <math.h>
#include "../MLX42/include/MLX42/MLX42.h"
#include "../lib/libft/libft.h"
#include "../lib/get_next_line/get_next_line.h"
#include "../lib/ft_printf/ft_printf.h"

# define PI M_PI
# define PIX 64
# define MOV 4
# define VISION_ANGLE PI / 3

typedef struct s_map
{
	char		**map;
	int		rows;
	int		cols;
	int		w_px;
	int		h_px;
}				t_map;

typedef struct splayer
{
	int		x;
	int		y;
	double	angle;
}				t_player;

typedef struct s_game
{
	void *mlx;
	t_map map;
	t_player player;

	int x_p;
	int y_p;
	int ins_floor;
	int ins_wall;
	int mini_w;
	int mini_h;

	mlx_image_t *mini;
	mlx_image_t *wall;
	mlx_image_t *floor;
	mlx_image_t *plyr;
}				t_game;

void ft_init_data(t_game *cub);
/*----------[paint_minimap]----------------*/
void ft_init_minimap(t_game *cub);
void ft_draw_map(t_game *cub);
void ft_draw_square(mlx_image_t *canvas, int y, int x, int color);
void ft_draw_player(mlx_image_t *mini, int y, int x, int color);

/*-----------[paint_map_2d]----------------*/
void ft_init_map2d(t_game *cub);
void ft_load_images(t_game *cub);
void ft_render_wall_and_floor(t_game *cub);
void ft_render_player(t_game *cub);

/*-----------[moves]-----------------------*/
void ft_keys_moves(t_game *cub);
void ft_move_up(t_game *cub);
void ft_move_down(t_game *cub);
void ft_move_left(t_game *cub);
void ft_move_right(t_game *cub);


void ft_hook(void *param);
#endif

