/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 11:10:22 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/04/03 11:49:43 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	void	*img;
	void	*blck_img;
	int	x;
	int y;
}				t_vars;

void	move_img (t_vars *vars)
{
	mlx_clear_window(vars->mlx, vars->win);

	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, vars->x, vars->y);

}

int	key_hook(int keycode, t_vars *vars)
{

	printf("keycode == %d\n",keycode);
	return (1);
}
int	exit_win(void)
{

	exit(1);
	return(0);;
}

int	get_width(t_vars	vars, char **map_array, int lines_count)
{
	int	width;

	width = 0;
	while (map_array[0][width])
		width++;
	return (--width * 64);
}

void	draw_to_win(t_vars vars, char **map_array)
{
	int	y;
	int	x;
	int width;
	int height;

	y = 0;
	while (map_array[y])
	{
		x = 0;
		while (map_array[y][x])
		{
			if(map_array[y][x] == '1')
			{
				vars.img = mlx_xpm_file_to_image(vars.mlx, "./1.xpm", &width, &height);
				mlx_put_image_to_window(vars.mlx, vars.win, vars.img,  x * 64, y * 64);
			}
			else if(map_array[y][x] == 'P')
			{
				vars.img = mlx_xpm_file_to_image(vars.mlx, "./P.xpm", &width, &height);
				mlx_put_image_to_window(vars.mlx, vars.win, vars.img,   x * 64, y * 64);
			}
			else if(map_array[y][x] == 'E')
			{
				vars.img = mlx_xpm_file_to_image(vars.mlx, "./E.xpm", &width, &height);
				mlx_put_image_to_window(vars.mlx, vars.win, vars.img,   x * 64, y * 64);
			}
			else if(map_array[y][x] == 'C')
			{
				vars.img = mlx_xpm_file_to_image(vars.mlx, "./C.xpm", &width, &height);
				mlx_put_image_to_window(vars.mlx, vars.win, vars.img,   x * 64, y * 64);
			}
			else if(map_array[y][x] == '0')
			{
				vars.img = mlx_xpm_file_to_image(vars.mlx, "./0.xpm", &width, &height);
				mlx_put_image_to_window(vars.mlx, vars.win, vars.img,   x * 64, y * 64);
			}
			x++;

		}
		y++;
	}
}

void	rabit_move(char *str, char **map_array)
{
	int	x;
	int y;

	x = 0;
	y = 0;
	if (str == "right")
	{
		while (map_array[y])
		{
			x = 0;
			while (map_array[y][x])
			{
				if(map_array[y][x] == 'P')
				{
					
				}
			}
			y++;
		}
	}
}

int	main(int ac, char **argv)
{
	t_vars	vars;
	int		i;
	int 	fd;	
	char    **map_array;
	char *line;
	int height;
	int width;

	if (ac != 2)
	{
		printf("\033[0;31m Invalid Map Name");
		return (0);
	}
		
	if (check_file_path(argv[1]) == 0)
	{
		printf("\033[0;31m Invalid Map, shoud add .ber");
		return (0);	
	}
	i = ft_count_file_lines(argv[1]);

	printf("line length = %d\n",i);

	map_array = malloc((i + 1) * sizeof(char *));
	if (!map_array)
		return (0);
	fill_array_from_File(argv[1], map_array);



 	if(!check_map_is_valid(map_array,"map.ber"))
	 	return (0);
	printf("\n\033[0;32m Valid Map");
    printf("height === %d\n",i * 64);

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, get_width(vars, map_array, i), 64 * i, "Hello world!");
	// vars.img = mlx_xpm_file_to_image(vars.mlx, "./background.xpm", &height	, &width);
	// mlx_put_image_to_window(vars.mlx, vars.win, vars.img,  0, 0);
	draw_to_win(vars, map_array);
	
	mlx_hook(vars.win,  2, 0,  key_hook,  &vars);
	mlx_hook(vars.win,  17 , 0,  exit_win, NULL);
	mlx_loop(vars.mlx);
}


