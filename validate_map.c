/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 10:28:33 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/02/27 12:58:34 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// int	check_characters(char **map_array)
// {

// }

int check_file_path(char *path)
{
    char    *expath;

    expath = ft_strchr(path, '.'); 
    if (!expath)
        return (0);
    if (ft_strncmp(expath, ".ber", ft_strlen(expath)) != 0)
        return (0);
    return(1);
}

int check_first_line(char *first)
{
    size_t i;

    i = 0;
    while (first[i] == '1')
        i++;
    
    if (ft_strlen(first) == i)
        return (1);
    return (0);
}

int	ft_count_file_lines(char *map_file)
{
	int	i;
	char *line;

	i = 0;
	int fd = open (map_file, O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		free(line);
		i++;
	}
	close(fd);
	return (i);

}

void    fill_array_from_File(char *map_file, char **map_array)
{
    char *line;
	int i;
	int fd;
	i = 0;
	fd = open (map_file,O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		map_array[i] = line;
		// printf("line == %s\n",map_array[i]);
		i++;
	}
    map_array[i] = 0;
	i   = 0;
	while (map_array[i] != 0)
		printf("%s",map_array[i++]);
	close(fd);
}

int	check_map_line_length(char **map_array, int file_lines)
{
	int	i;
	size_t	line_length;

	i = 0;

	while (map_array[i] /*&& map_array[i + 1]*/)
	{
		line_length = ft_strlen(map_array[i]);
		if (i == file_lines  - 1)
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

int check_line_is_wall(char *line)
{
	int i;

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
		if (*counter  > 1  )
		{
			printf("\033[0;31m Invalid Map, Double Character");
			return (0);
		}
	
		return (1);				
	}
	else {
		printf("\033[0;31m Invalid Map, characters is invalid : only (P,E,C,1,0) is allowed");
		return (0);
	}
}

int	is_contain_at_least_C(char **map_array)
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

int check_map_is_valid(char **map_array, char *map_file)
{
	int	i;
	int	j;
	int	lines_length;
	// char	double_chars[5];
	int	counter;

	j = 0;
	i = 0;
	counter = 0;
	// while (i < 5)
	// 	double_chars[i++] = 0;
	// i = 0;
	lines_length = ft_count_file_lines(map_file);
	if (!check_map_line_length(map_array, lines_length))
	{
		printf("\033[0;31m Invalid Map, lines length not equals");
		return (0);
	}
	if (!is_contain_at_least_C(map_array))
	{
		printf("\033[0;31m Invalid Map, sould contain at least one C");
		return (0);
	}
	while (map_array[i] != 0)
	{
		printf("%d",check_last_and_first_char(map_array[i]));
		if(check_last_and_first_char(map_array[i])  == 0)
		{
			printf("\033[0;31m Invalid Map, line should end and start with 1");
			return (0);
		}
		if (i == lines_length - 1 || i == 0)
		{
			if(!check_line_is_wall(map_array[i]))
			{
				printf("\033[0;31m Invalid Map, first and last lines should be full filled with only 1 char");
				return (0);
			}
		}
		j = 0;
		while (map_array[i][j] != '\n' && map_array[i][j] != '\0')
		{
			char c = map_array[i][j];
			if (!check_others_charachters(c, &counter))
				return (0);
			j++;
		}
		
		i++;
	}
	if (counter != 1 ) 
		{
			printf("\033[0;31m Invalid Map, at least  one P");
			return (0);
		}
	return (1);
}