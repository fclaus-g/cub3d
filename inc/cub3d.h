#ifndef CUB3D_H
# define CUB3D_H

#include <math.h>
#include "../MLX42/include/MLX42/MLX42.h"
#include "../lib/libft/libft.h"
#include "../lib/get_next_line/get_next_line.h"

# define PI M_PI
# define PIX 64 //tamaño de cada cuadro de la cuadricula
# define MOV 4 //velocidad de movimiento del player
# define VISION_ANGLE PI / 3
# define PLAYER_MINIMAP_SIZE 64
# define CUB3D_EXTENSION ".cub"

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_scene_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	t_rgb	floor;
	t_rgb	ceil;
}	t_scene_textures;

typedef struct s_map
{
	t_list			*lines;
	char			**map;
	int				left_padding;
	int				rows;
	int				cols;
	int				w_px;
	int				h_px;
}	t_map;

typedef struct scene
{
	t_scene_textures	textures;
	t_map				map;
}	t_scene;

// typedef struct s_coord
// {
// 	int	x;
// 	int	y;
// }	t_coord;

typedef struct splayer
{
	double		x;
	double		y;
	double		angle;
}				t_player;

typedef struct s_cub3d
{
	t_scene		scene;
	t_map		map;
	t_player	player;
}	t_cub3d;

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
void ft_draw_ray(t_game *cub);

/*-----------[paint_map_2d]----------------*/
void ft_init_map2d(t_game *cub);
void ft_load_images(t_game *cub);
void ft_render_wall_and_floor(t_game *cub);
void ft_render_player(t_game *cub);
double	ft_player_lookat_angle(char c);

/*-----------[moves]-----------------------*/
void ft_keys_moves(t_game *cub);
void ft_move_up(t_game *cub);
void ft_move_down(t_game *cub);
void ft_move_left(t_game *cub);
void ft_move_right(t_game *cub);

void ft_hook(void *param);

/*-----------[utils]-----------------------*/
void	print_player_position(t_game *cub);

/*-----------[map_validation]--------------*/
void	show_error(char *msg);
int		validate_scene(char *path, t_cub3d *cub);
void	free_matrix(char **matrix);
void	print_scene(t_cub3d *cub);
#endif
