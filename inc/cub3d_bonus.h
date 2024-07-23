#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"
# include "../lib/get_next_line/get_next_line.h"

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define HEIGHT 1080
# define WIDTH 1920
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

typedef struct s_rgb_texture
{
	t_rgb	color;
	char	*path;
}	t_rgb_texture;

typedef struct s_scene_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	t_rgb	floor;
	t_rgb	ceil;
	char	*floor_path;
	char	*ceil_path;
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

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

typedef struct splayer
{
	char		orient;
	double		x_pix;
	double		y_pix;
	float		x;
	float		y;
	double		angle;
	float		dir_x;
	float		dir_y;
	double		plane_x;
	double		plane_y;
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
	mlx_image_t	*micro;
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

typedef struct cub3d
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
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
	mlx_texture_t	*floor;
	mlx_texture_t	*ceil;
	mlx_texture_t	*hand;
	mlx_texture_t	*sprite1;
	mlx_texture_t	*sprite2;
	mlx_texture_t	*sprite3;
	double			cursor_x;
	int				timer;
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

/*-----------[bonus]----------------*/
void			ft_paint_hand(t_cub3d *cub);
void			ft_render_floor_and_ceiling(t_cub3d *cub);
void			ft_paint_stats(t_cub3d *cub, mlx_texture_t *sprite);

/*----------[minimap]----------------*/
void			ft_init_minimap(t_cub3d *cub);
void			ft_draw_map(t_cub3d *cub);
void			ft_draw_square(mlx_image_t *canvas, int y, int x, int color);
void			ft_draw_player(mlx_image_t *canvas, int y, int x, int color);
void			ft_draw_ray(t_cub3d *cub);

/*-----------[moves]-----------------------*/
void			ft_keys_moves(t_cub3d *cub);
void			ft_move_up(t_cub3d *cub);
void			ft_move_down(t_cub3d *cub);
void			ft_move_left(t_cub3d *cub);
void			ft_move_right(t_cub3d *cub);

/*-----------[collision]----------------*/
int				ft_check_collision(t_cub3d *cub, double y, double x);

/*-----------[player]----------------*/
double			ft_player_lookat_angle(char c);
void			print_player_position(t_cub3d *cub);
void			ft_refresh_player(t_player *player, int girar);
void			ft_player_orientation(t_player *player);
void			ft_rotate_player(t_cub3d *cub, int direction);

/*-----------[map_validation]--------------*/
void			show_error(char *msg);
int				validate_scene(char *path, t_cub3d *cub);
void			print_scene(t_cub3d *cub);
int				starts_with_and_space(char *line, char *start);

/*-----------[minimap]-----------------------*/
void			ft_init_minimap(t_cub3d *cub);
void			ft_draw_map(t_cub3d *cub);
void			ft_draw_square(mlx_image_t *canvas, int y, int x, int color);
void			ft_draw_player(mlx_image_t *canvas, int y, int x, int color);
void			ft_draw_ray(t_cub3d *cub);

/*-----------[raycaster]----------------*/
void			ft_raycaster(t_cub3d *cub);
void			ft_prepare_ray(t_cub3d *cub, int x);
void			ft_calc_hipotenusa(t_ray *ray);
void			ft_calc_player_hipotenusa(t_cub3d *cub);
void			ft_dda(t_cub3d *cub);

/*-----------[textures]----------------*/
mlx_texture_t	*ft_choice_texture(t_cub3d *cub);
uint32_t		transform_color(uint32_t color);
uint32_t		get_pixel_color_from_texture(mlx_texture_t *texture, int x, int y);
void			ft_load_textures(t_cub3d *cub);

/*-----------[walls]----------------*/
void			ft_wall_distance(t_cub3d *cub);
void			ft_wall_height(t_cub3d *cub);
void			ft_paint_wall(t_cub3d *cub, int x);
void			ft_init_ray_data(t_cub3d *cub);

/*-----------[utils]----------------*/
void			ft_print_player(t_cub3d *cub);
void			ft_init_ray_data(t_cub3d *cub);
void			ft_print_ray_data(t_cub3d *cub);
void			free_cub(t_cub3d *cub);
void			ft_delete_textures(t_cub3d *cub);

/*-----------[view]----------------*/
void			ft_init_view(t_cub3d *cub);
uint32_t		rgb_to_uint32(t_rgb rgb);
void			ft_paint_floor_and_ceiling(t_cub3d *cub);

/*-----------[walls]----------------*/
void			ft_wall_distance(t_cub3d *cub);
void			ft_wall_height(t_cub3d *cub);
uint32_t		ft_wall_color(t_cub3d *cub);
void			ft_paint_wall(t_cub3d *cub, int x);
void			ft_wall_x(t_cub3d *cub);

/*-----------[parser/init]----------------*/
void			init_cub(t_cub3d *cub);

/*-----------[parser/scene]----------------*/
int				read_and_parse_scene(char *path, t_cub3d *cub);

/*-----------[parser/validation]----------------*/
int				validate_scene_line(char *line, t_cub3d *cub);

/*-----------[parser/color_textures]----------------*/
int				validate_color_line(char *line, t_rgb *color);
int				validate_texture_line(char *line, char **texture);

/*-----------[parser/fill_map]----------------*/
void			fill_map_matrix(t_cub3d *cub);

/*-----------[parser/utils]----------------*/
int				file_is_reachable(char *path);
int				check_if_map_is_closed(t_cub3d *cub);
void			locate_player(t_cub3d *cub);
void			end_read_fd(int fd);

/*-----------[parser/is]----------------*/
int				is_empty_line(char *line);
int				is_valid_rgb(t_rgb *color);
int				is_numeric(char *str);

/*-----------[parser/is_map]----------------*/
int				is_map_space(char c);
int				is_map_element(char c);
int				is_map_player(char c);
int				is_map_character(char c);
int				is_map_line(char *line);

/*-----------[parser/errors]----------------*/
void			show_error_free(char *msg1, char *msg2, int msg_clean);
void			show_error_and_exit(char *msg, int exit_code);

/*-----------[parser/strings]----------------*/
void			free_matrix(char **matrix);
int				matrix_len(char **matrix);
int				starts_with_and_space(char *line, char *start);

/*-----------[bonus/hooks]----------------*/
void			ft_cursor_hook(double x, double y, void *param);

#endif
