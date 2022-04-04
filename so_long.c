/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 11:10:22 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/04/03 17:51:36 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"

typedef struct	s_game {
	void	*mlx;
	void	*win;
	void	*img;
	void	*player;
	void	*wall;
	void	*rabit;
	void	*space;
	void	*exit;
	void	*carrote;
	void	*blck_img;
	char	**map_array;
	int		moves_count;
	int	x;
	int y;
}				t_game;



int	exit_win()
{

	exit(1);
	return(0);;
}

int	get_width(t_game	game1, char **map_array, int lines_count)
{
	int	width;

	width = 0;
	while (map_array[0][width])
		width++;
	return (--width * 64);
}

void	get_path(t_game *game)
{
	int width;
	int height;
	game->wall = mlx_xpm_file_to_image(game->mlx, "./1.xpm", &width, &height);
	game->player = mlx_xpm_file_to_image(game->mlx, "./P.xpm", &width, &height);
	game->exit = mlx_xpm_file_to_image(game->mlx, "./E.xpm", &width, &height);
	game->carrote = mlx_xpm_file_to_image(game->mlx, "./C.xpm", &width, &height);
	game->space = mlx_xpm_file_to_image(game->mlx, "./0.xpm", &width, &height);
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
			if(map_array[y][x] == '1')
			{
				mlx_put_image_to_window(game.mlx, game.win, game.wall,  x * 64, y * 64);
			}
			else if(map_array[y][x] == 'P')
			{
				mlx_put_image_to_window(game.mlx, game.win, game.player,   x * 64, y * 64);
			}
			else if(map_array[y][x] == 'E')
			{
				mlx_put_image_to_window(game.mlx, game.win, game.exit,   x * 64, y * 64);
			}
			else if(map_array[y][x] == 'C')
			{
				mlx_put_image_to_window(game.mlx, game.win, game.carrote,   x * 64, y * 64);
			}
			else if(map_array[y][x] == '0')
			{
				mlx_put_image_to_window(game.mlx, game.win, game.space,   x * 64, y * 64);
			}
			x++;

		}
		y++;
	}
}

int	still_has_carrots(char **map_array)
{
	int x;
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
	ft_printf("move : %d\n",game->moves_count);
}

void	rabit_move(t_game *game,int right_left, int up_down)
{
	int	x;
	int y;

	x = 0;
	y = 0;

	while (game->map_array[y])
	{
		x = 0;
		while (game->map_array[y][x])
		{
			if(game->map_array[y][x] == 'P')
			{
				if (game->map_array[y + up_down][x + right_left] == 'C')
				{
					game->map_array[y][x] = '0';
					game->map_array[y + up_down][x + right_left] = 'P';
					mlx_clear_window(game->mlx, game->win);
					draw_to_win(*game, game->map_array);
					game->moves_count++;
					ft_printf("move : %d\n",game->moves_count);
					return ;
				}
				if (game->map_array[y + up_down][x + right_left] == '0')
				{
					game->map_array[y][x] = '0';
					game->map_array[y + up_down][x + right_left] = 'P';
					mlx_clear_window(game->mlx, game->win);
					draw_to_win(*game, game->map_array);
					game->moves_count++;
					ft_printf("move : %d\n",game->moves_count);
					return ;
				}
				if (game->map_array[y + up_down][x + right_left] == 'E')
				{
					if (still_has_carrots(game->map_array) == 0)
					{
						game->moves_count++;
						ft_printf("move : %d\n",game->moves_count);
						exit_win();
					}
					return ;
				}
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






int	main(int ac, char **argv)
{
	t_game	game;
	int		i;
	int 	fd;	
	char    **map_array;
	char *line;
	int height;
	int width;
    
	game.x = 20;
	game.moves_count = 0;
	if (ac != 2)
	{
		ft_printf("\033[0;31m Invalid Map Name");
		return (0);
	}
		
	if (check_file_path(argv[1]) == 0)
	{
		ft_printf("\033[0;31m Invalid Map, shoud add .ber");
		return (0);	
	}
	i = ft_count_file_lines(argv[1]);

	ft_printf("line length = %d\n",i);

	map_array = malloc((i + 1) * sizeof(char *));
	if (!map_array)
		return (0);
	fill_array_from_File(argv[1], map_array);
	game.map_array = map_array;
 	if(!check_map_is_valid(map_array,"map.ber"))
	 	return (0);
	ft_printf("\n\033[0;32m Valid Map\n"); 

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, get_width(game, map_array, i), 64 * i, "Hello world!");
	// game.img = mlx_xpm_file_to_image(game.mlx, "./background.xpm", &height	, &width);
	// mlx_put_image_to_window(game.mlx, game.win, game.img,  0, 0);
	get_path(&game);
	draw_to_win(game, map_array);
	
	mlx_hook(game.win,  2, 0,  key_hook,  &game);
	mlx_hook(game.win,  17 , 0,  exit_win, NULL);
	mlx_loop(game.mlx);
}


