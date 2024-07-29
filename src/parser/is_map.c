/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgarcia <frgarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:53:44 by frgarcia          #+#    #+#             */
/*   Updated: 2024/07/29 15:53:46 by frgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	is_map_space(char c)
{
	return (ft_strchr(SCENE_SPACES, c) != NULL);
}

int	is_map_element(char c)
{
	return (c == '0' || c == '1');
}

int	is_map_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

int	is_map_character(char c)
{
	return (is_map_space(c) || is_map_element(c) || is_map_player(c));
}

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!is_map_space(line[i]) && !is_map_element(line[i])
			&& !is_map_player(line[i]))
			return (0);
		i++;
	}
	return (1);
}
