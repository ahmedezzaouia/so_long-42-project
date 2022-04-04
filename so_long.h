/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 10:34:50 by ahmez-za          #+#    #+#             */
/*   Updated: 2021/12/18 16:15:31 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "./ft_printf/ft_printf.h"
#include "get_next_line.h"
#include <mlx.h>
#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int check_file_path(char *path);
int check_map_is_valid(char **map_array, char *map_file);
char    *get_next_line(int fd);
void    fill_array_from_File(char *map_file, char **map_array);
int	ft_count_file_lines(char *map_file);
int	check_map_line_length(char **map_array, int file_lines);