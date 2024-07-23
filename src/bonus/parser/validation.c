#include "../../../inc/cub3d_bonus.h"

/**
 * Validates scene extension. File must have CUB3D_EXTENSION extension.
 * ".cub" is allowed to be in any case.
 */
static int	validate_scene_extension(char *path)
{
	size_t	ext_len;

	ext_len = ft_strlen(CUB3D_EXTENSION);
	if (ft_strlen(path) < ext_len
		|| ft_strncmp(path + ft_strlen(path) - ext_len,
			CUB3D_EXTENSION, ext_len) != 0)
	{
		show_error("Invalid scene file extension.");
		return (0);
	}
	return (1);
}

/**
 * @brief 
 * 
 * @param cub cub3d struct
 * @param line 
 */
static void	do_map_calculations_with_new_line(t_cub3d *cub, char *line)
{
	int	i;
	int	len;

	cub->map.rows++;
	i = 0;
	len = ft_strlen(line);
	while (line[i] && is_map_space(line[i]))
		i++;
	if (cub->map.left_padding < 0 || i < cub->map.left_padding)
		cub->map.left_padding = i;
	i = len - 1;
	while (i >= 0 && is_map_space(line[i]))
		i--;
	if (!cub->map.cols || cub->map.cols < (i + 1))
		cub->map.cols = i + 1;
}

static int	validate_map_line(char *line, t_cub3d *cub)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!is_map_character(line[i]))
		{
			show_error("Invalid character in map.");
			return (0);
		}
		if (is_map_player(line[i]))
		{
			if (cub->player.angle != -1)
			{
				show_error("Multiple player characters in map.");
				return (0);
			}
			cub->player.angle = ft_player_lookat_angle(line[i]);
			ft_player_orientation(&cub->player);
		}
		i++;
	}
	ft_lstadd_back(&cub->map.lines, ft_lstnew(ft_strdup(line)));
	do_map_calculations_with_new_line(cub, line);
	return (1);
}

int	validate_scene_line(char *line, t_cub3d *cub)
{
	if ((is_empty_line(line) || !is_map_line(line)) && cub->map.rows)
		cub->scene.map_read_end = 1;
	if (is_empty_line(line))
		return (1);
	else if (cub->scene.map_read_end)
	{
		show_error_free(line, ": Invalid line after map.\n", 0);
		return (0);
	}
	if (starts_with_and_space(line, "NO"))
		return (validate_texture_line(line, &cub->scene.textures.no));
	if (starts_with_and_space(line, "SO"))
		return (validate_texture_line(line, &cub->scene.textures.so));
	if (starts_with_and_space(line, "WE"))
		return (validate_texture_line(line, &cub->scene.textures.we));
	if (starts_with_and_space(line, "EA"))
		return (validate_texture_line(line, &cub->scene.textures.ea));
	if (starts_with_and_space(line, "F"))
		return (validate_color_line(line + 2, &cub->scene.textures.floor));
	if (starts_with_and_space(line, "C"))
		return (validate_color_line(line + 2, &cub->scene.textures.ceil));
	return (validate_map_line(line, cub));
}

int	validate_scene(char *path, t_cub3d *cub)
{
	if (!validate_scene_extension(path))
		return (0);
	if (!file_is_reachable(path))
	{
		show_error("Scene file not found or without permissions.");
		return (0);
	}
	if (!read_and_parse_scene(path, cub))
		return (0);
	return (1);
}
