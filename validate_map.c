/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 10:28:33 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/04/04 13:54:04 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_file_path(char *path)
{
	char	*expath;

	expath = ft_strrchr(path, '.');
	if (!expath)
		return (0);
	if (ft_strncmp(expath, ".ber", ft_strlen(expath)) != 0)
		return (0);
	return (1);
}

int	check_first_line(char *first)
{
	size_t	i;

	i = 0;
	while (first[i] == '1')
		i++;
	if (ft_strlen(first) == i)
		return (1);
	return (0);
}

int	ft_count_file_lines(char *map_file)
{
	int		i;
	char	*line;
	int		fd;

	i = 0;
	fd = open (map_file, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	return (i);
}

void	fill_array_from_file(char *map_file, char **map_array)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	fd = open (map_file, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		map_array[i] = line;
		i++;
		line = get_next_line(fd);
	}
	map_array[i] = 0;
	i = 0;
	close(fd);
}

int	check_map_line_length(char **map_array, int file_lines)
{
	int		i;
	size_t	line_length;

	i = 0;
	while (map_array[i])
	{
		line_length = ft_strlen(map_array[i]);
		if (i == file_lines - 1)
			line_length += 1;
		if (ft_strlen(map_array[0]) != line_length)
			return (0);
		i++;
	}
	return (1);
}

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
