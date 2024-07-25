#include "../inc/cub3d.h"

static void init_cub_values(t_cub3d *cub)
{
	cub->wall = NULL;
	cub->mini.canvas = NULL;
	cub->plane.x = 0;
	cub->plane.y = 0;
	cub->ray.dir_x = 0;
	cub->ray.dir_y = 0;
	cub->ray.camera_x = 0;
	cub->ray.map_x = 0;
	cub->ray.map_y = 0;
	cub->ray.delta_dist_x = 0;
	cub->ray.delta_dist_y = 0;
	cub->ray.step_x = 0;
	cub->ray.step_y = 0;
	cub->ray.side_dist_x = 0;
	cub->ray.side_dist_y = 0;
	cub->ray.hit = 0;
	cub->ray.side = 0;
	cub->ray.perp_wall_dist = 0;
	cub->ray.line_height = 0;
	cub->ray.start_wall = 0;
	cub->ray.end_wall = 0;
	cub->cursor_x = 0;

}

static void	init_scene(t_cub3d *cub)
{
	cub->scene.textures.no = NULL;
	cub->scene.textures.so = NULL;
	cub->scene.textures.we = NULL;
	cub->scene.textures.ea = NULL;
	cub->scene.textures.floor.r = -1;
	cub->scene.textures.floor.g = -1;
	cub->scene.textures.floor.b = -1;
	cub->scene.textures.ceil.r = -1;
	cub->scene.textures.ceil.g = -1;
	cub->scene.textures.ceil.b = -1;
	cub->scene.map_read_end = 0;
	cub->map.map = NULL;
	cub->map.lines = NULL;
	cub->map.left_padding = -1;
	cub->map.rows = 0;
	cub->map.cols = 0;
}

static void	init_textures(t_cub3d *cub)
{
	cub->no = NULL;
	cub->so = NULL;
	cub->we = NULL;
	cub->ea = NULL;
}

static void	init_player(t_cub3d *cub)
{
	cub->player.init_orient = 0;
	cub->player.x_pix = 0;
	cub->player.y_pix = 0;
	cub->player.x = 0;
	cub->player.y = 0;
	cub->player.angle = -1;
	cub->player.dir_x = 0;
	cub->player.dir_y = 0;
	cub->player.plane_x = 0;
	cub->player.plane_y = 0;
	cub->player.fov = M_PI / 3;
}

void	init_cub(t_cub3d *cub)
{
	cub->wall = NULL;
	cub->window = NULL;
	cub->mini.canvas = NULL;
	init_cub_values(cub);
	init_textures(cub);
	init_player(cub);
	init_scene(cub);
}
