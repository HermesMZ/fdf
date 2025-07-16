/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:09:12 by mzimeris          #+#    #+#             */
/*   Updated: 2025/07/16 19:29:00 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	process_single_map_line(int fd, t_mlx_data *data, int clx)
{
	char	*line;
	char	**splitted_line;
	int		j;

	line = new_line(fd);
	if (!line)
		return (ft_putstr_fd("Error: map filling.\n", 2), 1);
	splitted_line = ft_split(line, ' ');
	if (!splitted_line)
	{
		free(line);
		ft_putstr_fd("Error: Failed to split map line.\n", 2);
		return (1);
	}
	j = 0;
	while (j < data->map->columns)
	{
		if (splitted_line[j])
			data->map->array_map[clx][j]
				= ft_atoi(splitted_line[j]);
		j++;
	}
	free(line);
	free_splitted(splitted_line);
	return (0);
}

static int	fill_map_data(t_mlx_data *data, char *file_path)
{
	int	fd;
	int	clx;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening file for filling data"), 1);
	clx = 0;
	while (clx < data->map->lines)
	{
		if (process_single_map_line(fd, data, clx) == 1)
			return (close_gnl_fd(fd), 1);
		clx++;
	}
	close_gnl_fd(fd);
	return (0);
}

static void	find_min_max_z(t_mlx_data *data)
{
	int	l;
	int	c;

	l = 0;
	while (l < data->map->lines)
	{
		c = 0;
		while (c < data->map->columns)
		{
			if (data->map->array_map[l][c] < data->map->min_z)
				data->map->min_z = data->map->array_map[l][c];
			if (data->map->array_map[l][c] > data->map->max_z)
				data->map->max_z = data->map->array_map[l][c];
			c++;
		}
		l++;
	}
}

int	check_extract_map(t_mlx_data *data, char *file_path)
{
	if (count_map_dimensions(data, file_path) == 1)
		return (1);
	data->map->array_map = create_map(data->map->lines, data->map->columns);
	if (!data->map->array_map)
		return (ft_putstr_fd("Error: Failed to allocate map memory.\n", 2), 1);
	if (fill_map_data(data, file_path) == 1)
	{
		free_map(data->map->array_map);
		data->map->array_map = NULL;
		return (1);
	}
	find_min_max_z(data);
	return (0);
}
