/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 11:10:22 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/02/27 12:56:48 by ahmez-za         ###   ########.fr       */
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

	if (keycode == 124)
	{
		if (vars->x <= 800)
			vars->x += 100;	
		move_img(vars);
	}
	else if (keycode == 123)
	{
		if (vars->x > 0)
			vars->x -= 100;	
		move_img(vars);
	}
	if (keycode == 126)
	{
		if (vars->y > 0)
			vars->y -= 100;	
		move_img(vars);
	}
	else if (keycode == 125)
	{
		printf("y = %d\n",vars->y);
		if (vars->y <= 500)
			vars->y += 100;	
		move_img(vars);
	}
	printf("key == %d\n",keycode);
	return (1);
}
int  f(viod)
{

	exit(1);
	return(0);;
}

int	main(int ac, char **argv)
{
	t_vars	vars;
	int width;
	int height;
	int		i;
	int 	fd;	
	char    **map_array;
	char *line;

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

	printf("\n");
	printf("\n");
	printf("\n");

	map_array = malloc((i + 1) * sizeof(char *));
	if (!map_array)
		return (0);
	
	fill_array_from_File(argv[1], map_array);
	 i = 0;
	// while (map_array[i] != 0)
	// 	// printf("%s",map_array[i++]);
	printf("\n");
	printf("\n");
	printf("\n");



 	if(!check_map_is_valid(map_array,"map.ber"))
	 	return (0);
	printf("\033[0;32m Valid Map");


	// vars.x = 0;
	// vars.y = 0;
	// vars.mlx = mlx_init();
	// vars.win = mlx_new_window(vars.mlx, 1000,700, "Hello world!");
	// vars.img = mlx_xpm_file_to_image(vars.mlx, "./ima.xpm", &width, &height);
	// //vars.blck_img = mlx_xpm_file_to_image(vars.mlx, "./black.xpm", &width, &height);
	// mlx_put_image_to_window(vars.mlx, vars.win, vars.img,  0, 0);
	// mlx_hook(vars.win,  2, 0,  key_hook,  &vars);
	// mlx_hook(vars.win,  17 , 0,  f, NULL);
	// mlx_loop(vars.mlx);
}


