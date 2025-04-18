/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frgarcia <frgarcia@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:52:35 by frgarcia          #+#    #+#             */
/*   Updated: 2024/07/29 15:52:36 by frgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	show_error_free(char *msg1, char *msg2, int msg_clean)
{
	char	*error;

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
	char	*error;

	error = ft_strjoin("Error\n", msg);
	ft_putstr_fd(error, 2);
	free(error);
}
