/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 11:10:22 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/04/04 14:59:33 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	reach_exit(t_game *game)
{
	if (still_has_carrots(game->map_array) == 0)
	{
		print_moves(game);
		exit_win();
	}
}

void	rabit_move(t_game *game, int right_left, int up_down)
{
	int	x;
	int	y;

	y = 0;
	while (game->map_array[y])
	{
		x = 0;
		while (game->map_array[y][x])
		{
			if (game->map_array[y][x] == 'P')
			{
				if (game->map_array[y + up_down][x + right_left] == 'C')
					change_position(game, &(game->map_array[y][x]),
						&(game->map_array[y + up_down][x + right_left]));
				if (game->map_array[y + up_down][x + right_left] == '0')
					change_position(game, &(game->map_array[y][x]),
						&(game->map_array[y + up_down][x + right_left]));
				if (game->map_array[y + up_down][x + right_left] == 'E')
					reach_exit(game);
				return ;
			}
			x++;
		}
		y++;
	}
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == 53)
		exit_win();
	if (keycode == 13 || keycode == 126)
	{
		rabit_move(game, 0, -1);
	}
	if (keycode == 1 || keycode == 125)
	{
		rabit_move(game, 0, 1);
	}
	if (keycode == 0 || keycode == 123)
	{
		rabit_move(game, -1, 0);
	}
	if (keycode == 2 || keycode == 124)
	{
		rabit_move(game, 1, 0);
	}
	return (1);
}

void	argv_validate(int ac, char *map_name)
{
	if (ac != 2)
	{
		ft_printf("\033[0;31m Error\nInvalid Map Name");
		exit(0);
	}
	if (check_file_path(map_name) == 0)
	{
		ft_printf("\033[0;31m Invalid Map, shoud add .ber");
		exit(0);
	}
}

int	main(int ac, char **argv)
{
	t_game	game;
	int		i;
	char	**map_array;

	game.moves_count = 0;
	argv_validate(ac, argv[1]);
	i = ft_count_file_lines(argv[1]);
	ft_printf("line length = %d\n", i);
	map_array = malloc((i + 1) * sizeof(char *));
	if (!map_array)
		return (0);
	fill_array_from_file(argv[1], map_array);
	game.map_array = map_array;
	if (!check_map_is_valid(map_array, "map.ber"))
		return (0);
	ft_printf("\n\033[0;32m Valid Map\n");
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx,
			get_width(game, map_array, i), 64 * i, "So Long");
	get_path_images(&game);
	draw_to_win(game, map_array);
	mlx_hook(game.win, 2, 0, key_hook, &game);
	mlx_hook(game.win, 17, 0, exit_win, NULL);
	mlx_loop(game.mlx);
}
