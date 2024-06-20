#include "../inc/cub3d.h"

void	init_scene(t_cub3d *cub)
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
	cub->map.map = NULL;
	cub->map.lines = NULL;
	cub->player.angle = -1;
}

void	show_error_free(char *msg1, char *msg2, int msg_clean)
{
	char *error;

	error = ft_strjoin(msg1, msg2);
	perror(error);
	free(error);
	if (msg_clean == 1)
		free(msg1);
	else if (msg_clean == 2)
		free(msg2);
	else if (msg_clean == 3)
	{
		free(msg1);
		free(msg2);
	}
}

void	show_error(char *msg)
{
	char *error;

	error = ft_strjoin("Error\n", msg);
	perror(error);
	// free(error);
}

int	is_map_space(char c)
{
	return (c == ' ');
}

int	is_map_element(char c)
{
	return (c == '0' || c == '1');
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!is_map_space(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_map_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

int	is_map_character(char c)
{
	return (is_map_space(c) || is_map_element(c) || is_map_player(c));
}

/**
 * Validates scene extension. File must have CUB3D_EXTENSION extension.
 * ".cub" is allowed to be in any case.
 */
int	validate_scene_extension(char *path)
{
	size_t	ext_len;

	ext_len = ft_strlen(CUB3D_EXTENSION);
	if (ft_strlen(path) < ext_len
		|| ft_strncmp(path + ft_strlen(path) - ext_len, CUB3D_EXTENSION, ext_len) != 0) {
		show_error("Invalid scene file extension.");
		return (0);
	}
	return (1);
}

int	file_is_reachable(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!is_map_space(line[i]) && !is_map_element(line[i]) && !is_map_player(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	validate_map_line(char *line, t_cub3d *cub)
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
		}
		i++;
	}
	ft_lstadd_back(&cub->map.lines, ft_lstnew(ft_strdup(line)));
	return (1);
}

int	is_cardinal_line(char *line)
{
	if (ft_strlen(line) < 4)
		return (0);
	return ((ft_strncmp(line, "NO", 2) == 0
			|| ft_strncmp(line, "SO", 2) == 0
			|| ft_strncmp(line, "WE", 2) == 0
			|| ft_strncmp(line, "EA", 2) == 0)
		&& is_map_space(line[2]));
}

void	free_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int	matrix_len(char **matrix)
{
	int	len;

	len = 0;
	if (!matrix)
		return (len);
	while (matrix[len] != NULL)
		len++;
	return (len);
}

int	validate_texture_line(char *line, char **texture)
{
	char	**texture_components;
	char	*path;

	if (*texture != NULL)
	{
		show_error("Duplicate texture line.");
		return (0);
	}
	texture_components = ft_split(line, ' ');
	if (matrix_len(texture_components) != 2)
	{
		free_matrix(texture_components);
		show_error("Invalid texture line.");
		return (0);
	}
	path = ft_strtrim(texture_components[1], " ");
	free_matrix(texture_components);
	if (!path)
	{
		show_error("Failed to allocate memory for texture path.");
		return (0);
	}
	*texture = path;
	return (1);
}

int is_scene_completed_without_map(t_cub3d *cub)
{
	return (cub->scene.textures.no != NULL
		&& cub->scene.textures.so != NULL
		&& cub->scene.textures.we != NULL
		&& cub->scene.textures.ea != NULL
		&& cub->scene.textures.floor.r != -1
		&& cub->scene.textures.ceil.r != -1);
}

int	is_scene_completed(t_cub3d *cub)
{
	return (is_scene_completed_without_map(cub)
		&& cub->map.map != NULL
		&& cub->player.angle != -1);
}

void	ft_lstprint(void *str)
{
	printf("%s\n", (char *)str);
}

void	print_scene(t_cub3d *cub)
{
	printf("NO: %s\n", cub->scene.textures.no);
	printf("SO: %s\n", cub->scene.textures.so);
	printf("WE: %s\n", cub->scene.textures.we);
	printf("EA: %s\n", cub->scene.textures.ea);
	printf("F: %d, %d, %d\n", cub->scene.textures.floor.r, cub->scene.textures.floor.g, cub->scene.textures.floor.b);
	printf("C: %d, %d, %d\n", cub->scene.textures.ceil.r, cub->scene.textures.ceil.g, cub->scene.textures.ceil.b);
	printf("Lines:\n");
	ft_lstiter(cub->map.lines, &ft_lstprint);
	printf("Map:\n");
	if (cub->map.map == NULL)
		printf("NULL\n");
	else {
		for (int i = 0; cub->map.map[i] != NULL; i++)
			printf("%s\n", cub->map.map[i]);
	}
}

int	is_valid_rgb(t_rgb *color)
{
	if (color->r < 0 || color->r > 255)
		return (0);
	if (color->g < 0 || color->g > 255)
		return (0);
	if (color->b < 0 || color->b > 255)
		return (0);
	return (1);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * Validates color component value.
 * 
 * @return -1 if invalid color component, color (0-255) if valid.
 */
int color_component_value(char *component)
{
	char	*trimmed;
	int		color_quantity;

	trimmed = ft_strtrim(component, " ");
	if (!is_numeric(trimmed))
	{
		free(trimmed);
		return (-1);
	}
	color_quantity = ft_atoi(trimmed);
	if (color_quantity < 0 || color_quantity > 255)
		return (-1);
	return (color_quantity);
}

int	validate_color_line(char *line, t_rgb *color)
{
	char	**color_components;

	if (color->r != -1)
	{
		show_error("Duplicate color line.");
		return (0);
	}
	color_components = ft_split(line, ',');
	if (matrix_len(color_components) != 3)
	{
		free_matrix(color_components);
		show_error("Invalid color line.");
		return (0);
	}
	color->r = color_component_value(color_components[0]);
	color->g = color_component_value(color_components[1]);
	color->b = color_component_value(color_components[2]);
	free_matrix(color_components);
	if (!is_valid_rgb(color))
	{
		show_error("Invalid color values.");
		return (0);
	}
	return (1);
}

int	validate_scene_line(char *line, t_cub3d *cub)
{
	// t_list	map;

	// init_list(&map);
	// if (!is_empty_line(line) && !is_map_line(line && cub->scene.map.start_line &&  num_lines > (cub->scene.map.end_line + 1))
	// {
	// 	show_error("Invalid line in scene file after map found.");
	// 	show_error_free(line, "\n", 0);
	// 	return (0);
	// }
	if (is_empty_line(line))
		return (1);
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (validate_texture_line(line, &cub->scene.textures.no));
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (validate_texture_line(line, &cub->scene.textures.so));
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (validate_texture_line(line, &cub->scene.textures.we));
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (validate_texture_line(line, &cub->scene.textures.ea));
	if (ft_strncmp(line, "F ", 2) == 0)
		return (validate_color_line(line + 2, &cub->scene.textures.floor));
	if (ft_strncmp(line, "C ", 2) == 0)
		return (validate_color_line(line + 2, &cub->scene.textures.ceil));
	if (!is_scene_completed_without_map(cub))
	{
		show_error("Scene is missing required elements. Invalid line.\n");
		ft_putstr_fd(line, 2);
		return (0);
	}
	// if (cub->scene.map.start_line == 1) // @TODO change !cub->scene.map.start_line
	// {
	// 	printf("Starting map at line %d\n", num_lines);
	// 	cub->scene.map.start_line = num_lines;
	// }
	// cub->scene.map.end_line = num_lines;
	return (validate_map_line(line, cub));
}

int	read_and_parse_scene(char *path, t_cub3d *cub)
{
	int		fd;
	char	*line;
	char 	*trimmed;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		trimmed = ft_strtrim(line, "\n");
		free(line);
		if (!validate_scene_line(trimmed, cub))
		{
			free(trimmed);
			close(fd);
			return (0);
		}
		free(trimmed);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

int	validate_scene(char *path, t_cub3d *cub)
{
	init_scene(cub);
	print_scene(cub);
	if (!validate_scene_extension(path))
		return (0);
	if (!file_is_reachable(path))
	{
		show_error("Scene file not found.");
		return (0);
	}
	if (!read_and_parse_scene(path, cub))
		return (0);
	return (1);
}