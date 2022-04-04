/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:31:10 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/04/04 14:33:16 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_images(t_game game, int x, int y)
{
	if (game.map_array[y][x] == '1')
		mlx_put_image_to_window(game.mlx, game.win,
			game.wall, x * 64, y * 64);
	else if (game.map_array[y][x] == 'P')
		mlx_put_image_to_window(game.mlx,
			game.win, game.player, x * 64, y * 64);
	else if (game.map_array[y][x] == 'E')
		mlx_put_image_to_window(game.mlx,
			game.win, game.exit, x * 64, y * 64);
	else if (game.map_array[y][x] == 'C')
		mlx_put_image_to_window(game.mlx, game.win,
			game.carrote, x * 64, y * 64);
	else if (game.map_array[y][x] == '0')
		mlx_put_image_to_window(game.mlx, game.win,
			game.space, x * 64, y * 64);
}

void	draw_to_win(t_game game, char **map_array)
{
	int	y;
	int	x;

	y = 0;
	while (map_array[y])
	{
		x = 0;
		while (map_array[y][x])
		{
			put_images(game, x, y);
			x++;
		}
		y++;
	}
}

int	still_has_carrots(char **map_array)
{
	int	x;
	int	y;
	int	counter;

	y = 0;
	counter = 0;
	while (map_array[y])
	{
		x = 0;
		while (map_array[y][x])
		{
			if (map_array[y][x] == 'C')
				counter++;
			x++;
		}
		y++;
	}
	return (counter);
}

void	print_moves(t_game *game)
{	
	game->moves_count++;
	ft_printf("move : %d\n", game->moves_count);
}

void	change_position(t_game *game, char *current_pos, char *next_pos)
{
	*current_pos = '0';
	*next_pos = 'P';
	mlx_clear_window(game->mlx, game->win);
	draw_to_win(*game, game->map_array);
	print_moves(game);
}
