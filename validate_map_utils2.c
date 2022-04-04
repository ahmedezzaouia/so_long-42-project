/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:04:27 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/04/04 15:04:51 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_last_and_first_char(char *line)
{
	size_t	length;

	length = ft_strlen(line) - 1;
	if (line[length] == '\n' )
		length--;
	return (line[0] == '1' && line[length] == '1');
}

int	check_line_is_wall(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
	{
		if (line[i] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_others_charachters(char c, int *counter)
{
	if (c == 'P' || c == 'C' || c == 'E' || c == '1' || c == '0')
	{
		if (c == 'P' )
			*counter += 1 ;
		if (*counter > 1)
		{
			ft_printf("\033[0;31m Error\nInvalid Map, Just One Player");
			return (0);
		}
		return (1);
	}
	else
	{
		ft_printf("\033[0;31m Error\nInvalid Map, Only (P,E,C,1,0) is allowed");
		return (0);
	}
}

int	is_contain_at_least_c(char **map_array)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map_array[i] != 0)
	{
		j = 0;
		while (map_array[i][j])
		{
			if (map_array[i][j] == 'C')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_exist(char **map_array)
{
	int		i;
	int		j;
	int		counter;

	i = 0;
	counter = 0;
	while (map_array[i])
	{
		j = 0;
		while (map_array[i][j])
		{
			if (map_array[i][j] == 'E')
				counter++;
			j++;
		}
		i++;
	}
	if (counter == 0)
	{
		ft_printf("\033[0;31m Error\nInvalid Map, should at least one exit");
		return (0);
	}
	return (1);
}
