/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 15:03:37 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/04/04 15:03:47 by ahmez-za         ###   ########.fr       */
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
