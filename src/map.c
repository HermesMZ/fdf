/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 17:09:12 by mzimeris          #+#    #+#             */
/*   Updated: 2025/07/18 15:39:48 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	process_single_point(t_mlx_data *data, int line_index, int j,
	char *point)
{
	t_point	new_point;
	char	**splitted;

	new_point.color.color = 0xFFFFFF;
	splitted = ft_split(point, ',');
	if (!splitted)
		return (ft_putstr_fd("Error: z / color.\n", 2), 1);
	new_point.x = (double)j;
	new_point.y = (double)line_index;
	new_point.z = ft_atoi(splitted[0]);
	new_point.px = 0;
	new_point.py = 0;
	if (splitted[1])
		new_point.color.color = ft_hextoi(splitted[1]);
	extract_rgb(&new_point.color, new_point.color.color);
	free_splitted(splitted);
	data->map->points[line_index][j] = new_point;
	return (0);
}

static int	process_single_map_line(int fd, t_mlx_data *data, int line_index)
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
		if (splitted_line[j] && process_single_point(data, line_index,
				j, splitted_line[j]))
			return (1);
		j++;
	}
	free(line);
	free_splitted(splitted_line);
	return (0);
}

static int	fill_map_data(t_mlx_data *data, char *file_path)
{
	int	fd;
	int	line_index;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening file for filling data"), 1);
	line_index = 0;
	while (line_index < data->map->lines)
	{
		if (process_single_map_line(fd, data, line_index) == 1)
			return (close_gnl_fd(fd), 1);
		line_index++;
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
			if (data->map->points[l][c].z < data->map->min_z)
				data->map->min_z = data->map->points[l][c].z;
			if (data->map->points[l][c].z > data->map->max_z)
				data->map->max_z = data->map->points[l][c].z;
			c++;
		}
		l++;
	}
}

int	check_extract_map(t_mlx_data *data, char *file_path)
{
	if (count_map_dimensions(data, file_path) == 1)
		return (1);
	data->map->points = create_map(data->map->lines, data->map->columns);
	if (!data->map->points)
		return (ft_putstr_fd("Error: Failed to allocate map memory.\n", 2), 1);
	if (fill_map_data(data, file_path) == 1)
	{
		free_map(data->map->points);
		data->map->points = NULL;
		return (1);
	}
	find_min_max_z(data);
	return (0);
}
