/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmez-za <ahmez-za@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 23:08:06 by ahmez-za          #+#    #+#             */
/*   Updated: 2021/12/18 13:16:01 by ahmez-za         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_is_new_line(char *save)
{
	int	i;

	if (!save)
		return (0);
	i = 0;
	while (save[i])
	{
		if (save[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_get_line(char *save)
{
	int		i;
	char	*line;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] != '\n' && save[i] != '\0')
		i++;
	line = ft_substr(save, 0, ++i);
	return (line);
}

char	*ft_get_remaining(char *save)
{
	int		i;
	char	*remain;

	i = 0;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	while (save[i] != '\0' && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		i++;
	remain = ft_substr(save, i, ft_strlen(save));
	free(save);
	return (remain);
}

char	*free_buffer(char *buffer)
{
	free(buffer);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*save = NULL;
	int			r;

	buffer = NULL;
	line = NULL;
	r = 1;
	if (fd < 0)
		return (NULL);
	buffer = malloc((1 + 5) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (ft_is_new_line(save) != 1 && r != 0)
	{
		r = read(fd, buffer,5);
		if (r == -1)
			return (free_buffer(buffer));
		buffer[r] = '\0';
		save = ft_strjoin(save, buffer);
	}
	free(buffer);
	line = ft_get_line(save);
	save = ft_get_remaining(save);
	return (line);
}