/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 10:34:50 by ahmez-za          #+#    #+#             */
/*   Updated: 2022/04/04 15:25:36 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "./libft/libft.h"
# include "./ft_printf/ft_printf.h"
# include "get_next_line.h"
# include <mlx.h>
# include<stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct s_game{
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
}				t_game;

int		check_file_path(char *path);
int		check_map_is_valid(char **map_array, char *map_file);
char	*get_next_line(int fd);
void	fill_array_from_file(char *map_file, char **map_array);
int		ft_count_file_lines(char *map_file);
int		check_map_line_length(char **map_array, int file_lines);

int		exit_win(void);
int		get_width(char **map_array);
void	get_path_images(t_game *game);
void	put_images(t_game game, int x, int y);
void	draw_to_win(t_game game, char **map_array);
int		still_has_carrots(char **map_array);
void	print_moves(t_game *game);
void	change_position(t_game *game, char *current_pos, char *next_pos);

int		check_file_path(char *path);
int		check_first_line(char *first);
int		ft_count_file_lines(char *map_file);
void	fill_array_from_file(char *map_file, char **map_array);
int		check_map_line_length(char **map_array, int file_lines);
int		check_last_and_first_char(char *line);
int		check_line_is_wall(char *line);
int		check_others_charachters(char c, int *counter);
int		is_contain_at_least_c(char **map_array);
int		check_exist(char **map_array);

#endif