/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_textures_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgarcia <frgarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:49:30 by frgarcia          #+#    #+#             */
/*   Updated: 2024/07/29 18:59:22 by frgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/cub3d_bonus.h"

int	validate_texture_line(char *line, char **texture)
{
	char	**texture_components;
	char	*path;

	if (*texture != NULL)
		return (show_error("Duplicate texture line."), 0);
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
	if (!file_is_reachable(path))
	{
		show_error_free(path,
			": Texture file not found or without permissions.\n", 1);
		return (0);
	}
	*texture = path;
	return (1);
}

/**
 * Validates color component value.
 * 
 * @return -1 if invalid color component, color (0-255) if valid.
 */
static int	color_component_value(char *component)
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
	{
		free(trimmed);
		return (-1);
	}
	free(trimmed);
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
