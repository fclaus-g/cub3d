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
	cub->scene.map_read_end = 0;
	cub->map.map = NULL;
	cub->map.lines = NULL;
	cub->map.left_padding = -1;
	cub->map.rows = 0;
	cub->map.cols = 0;
	cub->player.angle = -1;
}

void	show_error_free(char *msg1, char *msg2, int msg_clean)
{
	char *error;

	error = ft_strjoin(msg1, msg2);
	show_error(error);
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

void	show_error_and_exit(char *msg, int exit_code)
{
	show_error(msg);
	exit(exit_code);
}

void	show_error(char *msg)
{
	char *error;

	error = ft_strjoin("Error\n", msg);
	ft_putstr_fd(error, 2);
	free(error);
}

int	is_map_space(char c)
{
	return ft_strchr(SCENE_SPACES, c) != NULL;
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


void	map_calculations(t_cub3d *cub, char *line)
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
	map_calculations(cub, line);
	return (1);
}

int	is_cardinal_line(char *line)
{
	return starts_with_and_space(line, "NO")
		|| starts_with_and_space(line, "SO")
		|| starts_with_and_space(line, "WE")
		|| starts_with_and_space(line, "EA");
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
	path = ft_strtrim(texture_components[1], SCENE_SPACES);
	free_matrix(texture_components);
	if (!path)
		show_error_and_exit("Failed to allocate memory for texture path.", 1);
	*texture = path;
	return (1);
}

int	is_scene_completed(t_cub3d *cub)
{
	return (cub->scene.textures.no != NULL
		&& cub->scene.textures.so != NULL
		&& cub->scene.textures.we != NULL
		&& cub->scene.textures.ea != NULL
		&& cub->scene.textures.floor.r != -1
		&& cub->scene.textures.ceil.r != -1
		&& cub->map.map != NULL
		&& cub->player.angle != -1);
}

void	ft_print_map_line(void *str)
{
	printf("\"%s\"\n", (char *)str);
}

void	print_scene(t_cub3d *cub)
{
	printf("NO: %s\n", cub->scene.textures.no);
	printf("SO: %s\n", cub->scene.textures.so);
	printf("WE: %s\n", cub->scene.textures.we);
	printf("EA: %s\n", cub->scene.textures.ea);
	printf("F: %d,%d,%d\n", cub->scene.textures.floor.r, cub->scene.textures.floor.g, cub->scene.textures.floor.b);
	printf("C: %d,%d,%d\n", cub->scene.textures.ceil.r, cub->scene.textures.ceil.g, cub->scene.textures.ceil.b);
	printf("Lines:\n");
	ft_lstiter(cub->map.lines, &ft_print_map_line);
	printf("Map (%dx%d), padding_left_remove(%d):\n", cub->map.rows, cub->map.cols, cub->map.left_padding);
	if (cub->map.map == NULL)
		printf("NULL\n");
	else {
		for (int i = 0; cub->map.map[i] != NULL; i++)
			printf("\"%s\"\n", cub->map.map[i]);
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

	trimmed = ft_strtrim(component, SCENE_SPACES);
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

int starts_with_and_space(char *line, char *start)
{
	int		i;
	int		spaces;

	i = 0;
	spaces = 0;
	while (line[spaces] && is_map_space(line[spaces]))
		spaces++;
	while (start[i] && line[i + spaces])
	{
		if (line[i + spaces] != start[i])
			return (0);
		i++;
	}
	if (!is_map_space(line[i]))
		return (0);
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

void	fill_map_matrix(t_cub3d *cub)
{
	t_list	*current;
	int		i;
	int		j;
	char	*line;

	cub->map.map = (char **)malloc(sizeof(char *) * (cub->map.rows + 1));
	if (!cub->map.map)
		show_error_and_exit("Failed to allocate memory for map matrix.", 1);
	i = 0;
	current = cub->map.lines;
	while (current)
	{
		line = (char *)current->content;
		cub->map.map[i] = (char *)malloc(sizeof(char) * (cub->map.cols + 1));
		if (!cub->map.map[i])
			show_error_and_exit("Failed to allocate memory for map row.", 1);
		j = 0;
		while (j < cub->map.cols && line[j + cub->map.left_padding])
		{
			if (is_map_space(line[j + cub->map.left_padding]))
				cub->map.map[i][j] = MAP_FILL_SPACE;
			else
				cub->map.map[i][j] = line[j + cub->map.left_padding];
			j++;
		}
		while (j < cub->map.cols)
		{
			cub->map.map[i][j] = MAP_FILL_SPACE;
			j++;
		}
		cub->map.map[i][j] = '\0';
		current = current->next;
		i++;
	}
	cub->map.map[i] = NULL;
}


int	check_if_map_is_closed(t_cub3d *cub)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < cub->map.rows)
	{
		j = 0;
		while (j < cub->map.cols)
		{
			c = cub->map.map[i][j];
			if (c == '0' || is_map_player(c))
			{
				if (i == 0 || i == cub->map.rows - 1 || j == 0 || j == cub->map.cols - 1)
					return (0);
				if (i > 0 && cub->map.map[i - 1][j] == MAP_FILL_SPACE)
					return (0);
				if (i < cub->map.rows - 1 && cub->map.map[i + 1][j] == MAP_FILL_SPACE)
					return (0);
				if (j > 0 && cub->map.map[i][j - 1] == MAP_FILL_SPACE)
					return (0);
				if (j < cub->map.cols - 1 && cub->map.map[i][j + 1] == MAP_FILL_SPACE)
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}


void	locate_player(t_cub3d *cub)
{
	int		i;
	int		j;

	i = 0;
	while (i < cub->map.rows)
	{
		j = 0;
		while (j < cub->map.cols)
		{
			if (is_map_player(cub->map.map[i][j]))
			{
				cub->player.x_pix = j * GRID_SIZE;
				cub->player.y_pix = i * GRID_SIZE;
				printf("Player located at (%f, %f) with angle %f\n", cub->player.x_pix, cub->player.y_pix, cub->player.angle);
				return ;
			}
			j++;
		}
		i++;
	}
}
int	read_and_parse_scene(char *path, t_cub3d *cub)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		tmp = line;
		line = ft_strtrim(line, "\n");
		free(tmp);
		if (!validate_scene_line(line, cub))
		{
			close(fd);
			return (0);
		}
		line = get_next_line(fd);
	}
	close(fd);
	cub->map.cols -= cub->map.left_padding;
	fill_map_matrix(cub);
	if (!is_scene_completed(cub))
	{
		show_error("Scene is missing required elements.");
		return (0);
	}
	if (!check_if_map_is_closed(cub))
	{
		show_error("Map is not closed.");
		return (0);
	}
	cub->map.w_px = cub->map.cols * GRID_SIZE;
	cub->map.h_px = cub->map.rows * GRID_SIZE;
	locate_player(cub);
	return (1);
}


int	validate_scene(char *path, t_cub3d *cub)
{
	init_scene(cub);
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
