#ifndef CUB3D_H
# define CUB3D_H

#include <math.h>
#include "../MLX42/include/MLX42/MLX42.h"
#include "../lib/libft/libft.h"
#include "../lib/get_next_line/get_next_line.h"

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define HEIGHT 1080
# define WIDTH 1920
# define GRID_SIZE 64 //tamaño de cada cuadro de la cuadricula
# define MOV 4	//velocidad de movimiento del player
# define VISION_ANGLE M_PI / 3
# define CUB3D_EXTENSION ".cub"
# define SCENE_SPACES " \t"
// # define SCENE_MAP_CHARS "01NSWE"
# define MAP_FILL_SPACE ' '
# define NUM_RAYS 120

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
	int					map_read_end;
}	t_scene;

// typedef struct s_coord
// {
// 	int	x;
// 	int	y;
// }	t_coord;

typedef struct splayer
{
	double		x_pix;
	double		y_pix;
	double		angle;
}				t_player;

// typedef struct s_window
// {
// 	void		*mlx;
// 	mlx_image_t	*canvas;
// 	t_minimap	mini;
// }	t_windows;

// typedef struct s_map3d
// {
// 	int		rows;
// 	int		cols;
// 	char	**map;
// }	t_map3d;

typedef struct s_minimap
{
	mlx_image_t	*canvas;
	int			w;
	int			h;
}	t_minimap;

typedef struct s_plane
{
	double		x;
	double		y;
}	t_plane;

typedef struct s_ray
{
	int		x;
	int		y;
}	t_ray;

typedef struct s_dir
{
	double	x;
	double	y;
}	t_dir;

typedef	struct cub3d
{
	t_map		map;
	t_player	player;
	t_scene		scene;
	void		*window;
	mlx_image_t	*window_canvas;
	t_minimap	mini;
	t_plane		plane;
	t_dir		dir;
	t_ray		ray;
}	t_cub3d;


// typedef struct s_game
// {
// 	void *mlx;
// 	t_map map;
// 	t_player player;

// 	double dir_x;
// 	double dir_y;
// 	double plane_x;
// 	double plane_y;
// 	double fov;
// 	double foto;
// 	double old_foto;
// 	double camera_x;
// typedef struct s_game
// {
// 	void *mlx;
// 	t_map map;
// 	t_player player;

// 	int x_p;
// 	int y_p;
// 	int ins_floor;
// 	int ins_wall;
// 	int mini_w;
// 	int mini_h;

// 	mlx_image_t *mini;
// 	mlx_image_t *wall;
// 	mlx_image_t *floor;
// 	mlx_image_t *plyr;
// 	mlx_image_t *pantalla;
// }				t_game;

void ft_init_data(t_cub3d *cub);
/*----------[paint_minimap]----------------*/
void ft_init_minimap(t_cub3d *cub);
void	ft_init_map(t_cub3d *cub);
void ft_draw_map(t_cub3d *cub);
void ft_draw_square(mlx_image_t *canvas, int y, int x, int color);
void ft_draw_player(mlx_image_t *canvas, int y, int x, int color);
void ft_draw_ray(t_cub3d *cub);
void ft_paint_floor_and_ceiling(t_cub3d *cub);

/*-----------[paint_map_2d]----------------*/
void ft_init_map2d(t_cub3d *cub);
void ft_load_images(t_cub3d *cub);
void ft_render_wall_and_floor(t_cub3d *cub);
void ft_render_player(t_cub3d *cub);
double	ft_player_lookat_angle(char c);
//void ft_render_wall(t_cub3d *cub, int x, int y, double angle);
//void ft_draw_wall(t_cub3d *cub, int rays);

/*-----------[moves]-----------------------*/
void ft_keys_moves(t_cub3d *cub);
void ft_move_up(t_cub3d *cub);
void ft_move_down(t_cub3d *cub);
void ft_move_left(t_cub3d *cub);
void ft_move_right(t_cub3d *cub);
void ft_hook(void *param);

/*-----------[utils]-----------------------*/
void	print_player_position(t_cub3d *cub);

/*-----------[map_validation]--------------*/
void	show_error(char *msg);
int		validate_scene(char *path, t_cub3d *cub);
void	free_matrix(char **matrix);
void	print_scene(t_cub3d *cub);
int		starts_with_and_space(char *line, char *start);
#endif
