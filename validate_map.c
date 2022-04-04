/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 10:28:33 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/04/04 15:04:37 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_validate_splite(char **map_array, int lines_length)
{
	if (!check_map_line_length(map_array, lines_length))
	{
		ft_printf("\033[0;31m Error\nInvalid Map, lines length not equals");
		exit (0);
	}
	if (!check_exist(map_array))
		exit (0);
	if (!is_contain_at_least_c(map_array))
	{
		ft_printf("\033[0;31m Error\nInvalid Map, sould contain at least one C");
		exit (0);
	}
}

void	rectangle_validate(char **map_array, int i, int lines_length)
{
	if (check_last_and_first_char(map_array[i]) == 0)
	{
		ft_printf("\033[0;31m Error\nInvalid Map, line should surrond with 1");
		exit (0);
	}
	if (i == lines_length - 1 || i == 0)
	{
		if (!check_line_is_wall(map_array[i]))
		{
			ft_printf("\033[0;31m Error\nInvalid Map, first and last Nofulled 1");
			exit (0);
		}
	}
}

void	check_player_counter(int counter)
{
	if (counter != 1)
	{
		ft_printf("\033[0;31m Error\nInvalid Map, at least  one P");
		exit (0);
	}
}

int	check_map_is_valid(char **map_array, char *map_file)
{
	int	i;
	int	j;
	int	lines_length;
	int	counter;

	j = 0;
	i = 0;
	counter = 0;
	lines_length = ft_count_file_lines(map_file);
	map_validate_splite(map_array, lines_length);
	while (map_array[i] != 0)
	{
		rectangle_validate(map_array, i, lines_length);
		j = 0;
		while (map_array[i][j] != '\n' && map_array[i][j] != '\0')
		{
			if (!check_others_charachters(map_array[i][j], &counter))
				return (0);
			j++;
		}	
		i++;
	}
	check_player_counter(counter);
	return (1);
}
