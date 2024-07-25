#include "../inc/cub3d.h"

static void init_cub_values(t_cub3d *cub)
{
	cub->wall = NULL;
	cub->mini.canvas = NULL;
	cub->plane.x = 0;
	cub->plane.y = 0;
	cub->ray.dir.x = 0;
	cub->ray.dir.y = 0;
	cub->ray.camera_x = 0;
	cub->ray.map.x = 0;
	cub->ray.map.y = 0;
	cub->ray.delta_dist.x = 0;
	cub->ray.delta_dist.y = 0;
	cub->ray.step.x = 0;
	cub->ray.step.y = 0;
	cub->ray.side_dist.x = 0;
	cub->ray.side_dist.y = 0;
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
	cub->player = (t_player) {
		.init_pos = {0, 0},
		.init_orient = 0,
		.pos = {0, 0},
		.dir = {0, 0},
		.plane = {0, 0},
		.angle = -1,
		.fov = M_PI / 3
	};
}

void	init_cub(t_cub3d *cub)
{
	cub->map = (t_map) {
		.lines = NULL,
		.map = NULL,
		.left_padding = -1,
		.rows = 0,
		.cols = 0
	};
	cub->wall = NULL;
	cub->window = NULL;
	cub->mini.canvas = NULL;
	init_cub_values(cub);
	init_textures(cub);
	init_player(cub);
	init_scene(cub);
}
