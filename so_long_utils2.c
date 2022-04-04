/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:33:08 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/04/04 14:53:06 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	exit_win(void)
{
	exit(0);
	return (0);
}

int	get_width(t_game	game1, char **map_array, int lines_count)
{
	int	width;

	width = 0;
	while (map_array[0][width])
		width++;
	return (--width * 64);
}

void	get_path_images(t_game *game)
{
	int	w;
	int	h;

	game->wall = mlx_xpm_file_to_image(game->mlx, "./1.xpm", &w, &h);
	game->player = mlx_xpm_file_to_image(game->mlx, "./P.xpm", &w, &h);
	game->exit = mlx_xpm_file_to_image(game->mlx, "./E.xpm", &w, &h);
	game->carrote = mlx_xpm_file_to_image(game->mlx, "./C.xpm", &w, &h);
	game->space = mlx_xpm_file_to_image(game->mlx, "./0.xpm", &w, &h);
}