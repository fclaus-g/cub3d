#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"
# include "../lib/get_next_line/get_next_line.h"

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define HEIGHT 720
# define WIDTH 1280
# define GRID_SIZE 64 //tamaño de cada cuadro de la cuadricula

# define MOV 2	//velocidad de movimiento del player
# define ROT_SPEED 0.06 //velocidad de rotacion del player
# define OFFSET 17
# define VISION_ANGLE M_PI / 3
# define CUB3D_EXTENSION ".cub"
# define SCENE_SPACES " \t"
// # define SCENE_MAP_CHARS "01NSWE"
# define MAP_FILL_SPACE ' '
# define NUM_RAYS 120
# define INFINITE 1e30

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
	
	char 		orient;
	double		x_pix;
	double		y_pix;
	float		x;
	float		y;
	double		angle;
	float		dir_x;
	float		dir_y;
	double 		plane_x;
	double 		plane_y;
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
	int			x;
	int			y;
	float		dir_x;
	float		dir_y;
	float		camera_x;
	int			map_x;
	int			map_y;
	float		delta_dist_x;
	float		delta_dist_y;
	int			step_x;
	int			step_y;
	float		side_dist_x;
	float		side_dist_y;
	int			hit;
	int			side;
	float		perp_wall_dist;
	int			line_height;
	int			start_wall;
	int			end_wall;
	int			real_start_wall;
	int			real_end_wall;
	uint32_t	wall_color;
	float		wall_x;
}	t_ray;

typedef struct s_dir
{
	double	x;
	double	y;
}	t_dir;

typedef struct	cub3d
{
	t_map			map;
	t_player		player;
	t_scene			scene;
	void			*window;
	mlx_image_t		*window_canvas;
	mlx_image_t		*wall;
	t_minimap		mini;
	t_plane			plane;
	t_ray			ray;
	mlx_texture_t	*NO;
	mlx_texture_t	*SO;
	mlx_texture_t	*WE;
	mlx_texture_t	*EA;
	mlx_texture_t	*floor;
	mlx_texture_t	*ceil;
	mlx_texture_t	*hand;
}				t_cub3d;


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
void	ft_init_view(t_cub3d *cub);
void ft_draw_map(t_cub3d *cub);
void ft_draw_square(mlx_image_t *canvas, int y, int x, int color);
void ft_draw_player(mlx_image_t *canvas, int y, int x, int color);
void ft_draw_ray(t_cub3d *cub);
void ft_paint_floor_and_ceiling(t_cub3d *cub);

/*-----------[paint_map_2d]----------------*/
void ft_init_view2d(t_cub3d *cub);
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

/*-----------[raycasting.c]----------------*/
void ft_raycast(t_cub3d *cub);
void ft_player_orientation(t_player *player);
void ft_prepare_ray(t_cub3d *cub, int x);
void ft_calc_hipotenusa(t_ray *ray);
void ft_calc_player_hipotenusa(t_cub3d *cub);
void ft_dda(t_cub3d *cub);
void ft_wall_distance(t_cub3d *cub);
void ft_wall_height(t_cub3d *cub);
void ft_paint_wall(t_cub3d *cub, int x);
void ft_init_ray_data(t_cub3d *cub);

void ft_print_linea(t_cub3d *cub);
void ft_print_algo(t_cub3d *cub, int x);
void ft_print_player(t_cub3d *cub);
void ft_refresh_player(t_player *player, int girar);
void ft_print_ray_data(t_cub3d *cub);
void ft_raycaster(t_cub3d *cub);
void ft_init_player(t_cub3d *cub);
void ft_load_textures(t_cub3d *cub);
// uint32_t ft_get_pixel_texture(t_cub3d *cub, int x, int y);
uint32_t	get_pixel_color_from_texture(mlx_texture_t *texture, int x, int y);
void		ft_wall_x(t_cub3d *cub);
void ft_paint_wall(t_cub3d *cub, int x);
void ft_init_ray_data(t_cub3d *cub);
uint32_t ft_wall_color(t_cub3d *cub);
mlx_texture_t *ft_choice_texture(t_cub3d *cub);
void ft_paint_floor_and_ceiling(t_cub3d *cub);
int ft_check_collision(t_cub3d *cub, double y, double x);
void ft_paint_hand(t_cub3d *cub);
void ft_render_floor_and_ceiling(t_cub3d *cub);
#endif
